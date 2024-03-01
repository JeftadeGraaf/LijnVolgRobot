#include <Arduino.h>
#include <IRSensor.h>
#include <IRArray.h>

int IRArrayPins[] = {1,2,3,4,5};

// put function declarations here:
IRArray irArray(IRArrayPins, 5);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irArray.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
 
}