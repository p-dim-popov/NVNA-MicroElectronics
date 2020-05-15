#include <Arduino.h>
#define redLed 11
#define greenLed 9
#define sensorPin A0
#define BAUD_RATE 9600
#define LOWER_TEMP_BOUND 0
#define HIGHER_TEMP_BOUND 40
#define HOT 1
#define COLD -1
#define NORMAL 0
#define FIRST_TIME lastSensorValue == -1
#define MEANINGFUL_CHANGE 0.0001
#define SENSOR_MAX 1023
#define SENSOR_MIN 0
#define IS ==
#define IS_MORE_THAN >


int lastSensorValue = -1;
int maxSensorValue = SENSOR_MIN;
int minSensorValue = SENSOR_MAX;

double transformValueToVoltage(int value);
double transformVoltageToTempCelsius(double value);
void turnOnLed(int led);
void turnOffLed(int led);
int8_t checkTempStatus(double temp);
void printInfo();

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  maxSensorValue = sensorValue > maxSensorValue ? sensorValue : maxSensorValue;
  minSensorValue = sensorValue < minSensorValue ? sensorValue : minSensorValue;
  lastSensorValue = FIRST_TIME ? sensorValue : lastSensorValue;
  double sensorVoltage = transformValueToVoltage(sensorValue);
  double sensorTemperature = transformVoltageToTempCelsius(sensorVoltage);
  int8_t sensorTemperatureStatus = checkTempStatus(sensorTemperature);

  if (sensorTemperatureStatus IS COLD)
  {
    turnOffLed(redLed);
    turnOnLed(greenLed);
  }
  else if(sensorTemperatureStatus IS HOT){
    turnOffLed(greenLed);
    turnOnLed(redLed);
  }
  else {
    turnOffLed(redLed);
    turnOffLed(greenLed);
  }
  
  if (abs(sensorValue - lastSensorValue) IS_MORE_THAN MEANINGFUL_CHANGE)
  {
    printDataForTemperatureTendencies(sensorValue, sensorVoltage, sensorTemperature, lastSensorValue);
    Serial.println();
  }

  lastSensorValue = sensorValue;
}

void printDataForTemperatureTendencies(int sensorValue, double sensorVoltage, double sensorTemperature, int lastSensorValue){
    Serial.print("Sensor value: ");
    Serial.print(sensorValue);
    Serial.print(", Voltage: ");
    Serial.print(sensorVoltage);
    Serial.print(", Temperature: ");
    Serial.println(sensorTemperature);
    Serial.print("Last sensor value: ");
    Serial.print(lastSensorValue);
    Serial.print(", Last voltage: ");
    Serial.print(transformValueToVoltage(lastSensorValue));
    Serial.print(", Last temperature: ");
    Serial.println(transformVoltageToTempCelsius(transformValueToVoltage(lastSensorValue)));
    Serial.print("Max temp: ");
    Serial.print(transformVoltageToTempCelsius(transformValueToVoltage(maxSensorValue)));
    Serial.print(", Min temp: ");
    Serial.println(transformVoltageToTempCelsius(transformValueToVoltage(minSensorValue)));

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

int8_t checkTempStatus(double temp){
  return temp < LOWER_TEMP_BOUND 
    ? COLD 
    : temp > HIGHER_TEMP_BOUND 
      ? HOT 
      : NORMAL; 
}