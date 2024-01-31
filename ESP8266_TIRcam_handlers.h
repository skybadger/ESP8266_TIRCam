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
  void handlerGetCanAbortExposure );
  void handlerGetCanAsymmetricBin );
  void handlerGetCanFastReadout(void);
  void handlerGetCanGetCoolerPower(void);
  void handlerGetCanPulseGuide(void);
  void handlerGetCanSetCCDTemperature(void);
  void handlerGetCanStopExposure(void);
  
  //Get handlers

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
  
  //Skytemp
  message.concat ( "<li><p>Sky temperature read: <a href=\"http://");
  message.concat ( myHostname );
  message.concat ( "/skytemp\"> http://");
  message.concat ( myHostname );
  message.concat ( "/skytemp </a></p></li>");
  
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
