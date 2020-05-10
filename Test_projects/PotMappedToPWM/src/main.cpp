/*
Flynn Stilwell May 2020

Mapping a potentiometer reading to a specified range. 

*/



#include <Arduino.h>

#define potPin 14
#define ledPin 13

//Declare Variables
uint32_t scanTime = 10000;
volatile bool ledState = 0;

//Mapping Variables
uint32_t inputPot = 0;
const uint32_t inputMin = 0;
const uint32_t inputMax = 102;

uint32_t outputPeriod = 0;
const uint32_t outputPeriodMin = 1;
const uint32_t outputPeriodMax = 40000; //40,000 microseconds

void setup() {
 pinMode(potPin, INPUT);
 pinMode(ledPin, OUTPUT);
 analogReadResolution(10); //10bit ADC
 Serial.begin(115200);
}

void loop() {
 static uint32_t previousTime_us = 0;
 
 //Toggle LED state
 ledState = !ledState;
 digitalWrite(ledPin,ledState);

 //Format input signal
 inputPot = analogRead(potPin)/10; //Divide by 10 for more stable values
 inputPot = constrain(inputPot,1,102); //Make 1 the lowest to avoid dividing by 0 later

 //Map input to output range
 outputPeriod = map(inputPot, inputMin, inputMax, outputPeriodMax, outputPeriodMin);
 
 
 //Print Results
 Serial.print("Input val: ");
 Serial.print(inputPot);
 Serial.print(" Output val: ");
 Serial.println(outputPeriod);

//Configure scan time
 scanTime = outputPeriod/2;
 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 previousTime_us = micros();
}