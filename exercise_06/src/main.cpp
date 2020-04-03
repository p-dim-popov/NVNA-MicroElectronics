#include <Arduino.h>


const uint8_t ledPin = 13;
const uint8_t buttonPin = 3;
const uint16_t baud_rate = 9600;
const uint16_t oneSecond = 1000;

bool buttonState = 0;
bool prevButtonState = 0;
uint32_t time;

void timeControl(const uint32_t& time, const uint8_t& ledPin);

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(baud_rate);
}

void loop(){
  buttonState = digitalRead(buttonPin);
  if (buttonState) {
    if (prevButtonState != buttonState) {
      time = millis();
      prevButtonState = buttonState;
    }
  }
  else{
    if (prevButtonState != buttonState) {
      Serial.print("Button pressed for: ");
      Serial.print(millis() - time);
      Serial.println("ms");
      Serial.println();
      prevButtonState = buttonState;
      timeControl(millis() - time, ledPin);
    }
  }
}

void ledOn(const uint8_t& ledPin) {
  digitalWrite(ledPin, HIGH);
}

void ledOff(const uint8_t& ledPin) {
  digitalWrite(ledPin, LOW);
}

void toggleLed(const uint8_t& ledPin) {
  bool ledState = digitalRead(ledPin);
  digitalWrite(ledPin, !ledState);
}

void timeControl(const uint32_t& time, const uint8_t& ledPin) {
  bool ledState = digitalRead(ledPin);
  if (time > oneSecond * 3) return; 
  if (ledState) {
    if (time > oneSecond * 2) {
      ledOff(ledPin);
    }
  }
  else{
    if (time > oneSecond) {
      ledOn(ledPin);
    }
  }
}
