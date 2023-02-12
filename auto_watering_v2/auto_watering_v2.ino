const int sensorPin = A0;     // Pin connected to the soil moisture sensor
const int relayPin = 8;       // Pin connected to the relay
const int minPotPin = A1;     // Pin connected to the minimum threshold potentiometer
const int maxPotPin = A2;     // Pin connected to the maximum threshold potentiometer

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
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
}
