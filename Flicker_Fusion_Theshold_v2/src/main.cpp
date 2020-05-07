#include <Arduino.h>

#define potPin 14
#define ledPin 13
#define buttonPin 12

//Declare Variables
uint32_t scanTime = 10000;
volatile bool ledState = 0;
const int32_t debounceTime_ms = 150;
bool buttonState = 0;
float freq = 0;

//Mapping Variables
uint32_t inputPot = 0;
const uint32_t inputMin = 0;
const uint32_t inputMax = 102;

uint32_t outputPeriod = 0;
const uint32_t outputPeriodMin = 1;
const uint32_t outputPeriodMax = 40000; //30,000 usecs

//ISR Funtion Prototype
void ISR_Button();

void setup() {
 pinMode(potPin, INPUT);
 pinMode(ledPin, OUTPUT);
 analogReadResolution(10); //10bit ADC

 //Initialise interrupt
 attachInterrupt(buttonPin, ISR_Button, FALLING);

 Serial.begin(115200);
}

void loop() {
 static uint32_t previousTime_us = 0;
 
 //Toggle LED state
 ledState = !ledState;
 digitalWrite(ledPin,ledState);

 //Format input signal
 inputPot = analogRead(potPin)/10; //Divide by 10 for more stable values
 inputPot = constrain(inputPot,1,102);

 //Map input to output range
 outputPeriod = map(inputPot, inputMin, inputMax, outputPeriodMax, outputPeriodMin);

 //Calculate frequency
 freq = (1.0/outputPeriod) * 1000000.0; //Multiply by 10^6 as period is in usec
 
 
 //Print Results
//  Serial.print("Input val: ");
//  Serial.print(inputPot);
//  Serial.print(" Output val: ");
//  Serial.print(outputPeriod);
//  Serial.print(" Button: ");
//  Serial.print(buttonState);
//  Serial.print(" Frequency: ");
//  Serial.println(freq);

//Plot PWM
Serial.println(ledPin);

//Configure scan time
 scanTime = outputPeriod/2;
 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 previousTime_us = micros();
}

//Interrupt service routine
void ISR_Button(){
  static uint32_t previousMillisButton = millis();
  uint32_t currentMillisButton = millis();

  //Serial.println("Arrived in ISR");
    if ((currentMillisButton - previousMillisButton) >= debounceTime_ms){
      previousMillisButton = currentMillisButton;
      buttonState = !buttonState;
    }
    
}

//End of program
void saveFreq(){
  
}