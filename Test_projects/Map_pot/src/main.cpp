#include <Arduino.h>

#define potPin 14

//Declare Variables
uint32_t scanTime = 10000;

void setup() {
 pinMode(potPin, INPUT);
 Serial.begin(115200);
}

void loop() {
 static uint32_t previousTime_us = 0;
 
 Serial.println(analogRead(potPin));

 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 previousTime_us = micros();
}