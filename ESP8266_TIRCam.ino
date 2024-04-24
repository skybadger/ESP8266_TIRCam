/*
 Program to present MLX90640 Thermal IR imaging sensor sensor as an imaging camera available to ASCOM clients. 
 
 Output is sent to MQTT topics:
 /skybadger/sensors/temperature/host/radiant[], 
 /skybadger/device/health/host
 
 Supports REST web interface on port 80 returning application/json string
 
Uses I2C pins on ESP8266-01 to talk to devices. 
uses GPIO3 as single Serial Tx out pin @115200 baud/no parity/8 bits. 
To do:
Fix MQTT reporting by alignment with DomeSensor model.

Done: 
Fix all XXX.begin errors to return their boolean status as to whether present on the bus . 

Sensors added are:
Use MLX90640 library for sky temperature sensing

 Layout:
 GPIO 4,2 to SDA
 GPIO 5,0 to SCL 
 All 3.3v logic. 
 */
/*
 Needed this to debug a wifi stack exception caused by having the MQTT message size different betwwen here and the library code. 
 Only became apparent after a rebuild much later after the edit. 
 */
#define _USE_EEPROM_ 
#define USE_ESP32
//SSIDs and passwords are pulled in to protect from GIT over-sharing.
#include "TIRcam_ProjectDefs.h"
#include "AlpacaErrorConsts.h"
#include "SkybadgerStrings.h"
#include "DebugSerial.h"
#if defined USE_ESP8266
#include <esp8266_peri.h> //register map and access
#include <ESP8266WiFi.h>
#include <Wire.h>             //https://playground.arduino.cc/Main/WireLibraryDetailedReference
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#else if defined USE_ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "esp_http_server.h"
#include "esp_timer.h"
//#include "img_converters.h"
//#include "camera_index.h"
#include "Arduino.h"

//#include "fb_gfx.h"
//#include "fd_forward.h"
//#include "fr_forward.h"
#endif

#include <EEPROM.h>
#include <EEPROMAnything.h>
#include <ArduinoJson.h>  //https://arduinojson.org/v5/api/
#define MQTT_MAX_PACKET_SIZE 256 //Have to change in source since Arduino won't recompile the library otherwise. 
#include <PubSubClient.h> //https://pubsubclient.knolleary.net/api.html
#include <Math.h>         //Used for PI && log10
//#include <GDBStub.h>  //Debugging stub for GDB

//Ntp dependencies - available from v2.4
#include <time.h>
#include <sys/time.h>
#include <coredecls.h>

time_t now; //use as 'gmtime(&now);'

DynamicJsonBuffer jsonBuffer(256);
JsonObject& root = jsonBuffer.createObject();

//MQTT Pubsubclient variables
WiFiClient espClient;
PubSubClient client(espClient);
volatile bool callbackFlag = 0;
//Used by MQTT reconnect
volatile bool timerSet  = false;

const int MAXDATA = 256;

//Function definitions
uint32_t inline ICACHE_RAM_ATTR myGetCycleCount();
void onTimer(void);
void onTimeoutTimer(void);
void callback(char* topic, byte* payload, unsigned int length) ;

//Sky Temperature Sensor
#include "Adafruit_MLX90640.h"
Adafruit_MLX90640 mlx;
bool mlxPresent = false;
float[32x24] skyTemperature;

// Web server instance - create an instance of the server
// specify the port to listen on as an argument
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

//Timestring and MQTT reconnect functions
#include "Skybadger_common_funcs.h"

//Web Handler function definitions
#include "TIRcam_Eeprom.h"
#include "ESP8266_TIRcamHandlers.h"

void setup()
{
  Serial.begin( 115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.println(F("ESP starting."));
  //gdbstub_init();
  
  //Start NTP client
//  struct timezone tzone;
  configTime( TZ_SEC, DST_SEC, timeServer1, timeServer1, timeServer3 );
  //syncTime();
  
  //Setup defaults first - via EEprom. 
  EEPROM.begin(256);
#if defined _USE_EEPROM_
  setupFromEeprom();
#else
  setDefaults();
#endif 
  
  //Pins mode and direction setup for i2c on ESP8266-01
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
   
  //I2C setup SDA pin 0, SCL pin 2 on ESP-01
  //I2C setup SDA pin 5, SCL pin 4 on ESP-12
  Wire.begin(0, 2);
  //Wire.begin(5, 4);
  Wire.setClock(400000 );//100KHz target rate
  
  Serial.println("Pins setup & interrupts attached.");
    
  // Connect to wifi 
  setup_wifi();                   
  
  //Open a connection to MQTT
  client.setServer( mqtt_server, 1883 );
  client.connect( thisID, pubsubUserID, pubsubUserPwd ); 

  //Create a timer-based callback that causes this device to read the local i2C bus devices for data to publish.
  client.setCallback( callback );
  client.subscribe( inTopic );
  client.loop();
  publishHealth();
  Serial.println("MQTT setup complete.");

//Setup the sensors
//MLX IRcam sensor setup
  Serial.print("Probe MLX: ");
  mlxPresent = mlx.begin( MLX90640_I2CADDR_DEFAULT, &Wire );
  if( !mlxPresent ) 
  {
    Serial.println("MLX Sensor missing");
  }
  else
  {
    Serial.println("MLX Sensor found");
    mlx.setMode(MLX90640_INTERLEAVED);
    mlx.setResolution( MLX90640_ADC_19BIT );
    mlx.setRefreshRate(MLX90640_1_HZ);
  }
 
  //Setup webserver handler functions 
  //Common ASCOM handlers
  server.on(F("/api/v1/camera/0/action"),              HTTP_PUT, handleAction );
  server.on(F("/api/v1/camera/0/commandblind"),        HTTP_PUT, handleCommandBlind );
  server.on(F("/api/v1/camera/0/commandbool"),         HTTP_PUT, handleCommandBool );
  server.on(F("/api/v1/camera/0/commandstring"),       HTTP_PUT, handleCommandString );
  server.on(F("/api/v1/camera/0/connected"),           handleConnected );
  server.on(F("/api/v1/camera/0/description"),         HTTP_GET, handleDescriptionGet );
  server.on(F("/api/v1/camera/0/driverinfo"),          HTTP_GET, handleDriverInfoGet );
  server.on(F("/api/v1/camera/0/driverversion"),       HTTP_GET, handleDriverVersionGet );
  server.on(F("/api/v1/camera/0/interfaceversion"),    HTTP_GET, handleInterfaceVersionGet );
  server.on(F("/api/v1/camera/0/name"),                HTTP_GET, handleNameGet );
  server.on(F("/api/v1/camera/0/supportedactions"),    HTTP_GET, handleSupportedActionsGet );

  //ASCOM handler capability functions
  //server.on(UriRegex("^\\/api\\/v1\\/camera\\/([0-9])\\/can([a-z,A-Z]+)$"), handlerGenericGetCapabilityHandler );
  server.on(F("/api/v1/camera/0/canabortexposure"),    HTTP_GET, handlerGetCanAbortExposure );
  server.on(F("/api/v1/camera/0/canasymmetricbin",     HTTP_GET, handlerGetCanAsymmetricBin );
  server.on(F("/api/v1/camera/0/canfastreadout",       HTTP_GET, handlerGetCanFastReadout );
  server.on(F("/api/v1/camera/0/cangetcoolerpower",    HTTP_GET, handlerGetCanGetCoolerPower );
  server.on(F("/api/v1/camera/0/canpulseguide",        HTTP_GET, handlerGetCanPulseGuide );
  server.on(F("/api/v1/camera/0/cansetccdtemperature", HTTP_GET, handlerGetCanSetCCDTemperature );
  server.on(F("/api/v1/camera/0/canabortexposure",     HTTP_GET, handlerGetCanStopExposure );

//State
  server.on(F("/api/v1/camera/0/camerastate",     HTTP_GET, handlerGetCameraState);
  server.on(F("/api/v1/camera/0/ispulseguiding",  HTTP_GET, handlerGetIsPulseGuiding);
  server.on(F("/api/v1/camera/0/imageready",      HTTP_GET, handlerGetImageReady);

//Sensor properties
/*
handlerGetPixelSizeX(void);
handlerGetPixelSizeY(void);
handlerGetReadoutMode(void);
handlerGetReadoutModes(void);
handlerGetSensorName(void);
handlerGetSensorType(void);
handlerGetCameraXSize(void);
handlerGetCameraYSize(void);
handlerGetBayerOffsetX(void);
handlerGetBayerOffsetY(void);
handlerGetElectronsPerADU(void);
handlerGetFullWellCapacity(void);​
handlerGetMaxADU(void);
handlerGetMaxBinX(void);
handlerGetMaxBinY(void);
*/
//Image sizes
/*
handlerGetStartX(void);
handlerGetBinX(void);
handlerGetBinY(void);
handlerGetSubframeWidth(void);
handlerGetSubframeHeight(void);
*/

//cooler control
/*
handlerGetCCDTemperature(void);
handlerGetCoolerOn(void);
handlerGetCoolerPower(void);
handlerGetHeatSinktemperature(void);
handlerGetCCDTemperatureSetpoint(void);
*/

//Exposure controls
/*
handlerGetExposureMax(void);
handlerGetExposureMin(void);
handlerGetExposureResolution(void);
handlerGetFastReadout(void);
handlerGetGain(void);
handlerGetGainMax(void);
handlerGetGainMin();
handlerGetGains(void);
handlerGetHasShutter(void);
handlerGetLastExposureDuration(void);
handlerGetLastExposureStartTime(void);
handlerGetOffset(void);
handlerGetOffsetMax(void);
handlerGetOffsetMin(void);
handlerGetOffsets(void);
*/

//Image readout
/*
handlerGetImageArray(void);
handlerGetImageArrayVariant(void);
handlerGetPercentageComplete(void);
handlerGetSubExposure(void);
handlerGetSubExposure(void);
*/

//PUT

//ASCOM handler functions 

//handlerPutStartX(void);
//handlerPutStartY(void);
server.on(UriRegex("^\\/api\\/v1\\/camera\\/0\\/handlerPutStart([x,X,Y,y])$"), handlerPutStart );
//handlerPutBinFactorX(void);
//handlerPutBinFactorY(void);
server.on(UriRegex("^\\/api\\/v1\\/camera\\/0\\/handlerPutBinFactor([x,X,Y,y])$"), handlerPutBinFactor );
//handlerPutSubframeX(void);
//handlerPutSubframeY(void);
server.on(UriRegex("^\\/api\\/v1\\/camera\\/0\\/handlerPutSubFrame([x,X,Y,y])$"), handlerPutSubFrame );

//handlerPutCoolerEnabled(void);
//handlerPutCCDTemperature(void);
//handlerPutReadoutMode(void);
//handlerPutGain(void);
//handlerPutOffset(void);
//handlerPutSubExposureDuration(void);

//handlerPutAbortExposure(void);
//handlerPutStartExposure(void);
//handlerPutStopExposure (void);
server.on(UriRegex("^\\/api\\/v1\\/camera\\/0\\/handlerPut([a-z, A-Z]+)Exposure$"), handlerPutExposure );

handlerPutPulseGuide(void);
*/
  //Additional ASCOM ALPACA Management setup calls
  //Per device
  //TODO - split whole device setup from per-instance driver setup e.g. hostname, alpaca port to device compared to ccal setup on the driver, 
//  server.on(F("/setup"),                               HTTP_GET, handlerDeviceSetup );
//  server.on(F("/setup/hostname") ,                     HTTP_ANY, handlerDeviceHostname );
//  server.on(F("/setup/udpport"),                       HTTP_ANY, handlerDeviceUdpPort );
//  server.on(F("/setup/location"),                      HTTP_ANY, handlerDeviceLocation );


//Management interface calls.
/* ALPACA Management and setup interfaces
 * The main browser setup URL would be http://<hostname>:<port>/api/v1/setup  
 * The JSON list of supported interface versions would be available through a GET to http://<hostname>:<port>/management/apiversions
 * The JSON list of configured ASCOM devices would be available through a GET to http://<hostname>:<port>/management/v1/configureddevices
 * Where <hostname> is whatever you set it to be at wifi startup time via myHostname 
 * and the port is set in the Web server settings - typically 80.
 */
  //Management API - https://www.ascom-standards.org/api/?urls.primaryName=ASCOM%20Alpaca%20Management%20API#/Management%20Interface%20(JSON)
  server.on(F("/management/apiversions"),             HTTP_GET, handleMgmtVersions );
  server.on(F("/management/v1/description"),          HTTP_GET, handleMgmtDescription );
  server.on(F("/management/v1/configureddevices"),     HTTP_GET, handleMgmtConfiguredDevices );
  
  //Basic settings
  server.on(F("/status"),                              HTTP_GET, handlerStatus);
  server.on(F("/restart"),                             HTTP_ANY, handlerRestart); 
  server.on(F("/"), handlerStatus ); 
  server.onNotFound(handleNotFound);
       
  httpUpdater.setup(&server);
  Serial.println( "Setup webserver handlers");
  server.begin();
    
  //Setup timers for measurement loop
  //setup interrupt-based 'soft' alarm handler for periodic acquisition/recording of new measurements.
  ets_timer_setfn( &timer,        onTimer,        NULL ); 
  ets_timer_setfn( &timeoutTimer, onTimeoutTimer, NULL ); 
  
  //fire timer every 1000 msec
  //Set the timer function first
  ets_timer_arm_new( &timer, 1000, 1/*repeat*/, 1);
  //ets_timer_arm_new( &timeoutTimer, 2500, 0/*one-shot*/, 1);
  
  Serial.println( "Setup complete" );
}

//Timer handler for 'soft' interrupt timer. 
void onTimer( void * pArg )
{
  newDataFlag = true;
}

//Used to complete timeout actions. 
void onTimeoutTimer( void* pArg )
{
  //Read command list and apply. 
  timeoutFlag = true;
}

//Main processing loop
void loop()
{
  String timestamp;
  String output;
  static int loopCount = 0;
   
  if( newDataFlag == true )
  {
    //Serial.printf( "Time: %s \n", getTimeAsString2( timestamp ).c_str() );
    root["time"] = getTimeAsString2( timestamp );
    
    //MLX
    if( mlxPresent) 
    {
      ;//get next image
    }

    //Reset timing flag
    newDataFlag = false;
  }  

  //Handle web requests
  server.handleClient();

  if ( client.connected() )
  {
    //publish results
    if( callbackFlag == true )
    {
      publishMLX();
      publishHealth();
      callbackFlag = false;
    }
    client.loop();
  }
  else   //reconnect - using timers to handle async attempts.
  {
     reconnectNB();
     client.subscribe( inTopic );
  }   
}

/* MQTT callback for subscription and topic.
 * Only respond to valid states ""
 * Publish under ~/skybadger/sensors/<sensor type>/<host>
 * Note that messages have an maximum length limit of 18 bytes - set in the MQTT header file. 
 */
 void callback(char* topic, byte* payload, unsigned int length) 
 {  
  //set callback flag
  callbackFlag = true;  
 }

/*
 * Had to do a lot of work to get this to work 
 * Mostly around - 
 * length of output buffer
 * reset of output buffer between writing json strings otherwise it concatenates. 
 * Writing to serial output was essential.
 */
 void publishMLX( void )
 {
  String outTopic;
  String output;
  String timestamp;
  
  //publish to our device topic(s)
  DynamicJsonBuffer jsonBuffer(300);
  JsonObject& root = jsonBuffer.createObject();

  //checkTime();
  getTimeAsString2( timestamp );
  
  if (mlxPresent) 
  {
    output="";//reset
    root["time"] = timestamp;
    root["sensor"] = "MLX90640";
    root["SkyTemp"] = skyTemperature;

    outTopic = outSenseTopic;
    outTopic.concat("SkyTemperature/");
    outTopic.concat(myHostname);

    root.printTo( output );
    if ( client.publish( outTopic.c_str(), output.c_str(), true ) )        
      Serial.printf( "Published MLX90640 temperature sensor measurement %s to %s\n",  output.c_str(), outTopic.c_str() );
    else    
      Serial.printf( "Failed to publish MLX90640 Sky temperature sensor measurement %s to %s\n",  output.c_str(), outTopic.c_str() );
  }
 }
 
void publishHealth(void)
{
  String outTopic;
  String output;
  String timestamp;
  
  //checkTime();
  getTimeAsString2( timestamp );

  //Put a notice out regarding device health
  //publish to our device topic(s)
  DynamicJsonBuffer jsonBuffer(300);
  JsonObject& root = jsonBuffer.createObject();
  root["time"] = timestamp;
  root["hostname"] = myHostname;
  root["message"] = "Listening";
  root.printTo( output );
  outTopic = outHealthTopic;
  outTopic.concat( myHostname );  
  
  if ( client.publish( outTopic.c_str(), output.c_str(), true ) )
    Serial.printf( " Published health message: '%s' to %s\n",  output.c_str(), outTopic.c_str() );
  else
    Serial.printf( " Failed to publish health message: '%s' to %s\n",  output.c_str(), outTopic.c_str() );
  return;
}

uint32_t inline ICACHE_RAM_ATTR myGetCycleCount()
{
    uint32_t ccount;
    __asm__ __volatile__("esync; rsr %0,ccount":"=a" (ccount));
    return ccount;
}

void setup_wifi()
{
  int i=0;
  WiFi.mode(WIFI_STA);
  WiFi.hostname( myHostname );
  
  //WiFi.setOutputPower( 20.5F );//full power WiFi
  WiFi.begin(ssid2, password2 );
  Serial.print("Searching for WiFi..");
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
      Serial.print(".");
    if ( i++ > 400 )
      device.restart();
  }
  Serial.println("WiFi connected");
  Serial.printf("SSID: %s, RSSI %i dBm \n\r",  WiFi.SSID().c_str(), WiFi.RSSI() );
  Serial.printf("Hostname: %s\n\r",      WiFi.hostname().c_str() );
  Serial.printf("IP address: %s\n\r",    WiFi.localIP().toString().c_str() );
  Serial.printf("DNS address 0: %s\n\r", WiFi.dnsIP(0).toString().c_str() );
  Serial.printf("DNS address 1: %s\n\r", WiFi.dnsIP(1).toString().c_str() );

  //Setup sleep parameters
  //WiFi.mode(WIFI_NONE_SLEEP);
  wifi_set_sleep_type(NONE_SLEEP_T);
  //Still going to sleep after several hours of woking reliably. Thought it wwas a bad solder since it seemed to happen at night
  //So re-worked the solders and it happening in the morning. While it recovers afterwards, rather it didn't happen at all. 
  //Since it also happened to a partner device after a similar uptime - it could be an low level bug. Bith were rebuilt using lwip 1.4 HW after. 
  //wifi_set_sleep_type(LIGHT_SLEEP_T);

  delay(5000);
}
