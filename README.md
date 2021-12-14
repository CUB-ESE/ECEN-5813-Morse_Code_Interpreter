# Morse-Code-Interpreter
Code for Final Project for PES, ECEN-5813, Fall 2021

# MORSE CODE

This is a method used in telecommunication to encode text characters as standardized sequences of two different signal durations, called dots and dashes

# MORSE CODE INTERPRETER

This project uses FRDM-KL25Z as a MORSE code interpreter device. The development of this project involves PWM, TIMER, circular buffers, GPIO, and UART using interrupts. 

MORSE code interpreter works here in two ways. When the user taps the button, it will be interpreted as the MORSE code, or when the user enters the string from the terminal it will be translated into the Morse code and interpreted using LED. 

# USER INTERFACE
![Terminal](https://user-images.githubusercontent.com/47562746/145921728-034e22cd-4f33-4971-a248-07e03c66cc5c.PNG)
Figure 1: UART Terminal screenshot

# VIDEO DEMO
https://drive.google.com/file/d/1LgoO2Ni2UW6Yw-ez4Pn-ZqQDV5Ggl0y8/view?usp=sharing

Video Description: Video includes the program running in release mode. First it displays the intialization sequence by displaying Morse code for the characters from A - F.
Then it includes the converion of Morse code from the button to character and Character to Morse code.

# TESTING

Below screenshots shows the testing techniques and sequence, which basically includes uCUnit test to check the Converion modules and some asserting to test other functinality.

![Testing_1](https://user-images.githubusercontent.com/47562746/145922303-cac16814-f192-405d-8d35-df4086a3fb75.PNG)

![testing_2](https://user-images.githubusercontent.com/47562746/145922318-4e86e650-d4f4-465a-b371-e4d1a6351f9e.PNG)

![testing_3](https://user-images.githubusercontent.com/47562746/145922321-0daa64b7-8036-4663-bbe7-fc758e67259e.PNG)
