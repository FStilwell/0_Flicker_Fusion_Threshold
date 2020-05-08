#include <Arduino.h>

#define potPin 14
#define ledPin 13
#define buttonPin 12

//Declare Variables
uint32_t scanTime = 0;
const uint32_t scanOffset_us = 1;
int32_t scanDifference_us = 0;
volatile bool ledState = 0;
const int32_t debounceTime_ms = 150;
bool buttonState = 0;
float freq = 0;
uint32_t elapsedTime_us = 0;

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

void setup() {
 pinMode(potPin, INPUT);
 pinMode(ledPin, OUTPUT);
 analogReadResolution(10); //10bit ADC

 //Initialise interrupt
 attachInterrupt(buttonPin, ISR_Button, FALLING);

 Serial.begin(115200);
}

void loop() {
 static uint32_t elapsedPrevious_us = 0;

 while(buttonState == 1){
   saveFreq();
 }

 //Toggle LED state
 ledState = !ledState;
 digitalWrite(ledPin,ledState);

 static uint32_t previousTime_us = 0;

 //Plot PWM
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
 scanTime = outputPeriod/2 - scanOffset_us;
 while((micros()-previousTime_us) <= scanTime) {
   //do nothing
 }
 
 
 //Evaluate the scan time with the elapsed time
 uint32_t elapsedCurrent_us = micros();
 elapsedTime_us = elapsedCurrent_us - elapsedPrevious_us;
 scanDifference_us = elapsedTime_us - outputPeriod/2;
 Serial.print(scanTime);
 Serial.print(" , ");
 Serial.print(elapsedTime_us);
 Serial.print(" , ");
 Serial.println(scanDifference_us);
 Serial.flush();

 previousTime_us = micros();
 elapsedPrevious_us = micros();
}

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

//End of program
void saveFreq(){
  Serial.print("Chosen frequency: ");
  Serial.print(freq);
  Serial.println("Hz. Press button to return");
}