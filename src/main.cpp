#include <Arduino.h>

// Pins
constexpr int sensorPin1 = A2;
constexpr int sensorPin2 = A3;

constexpr int buzzer = 0;
constexpr int fullLED = 1;

/** The minimum value the ADC can read before throwing the alarm */
constexpr int minVoltageVal = 1024 * (3.3f / 5.f);

/** The highest possible value the ADC should measure */
constexpr int maxVoltageVal = 1024 * (4.2f / 5.f);

/** The midpoint of the voltage */
constexpr int midVoltageVal = (maxVoltageVal - minVoltageVal) / 2 + minVoltageVal;

void setup() {
    pinMode(buzzer, OUTPUT);
    pinMode(fullLED, OUTPUT);
}

void loop() {
    const int sensor1 = analogRead(sensorPin1);
    const int sensor2 = analogRead(sensorPin2);

    const int average = (sensor1 + sensor2) / 2;
    digitalWrite(fullLED, average > midVoltageVal ? HIGH : LOW);

    // Sound buzzer in danger zone
    digitalWrite(buzzer, sensor1 < minVoltageVal || sensor2 < minVoltageVal ? HIGH : LOW);
    delay(500);
}
