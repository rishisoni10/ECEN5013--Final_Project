/*
 * nvic.h
 *
 *  Created on: Oct 30, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_HSW_NVIC_H_
#define INCLUDES_HSW_NVIC_H_

#include "main.h"


#define ARM_INTERRUPT_LEVEL_BITS          2

#define EnableInterrupts __asm(" CPSIE i");
#define DisableInterrupts __asm(" CPSID i");

void enable_irq (int);
void disable_irq (int);
void set_irq_priority (int, int);


#endif /* INCLUDES_HSW_NVIC_H_ */
