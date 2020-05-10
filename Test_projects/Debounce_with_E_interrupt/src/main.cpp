/*
Use button with external interrupt to switch LED
20200406 Flynn Stilwell
*/

#include <Arduino.h>

#define buttonPin 12
#define LEDPin 13

//Function prototype
void ISR_Button(); 

volatile uint32_t pressCounter = 0;
volatile boolean LEDState = false;

boolean buttonPressed = false;

const uint8_t debounceTime_ms = 150;




void setup() {
 pinMode(buttonPin, INPUT_PULLUP);
 attachInterrupt(buttonPin, ISR_Button, FALLING);
 pinMode(LEDPin, OUTPUT);

 Serial.begin(115200);
}

void loop() {
  static int32_t previousMillis = 0;
  int32_t currentMillis = millis();
  
  digitalWrite(LEDPin, LEDState);

//Print press counter
    if ((currentMillis - previousMillis) >= 100){
      Serial.print("LED state = ");
      Serial.print(LEDState);
      Serial.print("\tPress Number = ");
      Serial.println(pressCounter);
      Serial.flush();

      previousMillis = currentMillis;
    }

}

//Interrupt service routine
void ISR_Button(){
  static uint32_t previousMillisButton = millis();
  uint32_t currentMillisButton = millis();

  //Serial.println("Arrived in ISR");
    if ((currentMillisButton - previousMillisButton) >= debounceTime_ms){
      previousMillisButton = currentMillisButton;
      
      LEDState = !LEDState;
      pressCounter++; 
    }
    
}