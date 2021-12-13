/*
 *  @file		: led.c
 *
 *  @description: includes the APIs required for the RGB LED control
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */

#include <MKL25Z4.h>

//defining macros for led ports
#define		RED		18
#define 	GREEN 	19
#define 	BLUE 	1

//Refer header file for function documentation

void ledInit(){

		//Clock gating for Port B & D
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;

		//making pins as GPIO
		PORTB->PCR[RED] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[RED] |= PORT_PCR_MUX(3);

		PORTB->PCR[GREEN] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[GREEN] |= PORT_PCR_MUX(3);

		PORTD->PCR[BLUE] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[BLUE] |= PORT_PCR_MUX(4);

}


void LedOff(){

		TPM2->CONTROLS[0].CnV = 0;
		TPM2->CONTROLS[1].CnV = 0;
		TPM0->CONTROLS[1].CnV = 0;
}

void RGB_LED_ON(uint32_t color)
{
		uint8_t R,G,B;

		//Converting uint32_t to uint8_t
		R=(color>>16)&(0xFF);
		G=(color>>8)&(0xFF);
		B=(color)&(0xFF);

		//setting corresponding duty cycle Timers
		TPM2->CONTROLS[0].CnV = R;
		TPM2->CONTROLS[1].CnV = G;
		TPM0->CONTROLS[1].CnV = B;
}
