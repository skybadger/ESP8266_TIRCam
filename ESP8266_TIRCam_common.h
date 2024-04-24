/*
ASCOM project common variables
*/
#ifndef _TIRCAM_COMMON_H_
#define _TIRCAM_COMMON_H_

//#define _REVERSE_READOUT_ORDER
#if defined _REVERSE_READOUT_ORDER_
const bool reverseReadoutOrder = true;
#else
const bool reverseReadoutOrder = false;
#endif

#if !defined MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 25
#endif

#if defined _USE_EEPROM_
char* myHostname             = nullptr;
char* thisID                 = nullptr;
#else
const char* defaultHostname = "espCam00";
char* myHostname = nullptr;
//MQTT settings
char* thisID = nullptr;
#endif

#define ASCOM_DEVICE_TYPE "camera" //used in server handler uris
//Instance defines which driver of the type it is at this IP address. Its almost always 0 unless you are running more than one switch, cover or filter/focuser 
//from a single device
const int defaultInstanceNumber = 0;
int instanceNumber = defaultInstanceNumber;
String preUri = "/api/v1/" + String( ASCOM_DEVICE_TYPE ) + "/" + String( instanceNumber) + "/";

//Mgmt Api Constants
const int instanceVersion = 0; //the iteration version identifier for this driver. Update every major change - relate to your repo versioning
char* Location = nullptr;

#define TZ              0       // (utc+) TZ in hours
#define DST_MN          00      // use 60mn for summer time in some countries
#define TZ_MN           ((TZ)*60)
#define TZ_SEC          ((TZ)*3600)
#define DST_SEC         ((DST_MN)*60)

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

#include <time.h>

//#define _REVERSE_READOUT_ORDER
#if defined _REVERSE_READOUT_ORDER_
const bool reverseReadoutOrder = true;
#else
const bool reverseReadoutOrder = false;
#endif

//ASCOM Properties
enum CameraStates { CAMERA_IDLE, CAMERA_WAITING, CAMERA_EXPOSING, CAMERA_READING, CAMERA_DOWNLOAD, CAMERA_ERROR };
const char* cameraStatech[] = { "camera idle", "camera waiting", "camera exposing", "cameras reading", "camera download", "camera error",  };
CameraStates cameraState = CAMERA_IDLE ;
CameraStates targetCameraState = CAMERA_IDLE ;

enum CameraCmds { CAM_NONE, CAM_EXP_START, CAM_EXP_STOP, CAM_EXP_ABORT, CAM_UPDATE };
CameraCmds cameraCmd = CAM_NONE; 

bool connected = NOT_CONNECTED;
bool imageReady = false;

/*
May throw a not implemented exception if this camera does not support PulseGuide
This method returns only after the move has completed.
The (symbolic) values for GuideDirections are: 
guideNorth 0 North (+ declination/elevation)
guideSouth 1 South (- declination/elevation)
guideEast 2 East (+ right ascension/azimuth)
guideWest 3 West (+ right ascension/azimuth)
*/
bool isPulseGuiding = false;
bool imageReady = false;

//Image parameters
int bayerOffsetX = 0, bayerOffsetY = 0;
int binX = 1, binY = 1; 
int*** imageArray; //(colour plane, X - row, column y)
int maxBinX = 1;                    // Returns the maximum allowed binning for the X camera axis  
int maxBinY = 1;                    //Returns the maximum allowed binning for the Y camera axis  
int numX = 32;                       //Sets the subframe width. Also returns the current value.  
int numY = 28;                       //Sets the subframe height. Also returns the current value.  
int startX = 0, startY = 0;          //Sets the subframe start position for the X axis (0 based) and returns the current value.  

//What about framesize as determined by numPixels/bin ratio ? 

/*
This is an optional property and can throw a PropertyNotImplementedException if Gain is not supported by the camera.
The Gain property is used to adjust the gain setting of the camera and has two modes of operation: 
GAIN VALUE MODE - The Gain property is a direct numeric representation of the camera's gain. 
In this mode the GainMin and GainMax properties must return integers specifying the valid range for Gain
The Gains property must return a PropertyNotImplementedException.
GAINS INDEX MODE - The Gain property is the selected gain's index within the Gains array of textual gain descriptions. 
In this mode the Gains method returns a 0-based array of strings, which describe available gain settings e.g. "ISO 200", "ISO 1600" 
GainMin and GainMax must throw PropertyNotImplementedExceptions.
Please note that the Gains array is zero based.
*/
//Gain
float gain = 1.0;
float gainMax = 256.0; 
float gainMin = 1.0;
char** gainNames;
int** gainPresets;
float electronsPerADU = 0.0F;

//Cooling parameters
float heatSinkTemperature = 0.0F;
float sensorTemperatureSetpoint = 0.0F; // Sets the camera cooler setpoint in degrees Celsius, and returns the current setpoint.  
int   sensorTemperature = 0;
bool  coolerOn = false;
int   coolerPower = 0; //%

//Exposure control
int    percentCompleted = 0;           //Percent completed, Interface Version 2 only  
float  lastExposureDuration = 0.0F;  //Reports the actual exposure duration in seconds (i.e. shutter open time).  
long int lastExposureStartTime = 0; //Reports the actual exposure start in the FITS-standard CCYY-MM-DDThh:mm:ss[.sss...] format. The start time must be UTC.  
float  exposureResolution = 0.001;

/*
This is an optional property and can throw a PropertyNotImplementedException if Offset is not supported by the camera.
The Offset property is used to adjust the offset setting of the camera and has two modes of operation: 
OFFSET VALUE MODE - The Offset property is a direct numeric representation of the camera's offset. 
In this mode the OffsetMin and OffsetMax properties must return integers specifying the valid range for Offset
The Offsets property must return a PropertyNotImplementedException.
OFFSETS INDEX MODE - The Offset property is the selected offset's index within the Offsets array of textual offset descriptions. 
In this mode the Offsets method returns a 0-based array of strings, which describe available offset settings e.g. "ISO 200", "ISO 1600" 
OffsetMin and OffsetMax must throw PropertyNotImplementedExceptions.
Please note that the Offsets array is zero based.
A driver can support none, one or both offset modes depending on the camera's capabilities. However, only one mode can be active at any one moment because both modes share the Offset property to return the offset value. Client applications can determine which mode is operational by reading the OffsetMin, OffsetMax and Offset properties. If a property can be read then its associated mode is active, if it throws a PropertyNotImplementedException then the mode is not active
*/
int offset = 0;                     // The camera's offset (OFFSET VALUE MODE) OR the index of the selected camera offset description in the Offsets array (OFFSETS INDEX MODE)  
int offsetMax = 0;                  //Maximum Offset value of that this camera supports  
int offsetMin = 0;                  //Minimum Offset value of that this camera supports  
char** offsetNames = nullptr;       //List of Offset names supported by the camera  

/*
This is an optional property and can throw a PropertyNotImplementedException if Offset is not supported by the camera.
Must be implemented if CanFastReadout is false, must throw a PropertyNotImplementedException if CanFastReadout is true.
ReadoutMode is an index into the array ReadoutModes, and selects the desired readout mode for the camera. Defaults to 0 if not set. Throws an exception if the selected mode is not available. 
It is strongly recommended, but not required, that driver authors make the 0-index mode suitable for standard imaging operations, since it is the default.
Please see ReadoutModes for additional information.
This is only available for the Camera Interface Version 2
*/
int   readoutMode = 0;                //Readout mode, Interface Version 2 only  
char** ReadoutModes  = nullptr;     //List of available readout modes, Interface Version 2 only  
char* sensorName = nullptr;         //Interface version 2 only. Must return empty string if name is unknown. 
int   sensorType = 0;                 // Type of colour information returned by the camera sensor, Interface Version 2 only  
int   cameraXSize = 32, cameraYSize = 28; 
int   maxADU = 0;                     //Reports the maximum ADU value the camera can produce.  
float exposureMax = 64.0;
float exposureMin = 0.0F;
bool  fastReadout = false;
float fullWellCapacity = 0;
float pixelSizeX = 0.0F; pixelSizeY = 0.0F;  // Returns the width of the CCD chip pixels in microns.  
float subExposureDuration = 0.0F;    // Camera's sub-exposure interval  

//capabilities
bool canAbortExposure = false;
bool canAsymmetricBin = false;
bool canGetCoolerPower = false;
bool canFastReadout = false;
bool canPulseGuide = false;
bool canSetCCDTemperature = false;
bool canStopExposure = false;
bool hasShutter = false;

#endif
