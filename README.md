# Flicker Fusion Threshold Assignment Project Report

## 1. Introduction

The purpose of this project is to construct a prototype of an embedded system to determine the frequency of a person's subjective flicker fusion threshold. "The flicker fusion threshold, or flicker fusion rate, is a concept in the psychophysics of vision. It is defined as the frequency at which an intermittent light stimulus appears to be completely steady to the average human observer" (Wikipedia, 2003).

The system prototype I contructed is based off of a Teensy 3.2 microcontroller, which is breadboarded along with a push button and 10kohm potentiometer. When uploaded, the program blinks the teensy's in-built LED with a 50% duty-cycle. The frequency of the blinking LED is proportional to the position of the potentiometer wiper, starting at the lowest frequency. Once the user finds the frequency at which they cannot see blinking, they press the pushbutton. This will output a message to a serial monitor showing the chosen frequency, and a prompt to press the button to return to adjusting the frequency.

The system uses the teensy's built-in LED because I did not have the right components, nor a multimeter to check the resistors' values I did have. This report will include a demonstration of how I would calculate the current-limiting resistor value for the LED to compensate.

The program was created initially in several smaller programs to prove functionalities; debouncing the button with an external interrupt, mapping the potentiometer analogue to digital (ADC) reading to a certain range, and mapping the ADC reading to the LED blink frequency. The frequency was tested using a serial plotter to plot the wavform.

## 2. Methods

### 2.1 Determining Current Limiting Resistor

According to the [teensy's datasheet](Project_media/Datasheets/MK20DX64VLH7_Datasheet.pdf), the single pin current limit is 25mA. I chose [this LED datasheet](Project_media/Datasheets/element14_1003210_LED.pdf) as I have used it for another course. As shown in figure 1 below, a current of 10mA was chosen because it should still operate at (worst case) 90 degrees Celsius ambient temperature, it gives a decent relative luminous density, and it is below half the single pin current limit of the microcontroller. This gave a forward voltage of 1.75 volts.

![Figure 1: Forward voltage and current selection](Project_media/Images/LED_data.PNG)

*_Figure 1:_ Forward voltage and current selection*

Using the parameters above, the series resistor value could be calculated using the equation in figure 2 below.

![Figure 2: Series Resistor Calculations](Project_media/Results/Series_resitor_calcs.PNG)

*_Figure 2:_ Series Resistor Calculations*

### 2.2 Breadboarding the System

The microcontroller is powered by the USB 5V supply. The system needed an LED (which was built-in), a potentiometer, a pushbutton, and the necessary jumper wires. I chose pin A0 for the potentiometer as it needed to connect to an ADC module, pin 12 for the push button as it was in a convenient position, and added the jumper wires to connect the components according to [this Eagle schematic](Schematic/Flicker_Fusion_schematic.PNG). The pushbutton makes use of the internal pullup resistor function in the microcontroller since I was unable to check the value of resistors I had. Figure 3 below shows this system.

![Figure 3: Bread-boarded embedded system](Project_media/Images/Breadboarded_System.jpg)

*_Figure 3:_ Bread-boarded embedded system*

### 2.3 Writing the program

I first broke the program into several smaller programs to make sure I could get them to work individually. This saved time on troubleshooting issues in the main program. I started off by using an example of [button debouncing with an external interrupt](Test_projects/Debounce_with_E_interrupt) from in-class.

After verifying that that the button debounce code worked, I went on to map the potentiometer ADC reading to a specific range in a [separate program](Test_projects/Map_pot).

I built off of the mapping code to enable mapping of the period of a blinking LED in [another separate program](Test_projects/PotMappedToPWM). My approach to blinking the LED was to flip the state of the LED for each cycle of the main loop in the program. This meant that the scan time of the program had to be half that of the blinking period (for a full cycle). I chose to do it this way because it is simpler than writing out separate on and off times for the LED. But this also meant that the duty cycle could only be 50%, which worked in favour of the project.

This led to compiling the smaller programs together to produce the [finished program](Flicker_Fusion_Theshold_v2).