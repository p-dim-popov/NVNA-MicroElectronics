#include <Arduino.h>
#define redLed 11
#define greenLed 9
#define sensorPin A0
#define BAUD_RATE 9600

double transformValueToVoltage(int value);
double transformVoltageToTempCelsius(double value);
void turnOnLed(int led);
void turnOffLed(int led);

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  double sensorValue = transformVoltageToTempCelsius(transformValueToVoltage(analogRead(sensorPin)));
  Serial.println(sensorValue);
}

double transformValueToVoltage(int value) {
  return (((double)value + 20.0) / 1023.0 * 5) - 0.1;
}

double transformVoltageToTempCelsius(double value) {
  return (value - 0.1) * (125 - (-40)) / (1.75 - 0.1) - 40;
}

void turnOnLed(int led) {
  digitalWrite(led, HIGH);
}
void turnOffLed(int led) {
  digitalWrite(led, LOW);
}