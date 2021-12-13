/*
 * @file	   : uart.h
 *
 * @description: includes the APIs required to configure and use UART0
 *
 *  Created on : December 1, 2021
 *  Author     : Santhosh, santhosh@colorado.edu
 */

#ifndef UART_H_
#define UART_H_

#include <MKL25Z4.H>

#include "cbuffer.h"


/*
 * @function: InitUart();
 *
 * @description: Initializes UART with with baud rate 115200, Data size 8, Parity None and  1 Stop bits
 *
 * Parameters
 * 		None
 *
 * Returns
 * 		None
 */
extern void InitUart(void);

/*
 * @function: user_input();
 *
 * @description: Used to detect the user input via UART
 *
 * Parameters
 * 		None
 *
 * Returns
 * 		(int) 1 if user input detected, 0 if not detected
 */
extern int uart_input(void);

/*
 * @function: disable_uart();
 *
 * @description: disables the UART0 interrupt
 *
 * Parameters
 * 		None
 *
 * Returns
 * 		None
 */
extern void disable_uart(void);

/*
 * @function: enable_uart();
 *
 * @description: enables the UART0 interrupt
 *
 * Parameters
 * 		None
 *
 * Returns
 * 		None
 */
extern void enable_uart(void);


#endif /* UART_H_ */
