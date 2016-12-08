/*
 * cirbuf.h
 *
 *  Created on: 11-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_TASKBUF_H_
#define SOURCES_TASKBUF_H_

typedef void(*task)(void);

typedef enum {
	logtask1 = 0,
	max_log_tasks
}log_tasks_e;

typedef enum {
	fasttask1 = 0,
	fasttask2,
	fasttask3,
	fasttask4,
	fasttask5,
	fasttask6,
	fasttask7,
	fasttask8,
	max_fast_tasks
}fast_tasks_e;

typedef enum {
	midtask1 = 0,
	midtask2,
	max_mid_tasks
}mid_tasks_e;

typedef enum {
	slowtask1 = 0,
	max_slow_tasks
}slow_tasks_e;


typedef struct {
task* buff; /*The buffer address*/
task* head; /*The buffer start address*/
task* tail; /*The buffer end address*/
uint32_t size; /*The total capacity of the buffer*/
uint8_t count; /*Total number of elements currently in buffer*/
} taskqueue_t;

void    taskBuff_init(taskqueue_t*,uint8_t ,task* );
uint8_t task_Push(taskqueue_t*,task );
uint8_t task_Pop(taskqueue_t*, task*);
uint8_t Is_buffer_full(taskqueue_t *c);
uint8_t Is_buffer_Empty(taskqueue_t *c);

#endif /*  */
