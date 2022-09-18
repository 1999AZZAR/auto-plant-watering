#include "config.h"

void setup()
{
  //begin serial
  Serial.begin(9600);

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
}

void loop()
{
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
    digitalWrite(relay, HIGH);
  } else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }
  delay(20);
}
