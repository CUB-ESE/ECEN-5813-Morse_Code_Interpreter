/*
 * @file: uart.h
 *
 * @description: includes function prototype to initialize UART0
 *
 *  Created on: December 1, 2021
 *  Author    : Santhosh, santhosh@colorado.edu
 */

#ifndef UART_H_
#define UART_H_

#include <MKL25Z4.H>

#include "cbuffer.h"
//#include "sysclock.h"

extern cbuffer TxBuff, RxBuff;

/*
 * @function: InitUart();
 *
 * @description Initializes UART with with baud rate 38400, Data size 8, Parity None and  2 Stop bits
 *
 * Parameters
 * 		None
 *
 * Returns
 * 		None
 */
void InitUart(void);

int uart_input(void);

void disable_uart(void);

void enable_uart(void);


#endif /* UART_H_ */
