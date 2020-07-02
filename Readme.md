# Sourdoh
Simple Arduino build with NodeMCU ESP8266, DHT11 temperature and humidity sensor, and SR04 proximity sensor. 
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
