#include <Arduino.h>

// ENV VAR
#define _DEBUG
#define is ==

// PINS
#define RED_LED 13
#define GREEN_LED 12
#define RED_LED_BUTTON 2
#define GREEN_LED_BUTON 3
#define SERIAL_BAUD 9600

// MACROS
#define TURN_ON_LED(LED) digitalWrite(LED, HIGH)
#define TURN_OFF_LED(LED) digitalWrite(LED, LOW)

#ifdef _DEBUG
  #define TRACE_LINE(str) Serial.println(str)
  #define TRACE(str) Serial.print(str)
#endif

#ifndef _DEBUG
  #define TRACE_LINE(str)
  #define TRACE(str)
#endif

int RedLedTurnOnTime = 0;
int GreenLedTurnOnTime = 0;

int RedLedLastState = 0;
int GreenLedLastState = 0;

void PrintChanges(const int redLedState, const int greenLedState);
void OnRedLedBtnClick();
void OnGreenLedBtnClick();

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(RED_LED_BUTTON, INPUT);
  pinMode(GREEN_LED_BUTON, INPUT);

  attachInterrupt(digitalPinToInterrupt(RED_LED_BUTTON), OnRedLedBtnClick, RISING);
  attachInterrupt(digitalPinToInterrupt(GREEN_LED_BUTON), OnGreenLedBtnClick, FALLING);

  Serial.begin(SERIAL_BAUD);
}

void loop() {
  #ifdef _DEBUG
    int redLedState = digitalRead(RED_LED);
    int greenLedState = digitalRead(GREEN_LED);

    if (RedLedLastState != redLedState || GreenLedLastState != greenLedState)
    {
      PrintChanges(redLedState, greenLedState);
      RedLedLastState = redLedState;
      GreenLedLastState = greenLedState;
    }
  #endif
  
}

void PointSeven(const int led){
  if (digitalRead(led))
  {
    TURN_OFF_LED(led);
    return;
  }
  TURN_ON_LED(led);
}

void PointEight(const int button){
  if (button is RED_LED_BUTTON)
  {
    if (!digitalRead(RED_LED))
    {
      TURN_ON_LED(RED_LED);
      return;
    } 

    TURN_ON_LED(GREEN_LED);
    return;
  }
  
  if (button is GREEN_LED_BUTON)
  {
    if (digitalRead(GREEN_LED))
    {
      TURN_OFF_LED(GREEN_LED);
      return;
    }

    TURN_OFF_LED(RED_LED);
  }
}

void OnRedLedBtnClick(){
  // PointSeven(RED_LED);

  PointEight(RED_LED_BUTTON);
}

void OnGreenLedBtnClick(){
  // PointSeven(GREEN_LED);

  PointEight(GREEN_LED_BUTON);
}

void PrintChanges(const int redLedState, const int greenLedState){
  TRACE_LINE("STATES: [RED_LED], [GREEN_LED]");
  TRACE("        "); 
  TRACE(redLedState ? "ON" : "OFF"); 
  TRACE(", "); 
  TRACE_LINE(greenLedState ? "ON" : "OFF");
}