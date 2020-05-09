# Flicker Fusion Threshold Assignment Project Report

## 1. Introduction

The purpose of this project is to construct a prototype of an embedded system to determine the frequency of a person's subjective flicker fusion threshold. "The flicker fusion threshold, or flicker fusion rate, is a concept in the psychophysics of vision. It is defined as the frequency at which an intermittent light stimulus appears to be completely steady to the average human observer" (Wikipedia, 2003).

The system prototype I contructed is based off of a Teensy 3.2 microcontroller, which is breadboarded along with a push button and 10kohm potentiometer. When uploaded, the program blinks the teensy's in-built LED with a 50% duty-cycle. The frequency of the blinking LED is proportional to the position of the potentiometer wiper, starting at the lowest frequency. Once the user finds the frequency at which they cannot see blinking, they press the pushbutton. This will output a message to a serial monitor showing the chosen frequency, and a prompt to press the button to return to adjusting the frequency.

The system uses the teensy's built-in LED because I did not have the right components, nor a multimeter to check the resistors' values I did have. This report will include a demonstration of how I would calculate the current-limiting resistor value for the LED to compensate.

The program was created initially in several smaller programs to prove functionalities; debouncing the button with an external interrupt, mapping the potentiometer analogue to digital (ADC) reading to a certain range, and mapping the ADC reading to the LED blink frequency. The frequency was tested using a serial plotter to plot the wavform.

## 2. Methods

### Determining Current Limiting Resistor

According to the [teensy's datasheet](Project_media/Datasheets/MK20DX64VLH7_Datasheet.pdf), the single pin current limit is 25mA. I chose [this LED datasheet](Project_media/Datasheets/element14_1003210_LED.pdf) as I have used it for another course.

![Figure 1: Forward voltage and current selection](Project_media\Images\LED data.PNG)

