#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;     // Pin connected to the soil moisture sensor
const int relayPin = 8;       // Pin connected to the relay
const int minPotPin = A1;     // Pin connected to the minimum threshold potentiometer
const int maxPotPin = A2;     // Pin connected to the maximum threshold potentiometer

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize the I2C 1602 display

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);

  lcd.init();       // initialize the lcd 
  lcd.backlight();  // Turn on the backlight
}

void loop() {
  int sensorValue = map(analogRead(sensorPin), 0, 1023, 0, 100);
  int minThreshold = map(analogRead(minPotPin), 0, 1023, 0, 100);
  int maxThreshold = map(analogRead(maxPotPin), 0, 1023, 0, 100);

  if (sensorValue < minThreshold) {
    digitalWrite(relayPin, HIGH);  // Turn the relay on
  } else if (sensorValue >= maxThreshold) {
    digitalWrite(relayPin, LOW);   // Turn the relay off
  }

  lcd.clear();  // Clear the display

  lcd.setCursor(0, 0);  // Set the cursor to the first row, first column
  lcd.print("Sensor: ");  // Print the label for the sensor value
  lcd.print(sensorValue);  // Print the sensor value
  lcd.print("%");  // Print the unit for the sensor value

  lcd.setCursor(0, 1);  // Set the cursor to the second row, first column
  lcd.print("Min: ");  // Print the label for the minimum threshold
  lcd.print(minThreshold);  // Print the minimum threshold
  lcd.print("%  Max: ");  // Print the label for the maximum threshold
  lcd.print(maxThreshold);  // Print the maximum threshold
  lcd.print("%");  // Print the unit for the threshold values

  delay(500); // Wait for 500 millisecondsy
}
