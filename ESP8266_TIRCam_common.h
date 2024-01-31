/*
ASCOM project common variables
*/
#ifndef _WEBTIRCAM_COMMON_H_
#define _WEBTIRCAM_COMMON_H_

//#define _REVERSE_READOUT_ORDER
#if defined _REVERSE_READOUT_ORDER_
const bool reverseReadoutOrder = true;
#else
const bool reverseReadoutOrder = false;
#endif

//ASCOM driver common descriptor variables 
unsigned int transactionId;
int connectionCtr = 0; //variable to count number of times something has connected compared to disconnected. 
unsigned int connected = (unsigned int) 0; //NOT_CONNECTED;
#define ALPACA_DISCOVERY_PORT 32227
int udpPort = ALPACA_DISCOVERY_PORT;
static const char* PROGMEM DriverName = "Skybadger.ESPTIRCam";
static const char* PROGMEM DriverVersion = "0.0.1";
static const char* PROGMEM DriverInfo = "Skybadger.ESPTIRCam RESTful native device. ";
static const char* PROGMEM Description = "Skybadger ESP2866-based wireless ASCOM Thermal camera";
static const char* PROGMEM InterfaceVersion = "2";
static const char* PROGMEM DriverType = "Camera";

static const char* GUID PROGMEM = "0013-0000-0000-0000";
//espcam00 GUID - "0013-0000-0000-0000"; //prototype & demo

//Strings
const char* defaultHostname = "espCam00";
char* myHostname = nullptr;

//MQTT settings
char* thisID = nullptr;

#define ASCOM_DEVICE_TYPE "camera" //used in server handler uris
//Instance defines which driver of the type it is at this IP address. Its almost always 0 unless you are running more than one switch, cover or filter/focuser 
//from a single device
const int defaultInstanceNumber = 0;
int instanceNumber = defaultInstanceNumber;
String preUri = "/api/v1/" + String( ASCOM_DEVICE_TYPE ) + "/" + String( instanceNumber) + "/";

//Mgmt Api Constants
const int instanceVersion = 3; //the iteration version identifier for this driver. Update every major change - relate to your repo versioning
char* Location = nullptr;

#define TZ              0       // (utc+) TZ in hours
#define DST_MN          00      // use 60mn for summer time in some countries
#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

//Pin limits
const int NULLPIN = -1; 
#if defined ESP8266_01
const int MINPIN = 0; //device specific
const int MAXPIN = 3; //device specific

//GPIO 0 is Serial tx, GPIO 2 I2C SDA, GPIO 1 SCL, so it depends on whether you use i2c or not.
//Cos that just leaves Rx at GPIO3 and external power circuitry is required. 
//In the case of the switch device as a dew heater controller, use 2 switch and 1 pwm pin to control all heater outputs.  
//This means GPIO 3 needs connecting to both switching outputs. 
const int pinMap[] = { 1, 3, NULLPIN }; 
#elif defined ESP8266_12
const int MINPIN = 0; //device specific
const int MAXPIN = 16; //device specific

//Most pins are used for flash, so we assume those for SSI are available.
//Typically use 4 and 5 for I2C, leaves 
const int pinMap[] = { 2, 14, 12, 13, 15, NULLPIN };
#else
const int pinMap[] = {NULLPIN};
#endif 

#endif
