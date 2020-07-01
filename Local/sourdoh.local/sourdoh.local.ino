#include <time.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"

#define ProxTriggerPin  5
#define ProxEchoPin     4
#define DHTPIN          14

#define LOCAL_SSID      "{ssid}"
#define PASSWORD        "{pwd}"
#define HOST            "{host ip}"
#define PORT            1
#define READ_DELAY_MS   20000

char riseReading[200];

DHT dht(DHTPIN, DHT11);
WiFiClient client;

void setup()
{
  pinMode(ProxTriggerPin, OUTPUT); 
  pinMode(ProxEchoPin, INPUT); 
  dht.begin();  
  Serial.begin(9600);  
  initWifi();
}

void loop()
{
  sprintf(riseReading, "temperatureCelcius=%.2f&humidityPercent=%.2f&distance=%.ld", dht.readTemperature(), dht.readHumidity(), measureSampledDistance());   
  postLocalMessage(); 
  delay(READ_DELAY_MS);
}

void initWifi() 
{
  Serial.print("\r\n\r\nAttempting to connect to SSID: ");
  Serial.println(LOCAL_SSID);    
  WiFi.begin(LOCAL_SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }    
  Serial.println("\r\nConnected to wifi");
}

long measureSampledDistance()
{
  long measureSum = 0;
  for (int i = 0; i < 25; i++)
  {
    delay(5);
    measureSum += singleMeasurement();
  }
  return measureSum / 25;
}

long singleMeasurement()
{
  long duration = 0;
  digitalWrite(ProxTriggerPin, HIGH);
  delayMicroseconds(11);
  digitalWrite(ProxTriggerPin, LOW);
  duration = pulseIn(ProxEchoPin, HIGH);
  return (long) (((float) duration / 58.0) * 10.0);
}

void postLocalMessage()
{
  Serial.print("sending ");
  Serial.print(riseReadinging);
  Serial.print(" to ");
  Serial.println(HOST);
  
  if(client.connect(HOST, PORT)) 
  {
    int bodyLength = strlen(riseReading);
    client.println("POST /sourdoh HTTP/1.1");
    client.print("Host: "); 
    client.print(HOST);
    client.print(":");
    client.println(PORT);
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(bodyLength);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    client.print(riseReading);
    delay(100);
    while(client.read() != -1);
  }
}
