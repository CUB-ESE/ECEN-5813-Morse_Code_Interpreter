/*
 * @file: uart.c
 *
 * @description: includes definition of function prototypes in uart.h to initialize UART0
 *
 *  Created on: December 1, 2021
 *  Author    : Santhosh, santhosh@colorado.edu
 */

#include <stdio.h>
#include <stdint.h>

#include "uart.h"

#define UART_OVERSAMPLE_RATE 	(16)    //UART0 over sampling rate
#define SYSCLOCK_FREQUENCY      (48e6)
#define BAUD_RATE 				(115200) //UART0 baud rate
#define STOP_BIT				(0)		//TWO Stop bits ('0' for 1 Stop Bit)
#define	BIT_MODE				(0)		//8-bit mode 	('1' for 9-bit mode)
#define PARITY_ENABLE			(0)		//Parity disabled ('1' parity enabled)
#define PARITY_TYPE				(0)		//('0'-Even parity/ '1'- Odd parity)


int uart_rx=0;
//create two buffer, one for Tx and one for Rx
cbuffer TxBuff, RxBuff;

//Refer header fors function description
void InitUart(void)
{
	uint16_t sbr;	//variable to store SBR constant value

	//Enabling clock to UART0 and PORTA
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Disabling Tx and Rx
	UART0->C2 &= (~UART0_C2_TE_MASK) & (~UART0_C2_RE_MASK);

	//Setting UART0 clock to 48MHz
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	//Setting PORTA pins to Tx and Rx of UART0
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);

	// Calculating sbr and setting baud rate to 38400 with over-sampling rate of 16
	sbr = (uint16_t)((SYSCLOCK_FREQUENCY )/(BAUD_RATE* UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disabling interrupts for RX active edge and LIN break detect, setting for two stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(STOP_BIT) | UART0_BDH_LBKDIE(0);

	// Disabling loop-back mode, setting to 8 data bit mode without parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(BIT_MODE) | UART0_C1_PE(PARITY_ENABLE);

	// Disabling inverting transmit data, disabling interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(1)| UART0_C3_NEIE(1)
				| UART0_C3_FEIE(1) | UART0_C3_PEIE(1);

	// Clearing all error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1)
				| UART0_S1_PF(1);

	// Sending LSB first, and disabling inverting received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

	//Setting priority to UART Interrupts
	NVIC_SetPriority(UART0_IRQn, 2);
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enabling only Rx interrupt
	UART0->C2 |= UART_C2_RIE(1);

	// Enabling UART0 Rx and Tx
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	//Clearing UART0 RDRF flag
	UART0->S1 &= ~UART0_S1_RDRF_MASK;
}


// UART0 IRQ Handler
void UART0_IRQHandler(void)
{
	uint8_t user_input;

	//Rx interrupt check
	if (UART0->S1 & UART0_S1_RDRF_MASK){
		uart_rx=1;
		user_input = UART0->D;         				//reading data register for user input
		if (!(IsBuffFull(&RxBuff))) {				//If Rx buffer is not full enqueues to Rx buffer

			cbuffer_enqueue(&RxBuff, user_input);
		}
	}

	//Tx interrupt check
	if ( (UART0->C2 & UART0_C2_TIE_MASK) ) {

		if (!IsBuffEmpty(&TxBuff)) {				//If Tx buffer is not empty

			UART0->D = cbuffer_dequeue(&TxBuff);	//dequeue a character and send to terminal

		} else {

			UART0->C2 &= ~UART0_C2_TIE_MASK;		//Disable Tx flag

		}
	}

}


//glue logic to route printf() to UART
int __sys_write(int handle, char *buff, int size)
{

	while (*buff != '\0') {

			while (IsBuffFull(&TxBuff));		//waiting for the Tx buffer to get space

			if(!IsBuffFull(&TxBuff))			//If Tx buff is full enable Tx Interrupt flag
				UART0->C2 |= UART0_C2_TIE(1);	//Set Tx Interrupt flag

			cbuffer_enqueue(&TxBuff, *buff);	//enqueue to Tx buffer
			buff++;
	}

	UART0->C2 |= UART0_C2_TIE(1);				//Set Tx Interrupt flag

	return 0;
}

//glue logic to route getchar() to UART
int __sys_readc(void)
{
	while (cbuffer_length(&RxBuff) == 0); // waiting for the user input

	return cbuffer_dequeue(&RxBuff);	  //return the user input
}

int uart_input(void)
{
	if(uart_rx){
		uart_rx=0;
		return 1;
	}else
	return 0;
}

void disable_uart(void)
{
	UART0->C2 &= (~UART0_C2_RE_MASK);
}

void enable_uart(void)
{
	UART0->C2 |=(UART0_C2_RE_MASK);
}
