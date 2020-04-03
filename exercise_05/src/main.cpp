#include <Arduino.h>

#define potentiometer A0
#define led 9
int sensorValue = 0;
int outputValue = 0;
int lastValue;
int maxValue = 0;
int minValue = 1023;

double sensorValueToVoltage(int scale, int voltage, int sensorValue);

void setup()
{
  pinMode(potentiometer, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lastValue = analogRead(potentiometer);
}

void loop()
{
  sensorValue = analogRead(potentiometer);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(led, outputValue);
  if (sensorValue > maxValue){
    maxValue = sensorValue;
  }
  if (sensorValue < minValue){
    minValue = sensorValue;
  }

  if (lastValue != sensorValue) {
    if (sensorValue > lastValue) {
      Serial.println("Value increases!");
    } else Serial.println("Values decreases!");

    lastValue = sensorValue;
    Serial.print("sensor = ");
    Serial.print(sensorValueToVoltage(1023.0, 5.0, sensorValue));
    Serial.println('V');
    Serial.print("Max value: ");
    Serial.println(sensorValueToVoltage(1023.0, 5.0, maxValue));
    Serial.print("Min value: ");
    Serial.println(sensorValueToVoltage(1023.0, 5.0, minValue));
    Serial.println();
  }
}

double sensorValueToVoltage(double scale, double voltage, int sensorValue){
  return (sensorValue / scale) * voltage;
}
