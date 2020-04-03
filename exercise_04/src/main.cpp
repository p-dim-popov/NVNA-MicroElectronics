#include <Arduino.h>

#define led 12
#define button 2

int counter = 0;

void blinkWithLogic();
void lightOnHold();
void holdReleaseHandler();
void toggleLogic();

void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  String input = Serial.readString();
  if (input == ("blink with logic")) {
    attachInterrupt(digitalPinToInterrupt(button), blinkWithLogic, RISING);
  }
  else if(input == "light on hold")
  {
    attachInterrupt(digitalPinToInterrupt(button), lightOnHold, RISING);
  }
  else if(input == "toggle mode"){
    attachInterrupt(digitalPinToInterrupt(button), toggleLogic, RISING);
  }
}

void switchLedState(const int &LED){
  uint8_t currentState = digitalRead(LED);
  digitalWrite(LED, !currentState);
  counter = 0;
}
void blinkWithLogic(){
  counter++;
  if (counter == 2 && !digitalRead(led))
    {
      switchLedState(led);
    }
    if (counter == 3)
    {
      switchLedState(led);
    }
}
void lightOnHold(){
  digitalWrite(led, HIGH);
  attachInterrupt(digitalPinToInterrupt(button), holdReleaseHandler, FALLING);
}
void holdReleaseHandler(){
  digitalWrite(led, LOW);
  attachInterrupt(digitalPinToInterrupt(button), lightOnHold, RISING);
}
void toggleLogic(){
  switchLedState(led);
}
