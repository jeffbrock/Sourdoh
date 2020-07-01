#include <time.h>
#include <ESP8266WiFi.h>
#include <AzureIoTHub.h>
#include <AzureIoTProtocol_HTTP.h>
#include "DHT.h"

#define MIN_EPOCH 40 * 365 * 24 * 3600

#define ProxTriggerPin 5
#define ProxEchoPin 4
#define DHTPIN 14

#define IOT_CONFIG_WIFI_SSID            ""
#define IOT_CONFIG_WIFI_PASSWORD        ""
#define IOT_CONFIG_CONNECTION_STRING    ""

char iotHubMessage[200];

DHT dht(DHTPIN, DHT11);
IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = nullptr;

void setup()
{
  pinMode(ProxTriggerPin, OUTPUT); 
  pinMode(ProxEchoPin, INPUT); 
  dht.begin();
  
  Serial.begin(9600);
  
  initWifi();
  initTime();
  initAzureHandle();
}

void loop()
{
  sprintf(iotHubMessage, "{ 'humidity': %.2f,'temperature':%.2f, 'distance':%.ld }", dht.readHumidity(), dht.readTemperature(), measureSampledDistance()); 
  Serial.print("Sending iotHubMessage: ");
  Serial.println(iotHubMessage);
  sendAzureIotiotHubMessage(); 
  delay(20000);
}

void initWifi() 
{
    Serial.print("\r\n\r\nAttempting to connect to SSID: ");
    Serial.println(IOT_CONFIG_WIFI_SSID);    
    WiFi.begin(IOT_CONFIG_WIFI_SSID, IOT_CONFIG_WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }    
    Serial.println("\r\nConnected to wifi");
}

static void initTime() 
{  
  time_t epochTime;
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (true) {
    epochTime = time(NULL);
    if (epochTime < MIN_EPOCH) {
      Serial.println("Fetching NTP epoch time failed! Waiting 2 seconds to retry.");
      delay(2000);
    } else {
      Serial.print("Fetched NTP epoch time is: ");
      Serial.println(epochTime);
      break;
    }
  }
}

void initAzureHandle()
{
  iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(IOT_CONFIG_CONNECTION_STRING, HTTP_Protocol);
  if (iotHubClientHandle == NULL)
  {
    Serial.println("Failed on IoTHubClient_LL_Create");
  }
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

void sendAzureIotiotHubMessage()
{
  IOTHUB_iotHubMessage_HANDLE iotHubMessageHandle = IoTHubiotHubMessage_CreateFromByteArray((const unsigned char *)iotHubMessage, strlen(iotHubMessage));
  if (iotHubMessageHandle == NULL)
  {
    Serial.println("unable to create a new IoTHubiotHubMessage");
  }
  else
  {                           
    if (IoTHubClient_LL_SendEventAsync(iotHubClientHandle, iotHubMessageHandle, nullptr, nullptr) != IOTHUB_CLIENT_OK)
    {
      Serial.println("failed to hand over the iotHubMessage to IoTHubClient");
    }
    IoTHubiotHubMessage_Destroy(iotHubMessageHandle);
  }

  IOTHUB_CLIENT_STATUS status;
  while ((IoTHubClient_LL_GetSendStatus(iotHubClientHandle, &status) == IOTHUB_CLIENT_OK) && (status == IOTHUB_CLIENT_SEND_STATUS_BUSY))
  {
    IoTHubClient_LL_DoWork(iotHubClientHandle);
    ThreadAPI_Sleep(100);
  }
}
