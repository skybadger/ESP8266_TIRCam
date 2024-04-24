/*
File to be included into relevant device REST setup 
*/
//Assumes Use of ARDUINO ESP8266WebServer for entry handlers
#if !defined _ASCOMAPICamera_rest_h_
#define _ASCOMAPICamera_rest_h_

//Can
/​/camera​/{device_number}​/canabortexposure
//Indicates whether the camera can abort exposures.
void handlerGetCanAbortExposure(void);

/​/camera​/{device_number}​/canasymmetricbin
//Indicates whether the camera supports asymmetric binning
void handlerGetcanAsymmetricBin(void);

/​/camera​/{device_number}​/canfastreadout
//Indicates whether the camera has a fast readout mode.
void handlerGetCanFastReadout(void);
​
//camera​/{device_number}​/cangetcoolerpower
//Indicates whether the camera's cooler power setting can be read.
void handlerGetCanGetCoolerPower(void);
​
//camera​/{device_number}​/canpulseguide
//Returns a flag indicating whether this camera supports pulse guiding
void handlerGetCanPulseGuide(void);
​
//camera​/{device_number}​/cansetccdtemperature
//Returns a flag indicating whether this camera supports setting the CCD temperature
void handlerGetCanSetCCDTemperature(void);
​
//camera​/{device_number}​/canstopexposure
//Returns a flag indicating whether this camera can stop an exposure that is in progress
void handlerGetCanStopExposure(void);

//GET
// ​/camera​/{device_number}​/bayeroffsetx
//Returns the X offset of the Bayer matrix.
void handlerGetBayerOffsetX( void ); 

// ​/camera​/{device_number}​/bayeroffsety
//Returns the Y offset of the Bayer matrix.
void handlerGetBayerOffsetY(void);

// ​/camera​/{device_number}​/binx
//Returns the binning factor for the X axis.
void handlerGetBinX(void);

// ​/camera​/{device_number}​/biny
//Returns the binning factor for the Y axis.
void handlerGetBinY(void);

/​/camera​/{device_number}​/camerastate
//Returns the camera operational state.
void handlerGetCameraState(void);

/​/camera​/{device_number}​/cameraxsize
/Returns the width of the CCD camera chip.
void handlerGetCameraXSize(void);

/​/camera​/{device_number}​/cameraysize
//Returns the height of the CCD camera chip.
void handlerGetCameraYSize(void);

​
//camera​/{device_number}​/ccdtemperature
//Returns the current CCD temperature
void handlerGetCCDTemperature(void);

/​/camera​/{device_number}​/cooleron
//Returns the current cooler on/off state.
void handlerGetCoolerOn(void);
​
//camera​/{device_number}​/coolerpower
//Returns the present cooler power level
void handlerGetCoolerPower(void);
​
//camera​/{device_number}​/electronsperadu
//Returns the gain of the camera
void handlerGetElectronsPerADU(void);
​
//camera​/{device_number}​/exposuremax
//Returns the maximum exposure time supported by StartExposure.
void handlerGetExposureMax(void);
​
//camera​/{device_number}​/exposuremin
//Returns the Minimium exposure time
void handlerGetExposureMin(void);
​
//camera​/{device_number}​/exposureresolution
//Returns the smallest increment in exposure time supported by StartExposure.
void handlerGetExposureResolution(void);
​
//camera​/{device_number}​/fastreadout
//Returns whenther Fast Readout Mode is enabled.
void handlerGetFastReadout(void);

​//camera​/{device_number}​/fullwellcapacity
//Reports the full well capacity of the camera
void handlerGetFullWellCapacity(void);​

//camera​/{device_number}​/gain
//Returns the camera's gain
void handlerGetGain(void);

/​/camera​/{device_number}​/gainmax
//Maximum Gain value of that this camera supports
void handlerGetGainMax(void);

/​/camera​/{device_number}​/gainmin
//Minimum Gain value of that this camera supports
void handlerGetGainMin();

/​/camera​/{device_number}​/gains
//List of Gain names supported by the camera
void handlerGetGains(void);

/​/camera​/{device_number}​/hasshutter
//Indicates whether the camera has a mechanical shutter
void handlerGetHasShutter(void);

​//camera​/{device_number}​/heatsinktemperature
//Returns the current heat sink temperature.
void handlerGetHeatSinktemperature(void);

/​/camera​/{device_number}​/imagearray
//Returns an array of integers containing the exposure pixel values
void handlerGetImageArray(void);

/​/camera​/{device_number}​/imagearrayvariant
//Returns an array of int containing the exposure pixel values
void handlerGetImageArrayVariant(void);
​
//camera​/{device_number}​/imageready
//Indicates that an image is ready to be downloaded
void handlerGetImageReady(void);

/​/camera​/{device_number}​/ispulseguiding
//Indicates that the camera is pulse guideing.
​void handlerGetIsPulseGuiding(void);

//camera​/{device_number}​/lastexposureduration
//Duration of the last exposure
void handlerGetLastExposureDuration(void);

​// /camera​/{device_number}​/lastexposurestarttime
// Start time of the last exposure in FITS standard format.
void handlerGetLastExposureStartTime(void);
​
// /camera​/{device_number}​/maxadu
// Camera's maximum ADU value
void handlerGetMaxADU(void);
​
// /camera​/{device_number}​/maxbinx
// Maximum binning for the camera X axis
void handlerGetMaxBinX(void);

// ​/camera​/{device_number}​/maxbiny
// Maximum binning for the camera Y axis
void handlerGetMaxBinY(void);

// /camera​/{device_number}​/numx
// Returns the current subframe width
void handlerGetSubframeWidth(void);

// ​/camera​/{device_number}​/numy
// Returns the current subframe height
void handlerGetSubframeHeight(void);

​// /camera​/{device_number}​/offset
// Returns the camera's offset
void handlerGetOffset(void);

​// /camera​/{device_number}​/offsetmax
// Maximum offset value of that this camera supports
void handlerGetOffsetMax(void);
 
​// /camera​/{device_number}​/offsetmin
// Minimum offset value of that this camera supports
void handlerGetOffsetMin(void);

​// /camera​/{device_number}​/offsets
// List of offset names supported by the camera
void handlerGetOffsets(void);

// ​/camera​/{device_number}​/percentcompleted
// Indicates percentage completeness of the current operation
void handlerGetPercentageComplete(void);

​// /camera​/{device_number}​/pixelsizex
// Width of CCD chip pixels (microns)
void handlerGetPixelSizeX(void);

// ​/camera​/{device_number}​/pixelsizey
// Height of CCD chip pixels (microns)
void handlerGetPixelSizeY(void);

​// /camera​/{device_number}​/readoutmode
// Indicates the canera's readout mode as an index into the array ReadoutModes
void handlerGetReadoutMode(void);

​// /camera​/{device_number}​/readoutmodes
// List of available readout modes
void handlerGetReadoutModes(void);

​// /camera​/{device_number}​/sensorname
//Sensor name
void handlerGetSensorName(void);

​// /camera​/{device_number}​/sensortype
// Type of information returned by the the camera sensor (monochrome or colour)
void handlerGetSensorType(void);

// ​/camera​/{device_number}​/setccdtemperature
//Returns the current camera cooler setpoint in degrees Celsius.
void handlerGetCCDTemperatureSetpoint(void);

​// /camera​/{device_number}​/startx
// Return the current subframe X axis start position
void handlerGetStartX(void);

​// /camera​/{device_number}​/starty
//Return the current subframe Y axis start position
void handlerGetSubExposure(void);

​// /camera​/{device_number}​/subexposureduration
//Camera's sub-exposure interval
void handlerGetSubExposure(void);

//PUT
// ​/camera​/{device_number}​/binx
// Sets the binning factor for the X axis.
void handlerPutBinFactorX(void);

​// /camera​/{device_number}​/biny
// Sets the binning factor for the Y axis.
void handlerPutBinFactorY(void);

​// /camera​/{device_number}​/cooleron
// Turns the camera cooler on and off
void handlerPutCoolerEnabled(void);

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

#endif
