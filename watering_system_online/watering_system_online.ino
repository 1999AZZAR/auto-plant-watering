#include "config.h"

void setup()
{
  //begin serial
  Serial.begin(115200);
  delay(10);
  mqtt.subscribe(&Pump);

  //pin mode
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(relay, OUTPUT);

  //initial value
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);

  //relay active low
  //digitalWrite(relay, HIGH);
  //relay active hi
  digitalWrite(relay, LOW);

  //Adding the WiFi networks to the MultiWiFi instance
  wifi_multi.addAP(ssid1, password1);
  wifi_multi.addAP(ssid2, password2);
  wifi_multi.addAP(ssid3, password3);

  //Wait for ESP8266 to scan the local area and connect with the strongest of the networks defined above
  Serial.print("Connecting to Wi-Fi...");
  while (wifi_multi.run(connectTimeOutPerAP) != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  MQTT_connect();
  unsigned long currentTime = millis();
  Adafruit_MQTT_Subscribe * subscription;
  while ((subscription = mqtt.readSubscription()))
  {
    if (subscription == &Pump)  //subscribe data
    {
      Serial.print(F("Got: "));
      Serial.println((char*) Pump.lastread);

      if (!strcmp((char*) Pump.lastread, "0"))
      {
        //relay active low
        //digitalWrite(relay, HIGH);
        //relay active hi
        digitalWrite(relay, LOW);
      }
      if (!strcmp((char*) Pump.lastread, "1"))
      {
        //relay active low
        //digitalWrite(relay, LOW);
        //relay active hi
        digitalWrite(relay, HIGH);
      }

    }
  }

  //pinout config in sensor
  int sensorValue = analogRead(A0);
  byte mappedValue = map(sensorValue, 400, 1024, 100, 0);
  Serial.println(mappedValue);
  //tweaking some inconsistan reading value
  if (mappedValue > 100) {
    mappedValue = 100;
  }

  //for builtin led notification system
  if (mappedValue > 3 && mappedValue <= 20)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (mappedValue > 20 && mappedValue <= 40) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (mappedValue > 40 && mappedValue <= 60) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  } else if (mappedValue > 60 && mappedValue <= 80) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
  } else if (mappedValue > 80 && mappedValue <= 100) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  if (currentTime - previousTime >= eventInterval) {
    //pinout config in sensor
    int sensorValue = analogRead(A0);
    byte mappedValue = map(sensorValue, 400, 1024, 100, 0);
    Serial.println(mappedValue);
    //tweaking some inconsistan reading value
    if (mappedValue > 100) {
      mappedValue = 100;
    }
    //publising data
    if (! AgricultureData.publish(mappedValue)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
    previousTime = currentTime;
  }
  delay(20);
}

void MQTT_connect()
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected())
  {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {

    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
}
