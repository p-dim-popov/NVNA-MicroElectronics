#include <Arduino.h>
const int greenLED = 13;
const int redLED = 8;
int syncCount = 0;
const int second = 1000;


bool mustBeInSync(int &syncCount){
  return syncCount % 2 == 0;
}
void turnOnGreenLED(){
	digitalWrite(greenLED, HIGH);
}
void turnOffGreenLED(){
	digitalWrite(greenLED, LOW);
}
void turnOnRedLED(){
	digitalWrite(redLED, HIGH);
}
void turnOffRedLED(){
	digitalWrite(redLED, LOW);
}


void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
}

void loop()
{
  int repeat = 0;
  secondTime:
    if(mustBeInSync(syncCount))
    {
      turnOnGreenLED();
      turnOnRedLED();
    }
    else
    {
      turnOffGreenLED();
      turnOnRedLED();
    }
    delay(second);
    if(mustBeInSync(syncCount))
    {
      turnOffGreenLED();
      turnOffRedLED();
    }
    else
    {
      turnOnGreenLED();
      turnOffRedLED();
    }
    delay(second);
  repeat++;
  if(repeat != 2) goto secondTime;
  syncCount++;
}