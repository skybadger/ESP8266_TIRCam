#if ! defined _ESP8266_TIRCamHandlers_h_
#define _ESP8266_TIRCamHandlers_h_

#include "TIRCam_eeprom.h"
#include <Wire.h>
#include "AlpacaErrorConsts.h"
#include "ASCOMAPICamera_rest.h"
#include "Skybadger_common_funcs.h" //for hasArgIC
#include "JSONHelperFunctions.h"

  extern ESP8266WebServer server;

  //ASCOM handlers
  //Can.. capability handlers
  void handlerGenericGetCapabilityHandler( void )
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGenericCapabilityHandler" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  
  //use with regex url handler registration
  int devNum = server.pathArg(0);
  string capability = server.pathArg(1);
  
  if( mlxPresent )
  {
      switch( capability )//cant uae strings here as argument to switch. suggests that should use a hash map of capability to value and read/write that direct. 
      {
        case "GetCanAbortExposure": 
          root["Value"] = (boolean) CanAbortExposure;      
          break;
        
      }
      errCode = Success;
      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F(capability), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading %s ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", capability, clientID, transID, root["Value"], errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
   
  void handlerGetCanAbortExposure( void )
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanAbortExposure" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) CanAbortExposure;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("CanAbortExposure"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canAbortExposure, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
  
  void handlerGetCanAsymmetricBin( void )
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanAsymmetricBin" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) canAsymmetricBin;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("CanAsymmetricBin"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canAsymmetricBin, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
  
  void handlerGetCanFastReadout(void)
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanFastReadout" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) canFastReadout;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCanFastReadout"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading canFastReadout ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canFastReadout, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

  void handlerGetCanGetCoolerPower(void)
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanGetCoolerPower" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) canGetCoolerPower;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCanGetCoolerPower"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canGetCoolerPower, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

  void handlerGetCanPulseGuide(void)
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanPulseGuide" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) canPulseGuide;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("CanPulseGuide"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, CanPulseGuide, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

  void handlerGetCanSetCCDTemperature(void)
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCanSetCCDTemperature" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) canSetCCDTemperature;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCanSetCCDTemperature"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading canSetCCDTemperature ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, CanSetCCDTemperature, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

  void handlerGetExposureCanStop(void)
  {
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureCanStop" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) CanAbortExposure;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetExposureCanStop"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canAbortExposure, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
  
  //Get handlers
// ​/camera​/{device_number}​/bayeroffsetx
//Returns the X offset of the Bayer matrix.
void handlerGetBayerOffsetX( void )
{
    String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetBayerOffsetX" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) bayerOffsetX;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetBayerOffsetX"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, bayerOffsetX, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/bayeroffsety
//Returns the Y offset of the Bayer matrix.
void handlerGetBayerOffsetY(void)
{
    String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetBayerOffsetY" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) bayerOffsetY;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetBayerOffsetY"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, GetBayerOffsetY, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
}

// ​/camera​/{device_number}​/binx
//Returns the binning factor for the X axis.
void handlerGetBinX(void)
{  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetBinX" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) binX;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetBinX"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, getBinX, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/biny
//Returns the binning factor for the Y axis.
void handlerGetBinY(void)
{
    String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetBinY" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) binY;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetBinY"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, getBinY, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
}

/​/camera​/{device_number}​/camerastate
//Returns the camera operational state.
void handlerGetCameraState(void)
{
    String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCameraState" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) cameraState;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCameraState"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCameraState ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, cameraState, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
}

/​/camera​/{device_number}​/cameraxsize
/Returns the width of the CCD camera chip.
void handlerGetCameraXSize(void)
{
    String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCameraXSize" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) cameraXSize;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCameraXSize"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCameraXSize ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, cameraXSize, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
}

/​/camera​/{device_number}​/cameraysize
//Returns the height of the CCD camera chip.
void handlerGetCameraYSize(void)
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCameraYSize" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) cameraYSize;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCameraYSize"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCameraYSize ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, cameraYSize, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​
//camera​/{device_number}​/ccdtemperature
//Returns the current CCD temperature
void handlerGetCCDTemperature(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCCDTemperature" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int ) ccdTemperature;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCCDTemperature"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCCDTemperature ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, ccdTemperature, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/cooleron
//Returns the current cooler on/off state.
void handlerGetCoolerOn(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCoolerOn" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) coolerOn;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCoolerOn"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCoolerOn ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, coolerOn, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
//camera​/{device_number}​/coolerpower
//Returns the present cooler power level
void handlerGetCoolerPower(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCoolerPower" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) coolerPower;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCoolerPower"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getCoolerPower ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, coolerPower, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​
//camera​/{device_number}​/electronsperadu
//Returns the gain of the camera
void handlerGetElectronsPerADU(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetElectronsPerADU" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (double) electronsPerADU;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetElectronsPerADU"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getelectronsPerADU ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, electronsPerADU, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
  ​
//camera​/{device_number}​/exposuremax
//Returns the maximum exposure time supported by StartExposure.
void handlerGetExposureMax(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureMax" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) exposureMax;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetExposureMax"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getExposureMax( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, exposureMax, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
//camera​/{device_number}​/exposuremin
//Returns the Minimium exposure time
void handlerGetExposureMin(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureMin" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) exposureMin;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetExposureMin"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading GetExposureMin ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, exposureMin, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
//camera​/{device_number}​/exposureresolution
//Returns the smallest increment in exposure time supported by StartExposure.
void handlerGetExposureResolution(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureResolution" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) exposureResolution;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetExposureResolution"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading GetExposureResolution ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, exposureResolution, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
//camera​/{device_number}​/fastreadout
//Returns whenther Fast Readout Mode is enabled.
void handlerGetFastReadout(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetFastReadout" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) fastReadout;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetFastReadout"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading fastReadout ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, fastReadout, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​//camera​/{device_number}​/fullwellcapacity
//Reports the full well capacity of the camera
void handlerGetFullWellCapacity(void)
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetFullWellCapacity" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) fullWellCapacity;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetFullWellCapacity"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading fullWellCapacity ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, fullWellCapacity, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

//camera​/{device_number}​/gain
//Returns the camera's gain
void handlerGetGain(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetGain" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) gain;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetGain"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getGain ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, gain, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/gainmax
//Maximum Gain value of that this camera supports
void handlerGetGainMax(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetGainMax" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) gainMax;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetGainMax"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getGainMax ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, gainMax, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/gainmin
//Minimum Gain value of that this camera supports
void handlerGetGainMin()
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetGainMin" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) gainMin;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetGainMin"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getGainMin ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, gainMin, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/gains
//List of Gain names supported by the camera
void handlerGetGains(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetGains" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      //Create new json array of return values. 
      /*
      for ( i=0;i< sizeof( gainNames ); i++ )
      {
        arr.addItem( gains[i]);
      }
      root.addItem( arr) //return array of gain label strings
      */
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetGains"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  //concatenate array of names into a single string. 
  String sTemp = new String();
  for ( i=0;i< sizeof( gainNames ); i++ )
  {
    sTemp += gains[i];
    debugD( "Reading getGains ( client %d trans %d ) resulted in value %s, code: %d, error: '%s'", clientID, transID, sTemp, errCode, errMsg.c_str() );    
  }
  
  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/hasshutter
//Indicates whether the camera has a mechanical shutter
void handlerGetHasShutter(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetHasShutter" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) hasShutter;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetHasShutter"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading hasShutter ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, hasShutter, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​//camera​/{device_number}​/heatsinktemperature
//Returns the current heat sink temperature.
void handlerGetHeatSinktemperature(void)  
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetHeatSinktemperature" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) heatSinkTemperature;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetHeatSinktemperature"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading heatSinkTemperature ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, heatSinkTemperature, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/imagearray
//Returns an array of integers containing the exposure pixel values
void handlerGetImageArray(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetImageArray" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      
      /*
      ArrItem arr = jsonBuffer.ArrItem();
      arr.AddItem
      other stuff

      */
      root["Value"] = arr;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetImageArray"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getImageArray ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, imageArray, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/imagearrayvariant
//Returns an array of int containing the exposure pixel values
void handlerGetImageArrayVariant(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetImageArrayVariant" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      /*
      root.Value = arr;      
      */
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetImageArrayVariant"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getImageArrayVariant ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
//camera​/{device_number}​/imageready
//Indicates that an image is ready to be downloaded
void handlerGetImageReady(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetImageReady" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) imageReady;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetImageReady"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getImageready ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, imageReady, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

/​/camera​/{device_number}​/ispulseguiding
//Indicates that the camera is pulse guideing.
​void handlerGetIsPulseGuiding(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetIsPulseGuiding" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      //root["Value"] = (boolean) CanAbortExposure;   
      errCode = notImplemented;  
      errMsg = F("pulseGuiding not implemented");            
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetIsPulseGuiding"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading isPulseGuiding ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

//camera​/{device_number}​/lastexposureduration
//Duration of the last exposure
void handlerGetLastExposureDuration(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetLastExposureDuration" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) lastExposureDuration;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetLastExposureDuration"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading lastExposureDuration ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, lastExposureDuration, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/lastexposurestarttime
// Start time of the last exposure in FITS standard format.
void handlerGetLastExposureStartTime(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetLastExposureStartTime" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (long int) lastExposureStartTime;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetLastExposureStartTime"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getLastExposureStartTime ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, lastExposureStartTime, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
​
// /camera​/{device_number}​/maxadu
// Camera's maximum ADU value
void handlerGetMaxADU(void)
{
​
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetMaxADU" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) maxADU;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetMaxADU"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getMaxADU ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, maxADU, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// /camera​/{device_number}​/maxbinx
// Maximum binning for the camera X axis
void handlerGetMaxBinX(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetMaxBinX" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) maxBinX;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetMaxBinX"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading GetMaxBinX ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, maxBinX , errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/maxbiny
// Maximum binning for the camera Y axis
void handlerGetMaxBinY(void)
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetMaxBinY" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) maxBinY;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetMaxBinY"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getMaxBinY ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, maxBinY, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// /camera​/{device_number}​/numx
// Returns the current subframe width
void handlerGetSubframeWidth(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetSubframeWidth" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );

  int subFramewidths[2] = { cameraXSize/binX ,cameraYSize/binY };
  if( mlxPresent )
  {
      root["Value"] = (boolean) CanAbortExposure;      

  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetSubframeWidth"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getSubFrameWidth ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/numy
// Returns the current subframe height
void handlerGetSubframeHeight(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureCanStop" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) CanAbortExposure;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCanAbortExposure"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canAbortExposure, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/offset
// Returns the camera's offset
void handlerGetOffset(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetOffset" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) offset;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetOffset"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getOffset ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, offset, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/offsetmax
// Maximum offset value of that this camera supports
void handlerGetOffsetMax(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetOffsetMax" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) offsetMax;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetOffsetMax"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading hetOffsetMax ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, offsetMax, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }
 
​// /camera​/{device_number}​/offsetmin
// Minimum offset value of that this camera supports
void handlerGetOffsetMin(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetOffsetMin" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) offsetMin;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetOffsetMin"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getOffsetMin ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, offsetMin, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/offsets
// List of offset names supported by the camera
void handlerGetOffsets(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetOffsets" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );

  String sTemp = new String();
  for ( int i=0;i< sizeof(offsetNames); i++ )
  {
    sTemp += offsetNames[i];
    sTemp += "|";
  }

  if( mlxPresent )
  {
      /* create a json arr for array entries 
      ArrItem arr= jsonBuffer.Array();
      for ( int i= 0; i< sizeof( offsetNames); i++ ) 
        arr.addItem( offsetNames[i]);
      root["Value"] = arr;
      */
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetOffsets"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %s, code: %d, error: '%s'", clientID, transID, c_str( sTemp), errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/percentcompleted
// Indicates percentage completeness of the current operation
void handlerGetPercentageComplete(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetPercentageComplete" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) percentCompleted;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetPercentageComplete"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getPercentageComplete ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, percentCompleted, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/pixelsizex
// Width of CCD chip pixels (microns)
// ​/camera​/{device_number}​/pixelsizey
// Height of CCD chip pixels (microns)
void handlerGetPixelSize(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetPixelSizeX" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );

  //use with regex url handler registration
  String whichPix = server.pathArg(0);
  int index = 0;
  if( whichPix.length == 1 ) 
  {
    if ( whichPix.equals("x") || whichPix.equal("X")
      index = 1;
    else if ( whichPix.equals("y") || whichPix.equals("Y") )
      index = 2;
  }

  if( mlxPresent )
  {
    switch(index) 
    {
      case 1: root["Value"] = (float) pixelSizeX; 
              debugD( "Reading getPixelSize ( client %d trans %d ) resulted in value %f for index %i, code: %d, error: '%s'", clientID, transID, pixelSizeX, index, errCode, errMsg.c_str() );
              break;
      case 2: root["Value"] = (float) pixelSizey; 
              debugD( "Reading getPixelSize ( client %d trans %d ) resulted in value %f for index %i, code: %d, error: '%s'", clientID, transID, pixelSizeY, index, errCode, errMsg.c_str() );
              break;
      case 0: 
      default:
            errCode = notConnected;  
            errMsg = F("X or Y dimension required not detected");         
            root["Message"] = "X or Y dimension required not detected";  
            debugD( "Reading getPixelSize ( client %d trans %d ) failed for index %i, code: %d, error: '%s'", clientID, transID, index, errCode, errMsg.c_str() );            
            break;
    }   
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetPixelSize"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  //debugD( "Reading getPixelSize ( client %d trans %d ) resulted in value %f for index %i, code: %d, error: '%s'", clientID, transID, pixelSizeX, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }


​// /camera​/{device_number}​/readoutmode
// Indicates the canera's readout mode as an index into the array ReadoutModes
void handlerGetReadoutMode(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetReadoutMode" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) readoutMode;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetReadoutMode"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getReadoutMode ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, readoutMode, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/readoutmodes
// List of available readout modes
void handlerGetReadoutModes(void)
{
  +String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetReadoutModes" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  
  String sTemp = new String();
  for ( int i=0;i< sizeof(readoutModes); i++ )
  {
    sTemp += offsetNames[i];
    sTemp += "|";
  }

  if( mlxPresent )
  {
      /* create a json arr for array entries 
      ArrItem arr= jsonBuffer.Array();
      for ( int i= 0; i< sizeof( readoutModes); i++ ) 
        arr.addItem( offsetNames[i]);
      root["Value"] = arr;
      */
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetReadoutModes"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getReadoutModes ( client %d trans %d ) resulted in value %s, code: %d, error: '%s'", clientID, transID, c_str(sTemp), errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/sensorname
//Sensor name
void handlerGetSensorName(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetSensorName" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = c_str( sensorName );
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetSensorName"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getSensorName ( client %d trans %d ) resulted in value %s, code: %d, error: '%s'", clientID, transID, c_str(sensorName), errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/sensortype
// Type of information returned by the the camera sensor (monochrome or colour)
void handlerGetSensorType(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetSensorType" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (int) sensorType;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetSensorType"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getSensorType ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, sensorType, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

// ​/camera​/{device_number}​/setccdtemperature
//Returns the current camera cooler setpoint in degrees Celsius.
void handlerGetCCDTemperatureSetpoint(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetCCDTemperatureSetpoint" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      if( !canSetCCDTemperature )
      {
        root["Message"] = "Cannot set/get sensor temperature on this sensor";
        errCode = notImplemented;
        errMsg = F"(Not implemented on this device");
        debugD( "Reading getCCDTemperatureSetPoint ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, sensorTemperatureSetpoint, errCode, errMsg.c_str() );
      }
      else
      {
        root["Value"] = (float) sensorTemperatureSetpoint;      
        debugD( "Reading getCCDTemperatureSetPoint ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() );
      }
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
      debugD( "Reading getCCDTemperatureSetPoint ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() );
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCCDTemperatureSetpoint"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  //debugD( "Reading getCCDTemperatureSetPoint ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, sensorTemperatureSetpoint, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/startx
// Return the current subframe X axis start position
// camera​/{device_number}​/starty
// Return the current subframe Y axis start position
//void handlerGetStartY(void)
//void handlerGetStartX(void)
void handlerGetStart(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetStartX" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );

  //use with regex url handler registration
  String whichPix = server.pathArg(0);
  int index = 0;
  if( whichPix.length == 1 ) 
  {
    if ( whichPix.toLower().equals("x") )
      index = 1;
    else if ( whichPix.toLower().equals("y") )
      index = 2;
  }

  if( mlxPresent )
  {
      switch( index) 
      {
        case 1: root["Value"] = (int) startX;
                debugD( "Reading getStartX ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, startX, errCode, errMsg.c_str() );
                break;
        case 2: root["Value"] = (int) startX;
                debugD( "Reading getStartX ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, startY, errCode, errMsg.c_str() );
                break;
        case 0: 
        default:
                errCode = notConnected;  
                errMsg = F("Unable to detect pixel axis in URL");         
                root["Message"] = "Unable to detect pixel axis in URL";  
                debugD( "Reading getStart ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() ); 
                break;
      }
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
      debugD( "Reading getStart ( client %d trans %d ) resulted in code: %d, error: '%s'", clientID, transID, errCode, errMsg.c_str() ); 
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetStartX"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  //debugD( "Reading getStartX ( client %d trans %d ) resulted in value %i, code: %d, error: '%s'", clientID, transID, startX, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }


​// /camera​/{device_number}​/subexposureduration
//Camera's sub-exposure interval
void handlerGetSubExposure(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetSubExposure" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (float) subExposureDuration;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetSubExposure"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading getSubExposureDuration ( client %d trans %d ) resulted in value %f, code: %d, error: '%s'", clientID, transID, subExposureDuration, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

//PUT ----------------------------------------------------------------------------------------------------------------------------------------------
// ​/camera​/{device_number}​/binx
// Sets the binning factor for the X axis.
//void handlerPutBinFactorX(void)
//void handlerPutBinFactorY(void)
void handlerPutBinFactor(void)
{
  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerPutBinFactor" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      //Process
      //Create new list item of CMD type
      //Add variable to of binFactor after checks 
      //Set CMD to update
      root["Value"] = (boolean) true;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerPutBinFactorX"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, binFactorX, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }


​// /camera​/{device_number}​/cooleron
// Turns the camera cooler on and off
void handlerPutCoolerEnabled(void)  String errMsg = "";
  int errCode = Success;
  
  DEBUGSL1( "Entered handlerGetExposureCanStop" );
  String timeString = "";
  String message = "";

  uint32_t clientID= -1;
  uint32_t transID = -1;

  String argToSearchFor[] = { "clientID", "ClientTransactionID", };
  if( hasArgIC( argToSearchFor[0], server, false ) )
    clientID = server.arg(argToSearchFor[0]).toInt();
    
  if ( hasArgIC( argToSearchFor[1], server, false) )
    transID = server.arg(argToSearchFor[1]).toInt();

  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
      root["Value"] = (boolean) CanAbortExposure;      
  }
  else
  {
      errCode = notConnected;  
      errMsg = F("Device not present");         
      root["Message"] = "MLX90640 sensor not present";  
  }
  jsonResponseBuilder( root, clientID, transID, ++serverTransID, F("handlerGetCanAbortExposure"), errCode , errMsg );       

  //root.printTo( Serial );Serial.println(" ");
  debugD( "Reading CanAbortExposure ( client %d trans %d ) resulted in value %b, code: %d, error: '%s'", clientID, transID, canAbortExposure, errCode, errMsg.c_str() );

  root.printTo(message);
  server.send( returnCode, F("application/json"), message);
  return;
  }

​// /camera​/{device_number}​/fastreadout
//Sets whether Fast Readout Mode is enabled.
void handlerPutReadoutMode(void);

// ​/camera​/{device_number}​/gain
//Sets the camera's gain.
void handlerPutGain(void);

// ​/camera​/{device_number}​/numx
//Sets the current subframe width
void handlerPutSubframeX(void);

// ​/camera​/{device_number}​/numy
//Sets the current subframe height
void handlerPutSubframeY(void);

​// /camera​/{device_number}​/offset
//Sets the camera's offset.
void handlerPutOffset(void);

// ​/camera​/{device_number}​/setccdtemperature
// Set the camera's cooler setpoint (degrees Celsius).
void handlerPutCCDTemperature(void);

​// /camera​/{device_number}​/startx
//Sets the current subframe X axis start position
void handlerPutStartX(void);

​// /camera​/{device_number}​/starty
//Sets the current subframe Y axis start position
void handlerPutStartY(void);

​// /camera​/{device_number}​/subexposureduration
// Sets the current Sub Exposure Duration
void handlerPutSubExposureDuration(void);

​// /camera​/{device_number}​/abortexposure
// Aborts the current exposure
void handlerPutAbortExposure(void);

// ​/camera​/{device_number}​/pulseguide
// Pulse guide in the specified direction for the specified time.
void handlerPutPulseGuide(void);

// ​/camera​/{device_number}​/startexposure
//Starts an exposure
void handlerPutStartExposure(void );

// ​/camera​/{device_number}​/stopexposure
//Stops the current exposure
void handlerPutStopExposure ( void );

  //Put handlers

  //Multi handlers
  
  //Private handlers
  String& setupFormBuilder( String& htmlForm, String& errMsg );
  void handleRestart( void );
  void handleStatusGet( void);
  void handleRoot(void);
  void handleNotFound();
  void handleSkyTempGet( void );
  
  //ToDo
  

/*********************************************************************************************************************/
//Private handlers used for setup not in the ASCOM API. 
/*
 * Handler to update the hostname
 * Causes the MQTT ID to be reset after restart. 
 */ 
void handleHostnamePut( void ) 
{
  String form;
  String errMsg;
  String newName;
  String argToSearchFor = "hostname";
  
  DEBUGSL1 (errMsg);
  DEBUGSL1( "Entered handleHostnamePut" );
  
  //Whether PUT or GET or POST, the argument will be found in the arg list 
  if( hasArgIC( argToSearchFor, server, false ) )
  {
    newName = server.arg( argToSearchFor );
    Serial.printf( "handleHostnamePut: found new %s - %s\n", argToSearchFor.c_str(), server.arg( argToSearchFor ).c_str() ); 
    DEBUGS1( "handleHostnamePut: found new hostname - " );    
    DEBUGSL1 ( server.arg( argToSearchFor ).c_str() );
    DEBUGSL1 ( newName.c_str() );

    if( newName.length() > 0 && newName.length() < MAX_NAME_LENGTH )
    {
      String redirectUri;
      String redirectHeader = "http://";
      
    DEBUGS1( "handleHostnamePut: new hostname is valid - length:" );
    DEBUGSL1 ( newName.length() );

      //save new hostname and cause reboot - requires eeprom read at setup to be in place.  
      strcpy( myHostname, newName.c_str() );
      redirectHeader.concat( myHostname );

      //Write new hostname to EEprom
      saveToEeprom();
    DEBUGS1( "handleHostnamePut: updated myHostname & saved to EEprom - " );
    DEBUGSL1 ( myHostname );
     
      //Send redirect response 
      redirectUri = "<!doctype html><html><meta></meta><body><p>New url: <a href=\"http://";
      redirectUri.concat( myHostname );
      redirectUri.concat( "\"><p>http://" );
      redirectUri.concat( myHostname );
      redirectUri.concat( "</p> </a></body></html>" );
      server.sendHeader( String( "Location"), redirectHeader );      
      server.send( 301, "text/html", redirectUri ); 
      device.restart();
    }
    else
    {
      errMsg = "handleHostnamePut: Error handling new hostname";
      form = setupFormBuilder( form, errMsg );
      server.send( 200, "text/html", form ); 
    }
  }
  else //Its a get with no arguments - why would we return the current hostname ?
  {
    ;//Going to ignore anything else. 
    server.send( 403, "text/plain", "forbidden" ); 
  }
}
 
void handleRestart( void )
{
  server.send( 205, "text/plain", "restarting");      
  device.reset();
  return;
}

void handleSkyTempGet( void )
{
  String timeString = "", message = "";
  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
    root["Sky Temperature"] = (float[]) skyTemperature;
  }
  else
    root["Message"] = "MLX90640 sensor not present";

  root.printTo( Serial );Serial.println(" ");
  root.printTo(message);
  server.send(200, "application/json", message);      
}

void handleStatusGet( void)
{
  String timeString = "", message = "";
  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();
  //Update the error message handling.
  // JsonArray errors = root.createArray( "errors" );
  
  root["time"] = getTimeAsString2( timeString );
  if( mlxPresent )
  {
    root["Sky image"] = (float[]) skyTemperature;
    root["Ambient Temperature"] = (float) ambientTemperature;
  }
  else
    root["MLXStatus"] = "MLX90640 sensor not present";
 
  root.printTo( Serial ); Serial.println(" ");
  root.prettyPrintTo( message );
  server.send(200, "application/json", message);  
}

   /*
   * Web server handler functions
   * Move into a setup page and add forms controls for calibration settings and hostname
   * Maybe turn on/off whihc data is reported ?
   */
  void handleNotFound()
  {
  String message = "<!Doctype html><html><body><h1>URL not found </h1>";
  //String UriTerminal = 
  message.concat( "<ul>");
  
  //Status
  message.concat ( "<li><p>Simple status read: <a href=\"http://");
  message.concat ( myHostname );
  message.concat ( "/status\"> http://");
  message.concat ( myHostname );
  message.concat ( "/status </a></p></li>");
  
  //Restart
  message.concat ( "<li><p>SQM Restart: <a href=\"http://");
  message.concat ( myHostname );
  message.concat ( "/restart\"> http://");
  message.concat ( myHostname );
  message.concat ( "/restart</a></p></li>");

  //Hostname
  message.concat ( "<li><p>SQM Hostname change: <a href=\"http://");
  message.concat ( myHostname );
  message.concat ( "/hostname\"> http://" );
  message.concat ( myHostname );
  message.concat ( "/hostname (PUT)</a></p></li>");
 
  //Setup
  message.concat ( "<li><p>SQM Setup: <a href=\"http://");
  message.concat ( myHostname );
  message.concat ( "/setup\"> http://");
  message.concat ( myHostname );
  message.concat ( "/setup</a></p></li>");

  message.concat ( "</ul></body></html>");  
  server.send(404, "text/html", message);
}
 
//Return sensor status
void handleRoot()
{
  String timeString = "", message = "";
  DynamicJsonBuffer jsonBuffer(256);
  JsonObject& root = jsonBuffer.createObject();

  root["time"] = getTimeAsString2( timeString );
  //Todo add skyTemp and SQM reading here
  
  //root.printTo( Serial );
  root.printTo(message);
  server.send(200, "application/json", message);
}

//Return sensor status
void handleSetupGet()
{
  String message = "";
  String form = "";

  form = setupFormBuilder( form, message );
  server.send(200, "text/html", form );
}
/*
 * Handler for setup dialog - issue call to <hostname>/setup and receive a webpage
 * Fill in form and submit and handler for each form button will store the variables and return the same page.
 optimise to something like this:
 https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/
 Bear in mind HTML standard doesn't support use of PUT in forms and changes it to GET so arguments get sent in plain sight as 
 part of the URL.
 */
String& setupFormBuilder( String& htmlForm, String& errMsg )
{
  htmlForm = "<!DOCTYPE HTML><html><head>";
  htmlForm += "<style> \
  fieldset {\n\
    width: 250px;\n\
    box-sizing: border-box;\n\
    margin-left: 136px;\n\
    border: 1px solid #999;\n\
  }</style>";
  htmlForm += "</head><meta></meta><body><div id=\"ErrorMsg\" >\n";
  if( errMsg != NULL && errMsg.length() > 0 ) 
  {
    htmlForm +="<b background='red' >";
    htmlForm.concat( errMsg );
    htmlForm += "</b>";
  }
  htmlForm += "</div>\n";
  
  //Hostname
  htmlForm += "<div id=\"hostnameset\" >";
  htmlForm += "<h2 halign=\"center\"> Change settings for SQM Meter </h2>\n";
  htmlForm += "<form action=\"http://";
  htmlForm.concat( myHostname );
  htmlForm += "/hostname\" method=\"PUT\" id=\"hostname\" >\n";
  htmlForm += "Changing the hostname will cause the SQM hardware to reboot and may change the address!\n<br>";
  htmlForm += "<fieldset>";
  htmlForm += "<legend>Setup hostname</legend>";
  htmlForm += "<label for=\"hostname\"><span>Hostname</span></label>";
  htmlForm += "<input type=\"text\" name=\"hostname\" maxlength=\"25\" value=\"";
  htmlForm.concat( myHostname );
  htmlForm += "\"><br>";
  htmlForm += "<input type=\"submit\" value=\"submit\">";
  htmlForm += "</fieldset>";
  htmlForm += "</form></div>";
  
  //SQM Cal constants
  htmlForm += "<div id=\"calset\" >";
  htmlForm += "<form action=\"http://";
  htmlForm.concat( myHostname );
  htmlForm += "/calibrate\" method=\"PUT\" id=\"calibrate\" >\n";
  htmlForm += "<fieldset>";
  htmlForm += "<legend>Setup Calibration constants</legend>";
  
  htmlForm += "<label for=\"rootcal\"><span>Crossing point </span></label>";
  htmlForm += "<input type=\"number\" id=\"rootcal\" name=\"rootcal\" value=\"";
  htmlForm += String(sqmRootCal);
  htmlForm += "\"><br>";
  
  htmlForm += "<label for=\"gradCal\"> <span>Gradient </span></label>";
  htmlForm += "<input type=\"number\" min=\"-5\" max=\"5\" id=\"gradCal\" value=\"";
  htmlForm += String( sqmGradientCal );
  htmlForm += "\"><br>";
  
  htmlForm += "<label for=\"offCal\"> <span>Offset constant </span></label>";
  htmlForm += "<input type=\"number\" min=\"-10.0\" max=\"10.0\" id=\"offCal\" value=\"";
  htmlForm += String( sqmOffsetCal );
  htmlForm += "\"><br>";

  htmlForm += "<input type=\"submit\" value=\"submit\">\n</form></div>\n";
  htmlForm += "</fieldset>";    
  htmlForm += "</form>";
  
  htmlForm += "</body>\n</html>\n";
  return htmlForm;
}
#endif
