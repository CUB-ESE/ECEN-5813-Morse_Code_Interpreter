/*
 * @file: cbuffer.h
 *
 * @description: includes function prototypes for circular buffer
 *
 *  Created on: December, 2021
 *  Author    : Santhosh, santhosh@colorado.edu
 */

#ifndef CBUFFER_H_
#define CBUFFER_H_

#include <stdint.h>
#include "MKL25Z4.h"

#define BUFFER_SIZE 256		// circular buffer size

//Structure to create circular buffer objects
typedef struct{
	uint8_t head;
	uint8_t tail;
	uint16_t length;
	uint8_t data[BUFFER_SIZE];
}cbuffer;


/*
 * @function: cbuffer_length()
 *
 * @description: returns the current size of the buffer
 *
 * Parameter
 * 		circular buffer
 *
 * Returns
 * 		length of the buffer
 */
uint16_t cbuffer_length(cbuffer *buff);

/*
 * @function: cbuffer_enqueue()
 *
 * @description: enqueues a byte of data to the circular buffer
 *
 * Parameter
 * 		(*buff,d) <-- circular buffer, data
 *
 * Returns
 * 		0 if buffer is full, else returns the length of the buffer
 */
uint8_t cbuffer_enqueue(cbuffer *buff, uint8_t d);

/*
 * @function: cbuffer_dequeue()
 *
 * @description: dequeues a byte of data from the buffer
 *
 * Parameter
 * 		(*buff) <-- circular buffer
 *
 * Returns
 * 		-1 if buffer is empty, else returns a byte of data
 */
int cbuffer_dequeue(cbuffer *buff);

/*
 * @function: IsBuffFull()
 *
 * @description: returns the buffer full status
 *
 * Parameter
 * 		(*buff) <-- circular buffer
 *
 * Returns
 * 		0 if not full, 1 if buffer is full
 */
int IsBuffFull(cbuffer *buff);


/*
 * @function: IsBuffEmpty()
 *
 * @description: returns the buffer empty status
 *
 * Parameter
 * 		(*buff) <-- circular buffer
 *
 * Returns
 * 		0 if not empty, 1 if buffer is empty
 */
int IsBuffEmpty(cbuffer *buff);


/*
 * @function: IsBuffCapacity()
 *
 * @description: returns the buffer capacity
 *
 * Parameter
 * 		(*buff) <-- circular buffer
 *
 * Returns
 * 		capacity of the buffer (Full size)
 */
int cbuffer_capacity(void);

#endif /* CBUFFER_H_ */
