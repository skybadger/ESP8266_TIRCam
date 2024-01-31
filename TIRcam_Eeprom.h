#if !defined _SQMEEPROM_H_
#define _SQMEEPROM_H_

#include "EEPROMAnything.h"

void setDefaults( void );
void saveToEeprom( void );
void setupFromEeprom( void );

void setDefaults ( void) 
{
  DEBUGSL1( "setDefaults: Entered ");

  lum = 0L;
  lux = 0.0F;
  ambientTemperature = 0.0F;
  skyTemperature = 0.0F;
  
  myHostname = (char*) calloc( sizeof(char), MAX_NAME_LENGTH );
  strcpy( myHostname, defaultHostname );

  thisID = (char*) calloc( sizeof(char), MAX_NAME_LENGTH );
  strcpy( thisID, myHostname );
  
  DEBUGSL1( "setDefaults: Exited ");
}

void saveToEeprom( void )
{
  int i = 0;
  int eepromAddr = 4;

  DEBUGSL1( "savetoEeprom: Entered ");
  
  //Constants  && variables

  //Strings
  //hostname
  EEPROMWriteString( eepromAddr, myHostname, MAX_NAME_LENGTH );
  eepromAddr += MAX_NAME_LENGTH;  
  DEBUGS1( "Written hostname: ");DEBUGSL1( myHostname );

  //MQTT ID
  strcpy( thisID, myHostname );

  EEPROM.put( 0, '*' );
  EEPROM.commit();

  //Test readback of contents
  char ch;
  String input;
  for (i=0; i< 100 ; i++ )
  {
    ch = (char) EEPROM.read( i );
    if ( ch == '\0' )
      ch = '_';
    input.concat( ch );
  }

  Serial.printf( "EEPROM contents: %s \n", input.c_str() );
}

void setupFromEeprom()
{
  int eepromAddr = 0;
  byte bTemp = 0;
  int i=0;
    
  DEBUGSL1( "setUpFromEeprom: Entering ");
  
  //Setup internal variables - read from EEPROM.
  bTemp = EEPROM.read( eepromAddr = 0 );
  DEBUGS1( "Read init byte: ");DEBUGSL1( (char) bTemp );
  if ( (byte) bTemp != '*' ) //initialise
  {
    setDefaults();
    saveToEeprom();
    DEBUGSL1( "Failed to find init byte - wrote defaults ");
    //Force a restart to load the saved vars
    device.restart();
    return;
  }    
    
  //Calibration constants

  //hostname - directly into variable array 
  if( myHostname != nullptr ) free ( myHostname );
  myHostname = (char*) calloc( sizeof(char), MAX_NAME_LENGTH );
  i = EEPROMReadString( eepromAddr = 4, myHostname, MAX_NAME_LENGTH );
  eepromAddr += MAX_NAME_LENGTH;
  
  DEBUGS1( "Read hostname: ");DEBUGSL1( myHostname );

  //MQTT ID  - copy hostname
  if( thisID != nullptr ) free (thisID);
  thisID = (char*) calloc( sizeof(char), MAX_NAME_LENGTH );
  strcpy( thisID, myHostname );
  
  DEBUGS1( "Read MQTT ID: ");DEBUGSL1( thisID );

  //Test readback of contents
  char ch;
  String input;
  for (i=0; i< 100 ; i++ )
  {
    ch = (char) EEPROM.read( i );
    if ( ch == '\0' )
      ch = '_';
    input.concat( ch );
  }
  DEBUGS1( "setupFromEeprom: exiting having read " );DEBUGS1( eepromAddr );DEBUGSL1( " bytes." );
}
#endif
