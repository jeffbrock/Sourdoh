# Sourdoh
Simple Arduino build with **NodeMCU ESP8266**, **DHT11** temperature and humidity sensor, and **SR04** proximity sensor. 
Sends results to Azure Iot Hub (`sourdoh.azureiot`) or to a local Rest service (`sourdoh.local` and `sourdoh.api`).

#### Wiring
* Power
  * Vin to Pos
  * GRD to Neg
* DHT11 Temp and Humidity Sensor, pins left to right looking at sensor side
  * Neg to GRD 
  * Pos to Vin
  * sensor to D5 (GPIO14)
* SR04 Proximity Sensor, pins left to right looking at the top of the board
  * Pos to Vin*
  * Trigger to D1 (GPIO5)
  * Echo to D2 (GPIO5)
  * Neg to GRD
  
![NodeMCU ESP8266](https://github.com/jeffbrock/sourdoh/blob/master/readme/NodeMCU%20GPIOs.png?raw=true)

#### Build
* Screw on jar cap, crude holes cut with utility knife, secured with shoe goo ;)

![Build](https://github.com/jeffbrock/sourdoh/blob/master/readme/IMG_20200702_081934.jpg)

#### Code
* Arduino IDE 1.8.13 (https://www.arduino.cc/)
  * NodeMCU Board Manager (http://arduino.esp8266.com/stable/package_esp8266com_index.json)
  * DHT Sensor Library 1.3.10
* Azure Hub Version - `sourdoh.azureiot`
  * Requires:
    * AzureIoTHub 1.0.45
    * AzureIoTProtocol_HTTP 1.0.45
    * AzureIoTUtility 1.0.4.5
  * Set variables:
    * IOT_CONFIG_WIFI_SSID            
    * IOT_CONFIG_WIFI_PASSWORD        
    * IOT_CONFIG_CONNECTION_STRING    
* Local Rest Version - `sourdoh.local` and `sourdoh.api`
  * Set variables:
    * LOCAL_SSID
    * PASSWORD
    * HOST
    * PORT
