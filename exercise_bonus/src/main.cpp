#include <Arduino.h>
#define redLed 13
#define yellowLed 10
#define greenLed 6
#define oneSecond 1000

String mode = "normal";
int trafficLightState = 0;
uint32_t millisState = 0;

void turnOnLed(const int& led){
  digitalWrite(led, HIGH);
}

bool isLedOn(const uint8_t& led){
  return digitalRead(led);
}

void turnOffLed(const int& led){
  digitalWrite(led, LOW);
}

void normalWork();
void trafficLightWorking(){
  if (mode == "normal")
    normalWork();
  
}

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  trafficLightWorking();
}


uint32_t passedTime();
void normalWork(){
  uint8_t times[] = {3, 1, 2, 1};
Serial.println(passedTime());
  switch (trafficLightState)
  {
    case 0:
      Serial.println("state 1");
      turnOnLed(redLed);
      if (passedTime() > times[trafficLightState] * oneSecond)
      {
        trafficLightState = 1;
        millisState = millis();
      }
      break;
    case 1:
      Serial.println("State 2");
      turnOnLed(yellowLed);
      if (passedTime() > times[trafficLightState] * oneSecond)
      {
        turnOffLed(redLed);
        turnOffLed(yellowLed);
        trafficLightState = 2;
        millisState = millis();
      }
      break;
    case 2:
      Serial.println("State 3");
      turnOnLed(greenLed);
      if (passedTime() > times[trafficLightState] * oneSecond)
      {
        turnOffLed(greenLed);
        trafficLightState = 3;
        millisState = millis();
      }
      break;
    case 3:
      Serial.println("State 4");
      turnOnLed(yellowLed);
      if (passedTime() > times[trafficLightState] * oneSecond)
      {
        turnOffLed(yellowLed);
        trafficLightState = 0;
        millisState = millis();
      }
      break;
    default:
      break;
  }
}

uint32_t passedTime(){
  return millis() - millisState;
}