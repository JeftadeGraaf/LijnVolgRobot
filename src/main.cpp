#include <Arduino.h>
#include <Display.h>

// put function declarations here:
int digitPins[7] = {17, 16, 15, 14, 2, 1, 0};
Display display(digitPins, 18, 19);


void setup() {
  // put your setup code here, to run once:
  display.setup();
  Serial.begin(9600);



}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  display.displayChar('F');
}
