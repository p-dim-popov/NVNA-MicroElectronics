#include <Arduino.h>

const int LED = 13;
const int button = 2;
int counter = 0;
void buttonClickHandler();
void setup()
{
  pinMode(LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(button), buttonClickHandler, RISING);
}

void loop()
{
}

void switchLedState(const int &LED){
  digitalWrite(LED, !digitalRead(LED));
  counter = 0;
}

void buttonClickHandler(){
  counter++;
  if (counter == 2 && !digitalRead(LED))
    {
      switchLedState(LED);
    }
    if (counter == 3)
    {
      switchLedState(LED);
    }
}