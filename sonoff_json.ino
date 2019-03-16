/*
 * CUSTOM SONOFF FIRMWARE
 * Maxime MOREILLON
 * 
 * Board type: Generic ESP8266
 * Flash mode: DOUT
 * Flash size: 1M (64 SPIFFS)
 */


// Libraries
#include <ESP8266WiFi.h> // Main ESP8266 library
#include <ArduinoOTA.h> // OTA update library
#include <WiFiUdp.h> // Required for OTA
#include <PubSubClient.h>
#include <ArduinoJson.h>


#include "credentials.h";
//#include "sonoff_kitchen_light_nagoya.h";
//#include "sonoff_living_light_nagoya.h";
#include "sonoff_test.h";

// MQTT
#define MQTT_BROKER_ADDRESS IPAddress(192, 168, 1, 2)
#define MQTT_PORT 1883
#define MQTT_LAST_WILL "{'state':'disconnected'}"
#define MQTT_QOS 1
#define MQTT_RETAIN true

// Pin mapping
#define RELAY_PIN 12
#define LED_PIN 13
#define BUTTON_PIN 0

// Global variables
WiFiClient wifi_client;
PubSubClient MQTT_client(wifi_client);

char* relay_state = INITIAL_STATE;

void setup() {
  // Mandatory initial delay
  delay(10);

  // Serial init
  Serial.begin(115200);
  Serial.println(); // Separate serial stream from initial gibberish
  Serial.println(F(__FILE__ " " __DATE__ " " __TIME__));

  IO_setup();
  wifi_setup();
  MQTT_setup();
  OTA_setup();
}


void loop() {
  ArduinoOTA.handle();
  MQTT_client.loop();
  read_button();
  wifi_connection_manager();
  MQTT_connection_manager();
}
