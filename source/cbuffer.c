/*
 *  @file       : cbuffer.c
 *
 *  @description: includes the APIs required for circular buffer
 *
 *  Created on  : December 1, 2021
 *  Author      : Santhosh, santhosh@colorado.edu
 */

#include "cbuffer.h"

//Refer header file for functions documentation

int cbuffer_capacity(void)
{
	return BUFFER_SIZE;
}

int IsBuffFull(cbuffer *buff)
{
	if(buff->length == cbuffer_capacity())
		return 1;

	return 0;
}

int IsBuffEmpty(cbuffer *buff)
{
	if(buff->length == 0)
		return 1;
	return 0;
}

uint16_t cbuffer_length(cbuffer *buff)
{
	return buff->length;
}

uint8_t cbuffer_enqueue(cbuffer *buff, uint8_t d)
{
	uint32_t irq_state;
	if(buff->length == BUFFER_SIZE)
		return 0;

	irq_state = __get_PRIMASK();
	__disable_irq();

	buff->data[buff->tail++] = d;
	buff->tail %= BUFFER_SIZE;
	buff->length++;

	__set_PRIMASK(irq_state);
	return buff->length;
}

int cbuffer_dequeue(cbuffer *buff)
{
	uint32_t irq_state;
	uint8_t ret_data;

	if(IsBuffEmpty(buff))
		return -1;

	irq_state = __get_PRIMASK();
	__disable_irq();

	ret_data = buff->data[buff->head++];
	buff->head %= BUFFER_SIZE;
	buff->length--;

	__set_PRIMASK(irq_state);
	return ret_data;

}
