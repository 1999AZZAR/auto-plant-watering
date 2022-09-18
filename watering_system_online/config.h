//lib config
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//pinout config out control
int led1 = D0;
int led2 = D1;
int led3 = D2;
int led4 = D3;
int led5 = D6;
int relay = D7;

//Defining the instance of ESP8266MultiWifi
WiFiClient client;
ESP8266WiFiMulti wifi_multi;

//wifi connectionn config
//WiFi 1
const char* ssid1 = "ora_bayar";
const char* password1 = "password";

//WiFi 2
const char* ssid2 = "android_ap";
const char* password2 = "12345678";

//WiFi 3
const char* ssid3 = "xiaomi";
const char* password3 = "87654321";

//timeout config
uint16_t connectTimeOutPerAP = 5000;

//millis timing
const unsigned long eventInterval = 3000; //1000 for 1s
unsigned long previousTime = 0;

//adafruit config
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "your_aio_username"
#define AIO_KEY         "your_aio_key"

//Set up the adafruit mqtt client
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
//Set up the feed you're publishing to
Adafruit_MQTT_Publish AgricultureData = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/sensor.soil");
//Set up the feed you're subscribing to
Adafruit_MQTT_Subscribe Pump = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/relay4");
