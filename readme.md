# Soil Moisture Sensor Relay Control using Arduino Nano
This code is written in the Arduino IDE and is used to control a relay using a soil moisture sensor and two potentiometers. The relay is turned on when the soil moisture level falls below a minimum threshold set by a potentiometer, and is turned off when the soil moisture level reaches a maximum threshold set by another potentiometer.

## Components
- Arduino Nano
- Relay module
- Soil moisture sensor
- 2 potentiometers (for setting the minimum and maximum thresholds)

## Circuit Diagram
Please refer to the previous explanation for the circuit diagram and connections.

## Code Explanation
- The code starts by setting the sensorPin and relayPin as inputs and outputs, respectively, using the pinMode function in the setup function.
- In the loop function, the soil moisture sensor reading is first read using analogRead(sensorPin) and then mapped to a value between 0 and 100 using the map function. The same process is repeated for the readings from the two potentiometers (minimum and maximum thresholds).
- Next, an if-else statement is used to compare the soil moisture value with the minimum and maximum thresholds. If the soil moisture value is less than the minimum threshold, the relay is turned on by setting the relayPin to HIGH. If the soil moisture value is greater than or equal to the maximum threshold, the relay is turned off by setting the relayPin to LOW.

## Usage
1. Connect the components as described in the circuit diagram.
2. Open the code in the Arduino IDE and upload it to the Arduino Nano.
3. Adjust the potentiometers to set the minimum and maximum thresholds for the soil moisture level.
4. Observe the relay turning on and off based on the soil moisture level.

## Note
Ensure that the connections and circuit diagram are correct before uploading the code to the Arduino Nano.
The relay module and potentiometers used in this project may differ from the ones mentioned in the code, so ensure that the pin numbers used in the code match the components used.

## Conclusion
By following this guide, you can control a relay using a soil moisture sensor and two potentiometers. This can be used for watering plants automatically or for any other application where you need to control a device based on soil moisture level.
