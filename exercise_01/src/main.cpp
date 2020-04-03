#include <Arduino.h>

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(19*100); // Wait for 19*100 millisecond(s)
  digitalWrite(13, LOW);
  delay(5000/19); // Wait for 5000/19 millisecond(s)
}