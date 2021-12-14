/*
 *  @file		: MorseCodeInterpreter.c
 *
 *  @description: includes the APIs required for the Morse code interpreter
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */


#include "MorseCodeInterpreter.h"
#include "cbuffer.h"
#include "uart.h"
#include "gpio.h"
#include "systick.h"
#include "led.h"
#include "tpm.h"

#include <ctype.h>

//circular buffer to store morse code inputs
cbuffer mcode;

//Structure to create lookup table to map characters to their Morse code
typedef struct{
	char *Mcode;
	char character;
}Mcode;

//Look-up table of all alphabets with their corresponding Morse code
static Mcode MorseCode[]={
		{"dD\n",'A'},{"Dddd\n",'B'},{"DdDd\n",'C'},{"Ddd\n",'D'},{"d\n",'E'},{"ddDd\n",'F'},{"DDd\n",'G'},{"dddd\n",'H'},{"dd\n",'I'},
		{"dDDD\n",'J'},{"DdD\n",'K'},{"dDdd\n",'L'},{"DD\n",'M'},{"Dd\n",'N'},{"DDD\n",'O'},{"dDDd\n",'P'},{"DDdD\n",'Q'},{"dDd\n",'R'},
		{"ddd\n",'S'},{"D\n",'T'},{"ddD\n",'U'},{"dddD\n",'V'},{"dDD\n",'W'},{"DddD\n",'X'},{"DdDD\n",'Y'},{"DDdd\n",'Z'},{"dDDDD\n",'1'},
		{"ddDDD\n",'2'},{"dddDD\n",'3'},{"ddddD\n",'4'},{"ddddd\n",'5'},{"Ddddd\n",'6'},{"DDddd\n",'7'},{"DDDdd\n",'8'},{"DDDDd\n",'9'},
		{"DDDDD\n",'0'}
};

//Number of elements in the MorseCode look-up table
const int NCodes = sizeof(MorseCode)/sizeof(MorseCode[0]);

//Refer header file for functions documentation

void delay(void){
	int t = now();
	while((now()-t)<2);
}

char* CharToMcode(char data)
{
		char *output=NULL;
		data = toupper(data);
		//Search for the match from the look-up table, if found displays using RGB LED and clears the CnvFlag
		for(int i=0;i<NCodes;i++){
			if(data == MorseCode[i].character){
				output=MorseCode[i].Mcode;
				for(int j=0;MorseCode[i].Mcode[j] != '\n';j++){

					if(MorseCode[i].Mcode[j] == 'd'){
						delay();
						RGB_LED_ON(RED);
						delay();
						LedOff();
					}else{
						delay();
						RGB_LED_ON(GREEN);
						delay();
						LedOff();
					}

				}

				delay();
				RGB_LED_ON(BLUE);			//To indicate end of character
				delay();
				LedOff();
			}
		}

	return output;
}

char TapToChar(char* TapCode)
{
		int q=0;
		int j=0;

		//searches for the match from the look-up table
		for(int i=0; i<NCodes; i++){
			q=0;
			for(j=0; ((*(TapCode+j)!='\n'));j++){
				if((*(TapCode+j))==(*(MorseCode[i].Mcode + j)))
					continue;
				else{
					q=1;
					break;
				}
			}

			if((*(MorseCode[i].Mcode + j)=='\n') && (q==0))
				return MorseCode[i].character;
		}

		return 0;
}

void Init_MorseCodeInterpreter(void)
{
    INIT_SysTick();
    InitUart();
	INIT_GPIO();
	ledInit();
	INIT_RGB_LED_PWM();
}

void Boot_Sequence(void)
{
	char sequence[]={'A','B','C','D','E','F'};
	for(int i=0; i<(sizeof(sequence)); i++)
		CharToMcode(sequence[i]);
}
