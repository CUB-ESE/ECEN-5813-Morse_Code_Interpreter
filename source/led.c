/*
 * led.c
 *
 *  Created on: Dec 1, 2021
 *      Author: ajsan
 */


#include <MKL25Z4.h>

//defining macros for led ports
#define		RED		18
#define 	GREEN 	19
#define 	BLUE 	1

//Function: ledInit()
/*
 * Initializes RGB led's by setting clock to the port and making them as GPIO along
 * with setting the direction as output
 *
 */
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

//		//Setting pins as output
//		GPIOB->PDDR |= (1<<RED);
//		GPIOB->PDDR |= (1<<GREEN);
//		GPIOD->PDDR |= (1<<BLUE);
//
//		//All led off
//		GPIOB->PSOR |=(1<<RED);
//		GPIOB->PSOR |=(1<<GREEN);
//		GPIOD->PSOR |=(1<<BLUE);

}

//Function: redLedOn()
/*
 * Turns on red led
 *
 */
void redLedOn(){

	GPIOB->PCOR |=(1<<RED);
}

//Function: redLedOff()
/*
 * Turns off red led
 *
 */
void redLedOff(){

	GPIOB->PSOR |=(1<<RED);

}

//Function: greenLedOn()
/*
 * Turns on green led
 *
 */
void greenLedOn(){

	GPIOB->PCOR |=(1<<GREEN);

}

//Function: greenLedOff()
/*
 * Turns off green led
 *
 */
void greenLedOff(){

	GPIOB->PSOR |=(1<<GREEN);

}

//Function: blueLedOn()
/*
 * Turns on blue led
 *
 */
void blueLedOn(){

	GPIOD->PCOR |=(1<<BLUE);


}

//Function: blueLedOff()
/*
 * Turns off blue led
 *
 */
void blueLedOff(){

	GPIOD->PSOR |=(1<<BLUE);

}

//Function: whiteLedOn()
/*
 * Turns on white led
 *
 */
void whiteLedOn(){

	redLedOn();
	greenLedOn();
	blueLedOn();

}

//Function: whiteLedOff()
/*
 * Turns off white led
 *
 */
void LedOff(){

//	redLedOff();
//	greenLedOff();
//	blueLedOff();

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
