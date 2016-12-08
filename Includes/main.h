/*
 * main.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_HSW_MAIN_H_
#define INCLUDES_HSW_MAIN_H_

#include "HSW/uart.h"
#include "HSW/nvic.h"
#include "HSW/tsi.h"
#include "BASE/taskbuf.h"

#include "HSW/i2c.h"
#include "HSW/i2c1.h"
#include "HSW/rtc.h"
#include "ASW/angle_cal.h"
#include "BASE/mma8451.h"


#include "MKL25Z4.h"
#include "stdint.h"
#include "BASE/logger.h"
#include "BASE/profiler.h"
#include "BASE/ds1631.h"
#include "ASW/led.h"

extern int totalAlarmSeconds;
extern uint32_t seconds , minutes, onesecond, hours;

extern uint8_t fasttask_trig ;
extern uint8_t midtask_trig ;
extern uint8_t slowtask_trig ;

extern uint8_t logtask_trig ;
extern volatile uint32_t traveltimer;


#define TRUE 	(1)
#define FALSE	(0)

#define LOG			//to enable uart logging
//#define MSG
#define DMA_test
//#define BBB

#endif /* INCLUDES_HSW_MAIN_H_ */
