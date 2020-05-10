/*
Flynn Stilwell May 2020

This program maps a potentiometer ADC reading to a certain range.

*/


#include <Arduino.h>

#define potPin 14

//Declare Variables
uint32_t scanTime = 10000;

//Mapping Variables
uint32_t inputPot = 0;
const uint32_t inputMin = 0;
const uint32_t inputMax = 102;

uint32_t outputPeriod = 0;
const uint32_t outputPeriodMin = 1; //Minimum value of 1 to prevent dividing by 0 later
const uint32_t outputPeriodMax = 30000; //30,000 usecs

void setup() {
 pinMode(potPin, INPUT);
 analogReadResolution(10); //10bit ADC
 Serial.begin(115200);
}

void loop() {
 static uint32_t previousTime_us = 0;

 //Format input signal
 inputPot = analogRead(potPin)/10; //Divide by 10 for more stable values

 //Map input to output range
 
 outputPeriod = map(inputPot, inputMin, inputMax, outputPeriodMin, outputPeriodMax);
 
 //outputPeriod = (inputPot - inputMin)/(inputMax - inputMin);
 //outputPeriod = outputPeriod*(outputPeriodMax - outputPeriodMin) + outputPeriodMin;
 
 
 //Print Results
 Serial.print("Input val: ");
 Serial.print(inputPot);
 Serial.print(" Output val: ");
 Serial.println(outputPeriod);

//Configure scan time
 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 previousTime_us = micros();
}