/*
 * cirbuf.c
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */


#include "main.h"
#include "stdlib.h"


uint8_t task_Push(taskqueue_t *c,task data)
{
	task* adr;
	adr = c->head + 1;
	if(adr >= c->buff + c->size) {
	adr = c->buff;
	}
	if(Is_buffer_full(c)) {
	return(0);
	}
	*c->head = data;
	c->head = adr;
	c->count++;
	return(1);
}


uint8_t task_Pop(taskqueue_t *c, task *data)
{
	task* adr;
	if(c->count == 0) {
	return(0);
	}
	else {
	*data = *(c->tail);
	*(c->tail) = 0;
	adr = c->tail + 1;
	if(adr >= c->buff + c->size) {
	adr = c->buff;
	}
	c->tail = adr;
	c->count--;
	}
	return(1);
}

void taskBuff_init(taskqueue_t *c,uint8_t size,task* buff)
{
	c->buff = malloc(sizeof(task) * size);
    c->size = size;							 //total size of buffer
    c->head = c->buff;					 //initially head and tail are at buff
    c->tail = c->buff;
    c->count = 0;			   			 //current number of items in buffer
}


uint8_t Is_buffer_full(taskqueue_t *c)
{
	return(c->count == c->size);
}

uint8_t Is_buffer_Empty(taskqueue_t *c)
{
	return(c->count == 0);
}




