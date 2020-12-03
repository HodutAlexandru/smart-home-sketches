/*
 ESP8266 --> ThingSpeak Channel
 
 This sketch sends the Wi-Fi Signal Strength (RSSI) of an ESP8266 to a ThingSpeak
 channel using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).
 
 Requirements:
 
   * ESP8266 Wi-Fi Device
   * Arduino 1.8.8+ IDE
   * Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Library: esp8266 by ESP8266 Community
   * Library: ThingSpeak by MathWorks
 
 ThingSpeak Setup:
 
   * Sign Up for New User Account - https://thingspeak.com/users/sign_up
   * Create a new Channel by selecting Channels, My Channels, and then New Channel
   * Enable one field
   * Enter SECRET_CH_ID in "secrets.h"
   * Enter SECRET_WRITE_APIKEY in "secrets.h"
 Setup Wi-Fi:
  * Enter SECRET_SSID in "secrets.h"
  * Enter SECRET_PASS in "secrets.h"
  
 Tutorial: http://nothans.com/measure-wi-fi-signal-levels-with-the-esp8266-and-thingspeak
   
 Created: Feb 1, 2017 by Hans Scharler (http://nothans.com)
*/

#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

unsigned long channelNumber = <SECRET_CH_ID>; // to be replaced with real one
const char * apiKey = <SECRET_WRITE_APIKEY>; // to be replaced with real one

char ssid[] = SECRET_SSID;   // your network SSID (name) || to be replaced with real one
char pass[] = SECRET_PASS;   // your network password || to be replaced with real one

WiFiClient  client;

void setup() {
  init();
}

void loop() {

  // Trying to connect to WiFi
  wifiConnection();

  // Measure Signal Strength (RSSI) of Wi-Fi connection
  long rssi = WiFi.RSSI();

  // Write value to Field 1 of a ThingSpeak Channel
  int httpCode = ThingSpeak.writeField(channelNumber, 1, rssi, apiKey);

  if (httpCode == 200) {
    Serial.println("Write operation succsessfully done.");
  }
  else {
    Serial.println("Write operation fails. Http code: " + String(httpCode));
  }

  // Wait 20 seconds to update the channel again
  delay(20000);
}

void init() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

wifiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}
