<h2>ESP8266_TIRcam </h2>
<p>This applicaiton creates a web-server REST ALPACA client for a MELEXIS 90640 Thermal IR camera sensor accessed over a over WiFi connection.</p>
<p>This application runs on the ESP8266-01 wifi-enabled SoC device to capture thermal IR image sensor readings and transmit them to the local MQTT service. 
In my arrangement, Node-red flows are used to listen for and graph the updated readings in the dashboard UI. 
The unit is setup for I2C operation and is expecting to see SCL on GPIO0 and SDA on GPIO2. </p>

<p>The Thermal IR imaging sensor used is the MLX90640 which is set to auto range to keep flux readings sensibly high
The u.timate purpose of this implementation is to provide a whole-sky temperature sensor to suport an observatory by allowing the determination of whether its clear or not. </p>

<h3>Dependencies:</h3>
<ul>
<li>Arduino 1.8, </li>
<li>ESP8266 V2.4+ lwip1.9hb </li>
<li>Arduino MQTT client (https://pubsubclient.knolleary.net/api.html)<li>
<li>Arduino MLX90640 library </li>
<li>Arduino JSON library (v5.13) </li></ul>

<h3>Testing</h3>
Access by serial port  - Tx only is available from device at 115,600 baud at 3.3v. THis provides debug output .
Wifi is used for MQTT reporting only and servicing web requests
Use http://ESPTIR01 to receive json-formatted output of current sensors. 

<h3>Use:</h3>
I use mine to source a dashboard via hosting the mqtt server in node-red. It runs off a solar-panel supply in my observatory dome. 

<h3>ToDo:</h3>
Complete functional
