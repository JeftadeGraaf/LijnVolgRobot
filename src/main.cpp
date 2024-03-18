#include <Arduino.h>
#include <IRSensor.h>
#include <IRArray.h>

int IRArrayPins[5] = {4,5,6,7,8};



// put function declarations here:
IRArray irArray(IRArrayPins);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irArray.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(irArray.distances[0]);
  delay(100);
  irArray.refreshValues();
  Serial.println(irArray.values[0]);
}