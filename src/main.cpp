#include <Arduino.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>
#include <WiFi.h>

//#ifdef ESP32   
//#endif
#define ONBOARD_LED 2
#define BAUD_RATE 9600
#define WIFI_SSID         "Little Nest"
#define WIFI_PASS         "zebraidea650"
#define APP_KEY    "6d5ce968-7153-48a1-88ac-545bfd4894df"    // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET "28620882-5b78-4f33-a24d-457d3771a95c-5f974a2e-f1b1-4cad-8ad9-3d9ca8a5ec93" // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID  "632910bcfa69c39e7cceb777"  // Should look like "5dc1564130xxxxxxxxxxxxxx"

bool onPowerState(const String &deviceId, bool &state) {
  printf("device %s turned %s\r\n", deviceId.c_str(), state?"on":"off");
  if(state)
    digitalWrite(ONBOARD_LED,HIGH);
  else
    digitalWrite(ONBOARD_LED,LOW);
  
  return true; // indicate that callback handled correctly
}

// setup function for WiFi connection
void setupWiFi() {
  printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    printf(".");
    delay(250);
  }
  }

  //printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str()); 
// ledPin refers to ESP32 GPIO 23
//const int ledPin = 23;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  Serial.begin(BAUD_RATE); printf("\r\n\r\n");
  setupWiFi();
 // create and add a switch to SinricPro
 SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];
 // set callback function
 mySwitch.onPowerState(onPowerState);
 // startup SinricPro
 SinricPro.begin(APP_KEY, APP_SECRET);
}

// the loop function runs over and over again forever
void loop() {
 SinricPro.handle();
}