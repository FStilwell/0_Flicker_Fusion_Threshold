#include <Arduino.h>

#define potPin 14
#define ledPin 13
#define buttonPin 12

//Declare Variables
uint32_t scanTime = 0;
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

//Funtion Prototypes
void ISR_Button();
void saveFreq();


//======================================= Setup ==================================================
void setup() {
 pinMode(potPin, INPUT);
 pinMode(ledPin, OUTPUT);
 analogReadResolution(10); //10bit ADC

 //Initialise interrupt
 attachInterrupt(buttonPin, ISR_Button, FALLING);

 Serial.begin(115200);
}
//===================================== Main Loop ================================================
void loop() {
 static uint32_t elapsedPrevious_us = 0;
 static uint32_t previousTime_us = 0;
 
 //Change state to save frequency
 while(buttonState == 1){
   saveFreq();
 }
 
 //PWM plot point 1
 //Serial.println(ledState);

 //Toggle LED state
 ledState = !ledState;
 digitalWrite(ledPin,ledState);

 //PWM plot point 2
 //Serial.println(ledState);

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
 Serial.print(" Frequency: ");
 Serial.print(freq);
 Serial.print("Hz , ");

//Configure scan time
 scanTime = outputPeriod/2;
 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 
 previousTime_us = micros();
}
//======================================= ISR ==================================================
//Interrupt service routine
void ISR_Button(){
  static uint32_t previousMillisButton = 0;
  uint32_t currentMillisButton = millis();

  //Serial.println("Arrived in ISR");
    if ((currentMillisButton - previousMillisButton) >= debounceTime_ms){
      previousMillisButton = currentMillisButton;
      buttonState = !buttonState;
    }
    
}
//======================================= Save Frequency========================================
//End of program
void saveFreq(){
  Serial.print("Chosen freq: ");
  Serial.print(freq);
  Serial.print("Hz Period: ");
  Serial.print(outputPeriod);
  Serial.println(". Press button to return");
}