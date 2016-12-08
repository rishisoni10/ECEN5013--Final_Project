/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "main.h"
#include "math.h"
#define PI 3.14159265
#define Max_EngTemp_allowed 18

float Speed;
float Distance;
uint32_t flag =0;

float  OldTime;
float  NewTime;

float x_travel;
float y_travel;

float Calculated_Position_x;
float Calculated_Position_y;

int32_t touchValue[2];
uint32_t seconds , minutes, onesecond, hours;

 uint8_t fasttask_trig = 0;
 uint8_t midtask_trig = 0;
 uint8_t slowtask_trig = 0;
 uint8_t logtask_trig = 0;

//setup task queues
taskqueue_t taskbuffer;
task taskarray[100];
log_tasks_e logtaskid;
fast_tasks_e fasttaskid;
mid_tasks_e midtaskid;
slow_tasks_e slowtaskid;

task logtaskarray[max_log_tasks];
task fasttaskarray[max_fast_tasks];
task midtaskarray[max_mid_tasks];
task slowtaskarray[max_slow_tasks];

task tasktorun;

typedef enum {
	car_straight = 0,
	Car_right,
	Car_left
}car_orientation_e;

car_orientation_e car_orientation;

typedef enum {
	state1 = 0,
	state2,
	state3,
	state4,
	state5,
	state6,
	state7,
	state8,
	max_state
}statemachine_state;

statemachine_state state = state1;

float eng_temp[20];
float avg_engtemp;
float temp_diaplay;
int16_t orientation;
uint32_t numberof_temp_samples = 0;

//two dimentional: 0 -- previous data 1-- new data . each data has x and y coordinate
uint32_t GPS_Data[2][2] ;
//todo: remove once eeprom available
uint32_t GPS_simu[20][2];
uint32_t nextgpsdata;
float timesincelast;
uint32_t engine_crashed;

void statemachine(void){
	switch(state){
	case state1:
		//do all peripheral init
		uart_init(BAUD_RATE);
	    state = state2;
		break;
	case state2:
		I2C_Init();
		state = state3;
			break;
	case state3:
	    TaskTimer_init();
		state = state4;
			break;
	case state4:
		rtc_Clock_Configuration();
		rtc_init();
		state = state5;
			break;
	case state5:
		accel_init();
		state = state6;
			break;
	case state6:
		led_init();
		touch_init(1 << 10);
		state = state7;
			break;
	case state7:
	    Env_Setup();
	    state = state8;
			break;
	case state8:
		//nothing to do , may call main task
	default:
			break;
	}

}

//todo: remove this function once eeprom is given by rishi
void simulate_gps(void){

	for(int i = 0; i < 2; i++){
		for(int j =0; j < 2; j ++){
			GPS_Data[i][j] = i;
		}
	}

	for(int i = 0; i < 20; i++){
		for(int j =0; j < 2; j ++){
			GPS_simu[i][j] = i*5;
		}
	}
}

float Calculate_average_temp(void){
	int i = 0;
	float avg_value = 0.0 , sum_temp = 0.0;
	for(i = 0; i < numberof_temp_samples ; i++ ){
		sum_temp += eng_temp[i];
	}
	avg_value = sum_temp/numberof_temp_samples;
	return(avg_value);
}

void task_scheduler(void){

	if(logtask_trig){  // log task gets called every 1 second (highest priority)
		//push log/eeprom task in task queue
		task_Push(&taskbuffer,logtaskarray[logtaskid]);
		task_Push(&taskbuffer,logtaskarray[logtaskid]);
		(logtaskid < max_log_tasks - 1) ? (logtaskid++) : (logtaskid = logtask1);
		logtask_trig = 0;
	}
	if(slowtask_trig ) // slow task takes high priority
	{
		//push next slow task in task queue
		task_Push(&taskbuffer,slowtaskarray[slowtaskid]);
		task_Push(&taskbuffer,slowtaskarray[slowtaskid]);
		(slowtaskid < max_slow_tasks - 1) ? (slowtaskid++) : (slowtaskid = midtask1);
	}
	else if(midtask_trig) // mid task takes mid priority
	{
		//push next mid task in task queue
		task_Push(&taskbuffer,midtaskarray[midtaskid]);
		task_Push(&taskbuffer,midtaskarray[midtaskid]);
		(midtaskid < max_mid_tasks - 1) ? (midtaskid++) : (midtaskid = midtask1);
	}
	else if(fasttask_trig) // fast task is least prio
	{
		//push next fast task in task queue
		task_Push(&taskbuffer,fasttaskarray[fasttaskid]);
		task_Push(&taskbuffer,fasttaskarray[fasttaskid]);
		(fasttaskid < max_fast_tasks -1) ? (fasttaskid++) : (fasttaskid = fasttask1);
	}
	else {
		//push next fast task in task queue
		task_Push(&taskbuffer,midtaskarray[midtask2]);
		task_Push(&taskbuffer,midtaskarray[midtask2]);
	}
}

void Task_Display(void){

	LOG_return();
	LOG_0("Time - ");
	LOG_2(" : ",minutes);
	LOG_2(" : ",seconds);
	LOG_0("\n\r");
	LOG_0("refined value - \n\r");
	LOG_2(" X_pos - ",Calculated_Position_x);
	LOG_2(" \n\r Y_pos - ",Calculated_Position_y);
	LOG_0("\n\r");
	LOG_2("Speed = ", Speed);
	LOG_0("\n\r");
	LOG_2("temp = ",temp_diaplay);
	LOG_0(" * C       ");
	LOG_0("\n\r");
	if(engine_crashed){
	LOG_0("engine heat up !!\n\r");
	R(1);
	G(0);
	B(0);
	}
	else{
		LOG_0("                 \n\r");
		R(0);
		G(0);
		B(0);
		}

	if (car_orientation == Car_right){
		LOG_0("       ___           \n\r");
		LOG_0("      /___/          \n\r");
		LOG_0("    /     /          \n\r");
		LOG_0("   /_____/           \n\r");
		LOG_0("   /___/             \n\r");
	}
	else if (car_orientation == Car_left){
		LOG_0("      ___             \n\r");
	    LOG_0("    \\ ___\\            \n\r");
	    LOG_0("    \\      \\           \n\r");
	    LOG_0("     \\ _____\\           \n\r");
	    LOG_0("       \\ ___\\           \n\r");
	}
	else{
		LOG_0("     ___             \n\r");
	    LOG_0("    |___|            \n\r");
	    LOG_0("   |     |           \n\r");
	    LOG_0("   |_____|           \n\r");
	    LOG_0("    |___|           \n\r");
	}

}


void task_CaptureGPS(void){
	// store the last read data as previous (0) data
	GPS_Data[0][0]= GPS_Data[1][0];
	GPS_Data[0][1]= GPS_Data[1][1];

	//capture gps data or read stored eeprom data
	//todo : call eeprom funtion once available
	GPS_Data[1][0]= GPS_simu[nextgpsdata][0];
	GPS_Data[1][1]= GPS_simu[nextgpsdata][1];
	(nextgpsdata < 20) ? (nextgpsdata++) : (nextgpsdata = 0);
	//LOG_0("Task - 1 \n\r");
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
}

void task_CheckEngineHealth(void){
	//check that the avg temp of engine is above a threshold
	avg_engtemp = Calculate_average_temp();
	if(temp_diaplay > Max_EngTemp_allowed){
		engine_crashed = 1;
	}
	else{
		engine_crashed = 0;
	}
	numberof_temp_samples = 0;//reset temp array
	// LOG_0("Task - 2 \n\r");
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
}


void task_UpdateDistance(void){
	//calculate the distance traveled with last captured speed in speed task
	OldTime = NewTime;
	NewTime = minutes*60 + seconds + (traveltimer * (0.000004))  ; //updated in rtc irq
	timesincelast = NewTime - OldTime; //total number of seconds since last calculation
	Distance = Speed * timesincelast; // update distance is called before update speed always so uses last captured speed value
	//LOG_0("Task - 3 \n\r");
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
}


void task_UpdateSpeed(void){
		//LOG_0("Task - 4 \n\r");
		Task_Display();
		Task_Display();
		Task_Display();
		Task_Display();
		Task_Display();
		Task_Display();
	    Task_Display();
		Task_Display();
}

void Speed_check(void){
	        touchValue[1] = touch_data(10);

			if((touchValue[1] > (touchValue[0] + 15)) && (Speed < 305)){
				Speed = Speed + 5.5;
			}
			if((touchValue[1] < (touchValue[0] - 15))  && (Speed > 15)){
				Speed = Speed - 5.4;
			}

			touchValue[0] = touchValue[1];

			if(Speed >= 320){
				Speed = 320;
			}

			if(Speed <= 2){
				Speed = 0;
			}
}

void task_UpdateDirection(void){
	//update the orientation of car using ax sensor
	 orientation = 0;
	//LOG_0("Task - 5 \n\r");
	 accel_read();

	 if( resulty < 0){
		 car_orientation = Car_right;
	 }
	 else if( resulty > 0){
		 car_orientation = Car_left;
	 }
	 else
	 {
		 car_orientation = car_straight;
	 }
	 Task_Display();
	 Task_Display();
	 Task_Display();
	 Task_Display();
	 Task_Display();
	 Task_Display();
	 Task_Display();
	 Task_Display();
}

void task_UpdateCordinate(void){
	//calculate the x and y travel depending on the distance traveled and the orientation of car
	float val;
	val = PI / 180.0;
	x_travel = Distance * cos (orientation*val);
	y_travel = Distance * sin (orientation*val);
	//LOG_0("Task - 6 \n\r");
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
}


void task_CalculatePosition(void){
	//calculate the x and y coordinate with respect to the starting gps position
    Calculated_Position_x = GPS_Data[0][0] + x_travel;
    Calculated_Position_y = GPS_Data[0][1] + y_travel;

    //update the base location with the calulated value
    GPS_Data[0][0] = Calculated_Position_x;

    Task_Display();GPS_Data[0][1] = Calculated_Position_y;
	//LOG_0("Task - 7 \n\r");
    Task_Display();
    Task_Display();
    Task_Display();
    Task_Display();
    Task_Display();
    Task_Display();
    Task_Display();
    Task_Display();
}

void task_CaptureEngineTemp(void){
	//calculate the temp value via i2c
	temp_diaplay = DS1631_Read_Temperature ();
	eng_temp[numberof_temp_samples] = temp_diaplay;
	(numberof_temp_samples < 20) ? (numberof_temp_samples++) : (numberof_temp_samples = 0);
	//LOG_0("Task - 8 \n\r");
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
	Task_Display();
}


void Env_Setup(void){
	//setup a queue to hold max 100 tasks
	taskBuff_init(&taskbuffer,100,taskarray);

	//setup array of all slow task
	slowtaskarray[slowtask1] = &task_CaptureGPS;
	//slowtaskarray[slowtask2] = &task_UpdateDirection;

	//setup array of all mid task
	midtaskarray[midtask1] = &task_CheckEngineHealth;
	midtaskarray[midtask2] = &task_UpdateDirection;

	//setup array of all fast task
	fasttaskarray[fasttask1] = &task_UpdateCordinate;
	fasttaskarray[fasttask2] = &task_CalculatePosition;
	fasttaskarray[fasttask3] = &task_CaptureEngineTemp;
	fasttaskarray[fasttask4] = &task_UpdateDistance;
	fasttaskarray[fasttask5] = &task_UpdateSpeed;
	fasttaskarray[fasttask6] = &task_CheckEngineHealth;
	fasttaskarray[fasttask7] = &task_UpdateDirection;
	fasttaskarray[fasttask8] = &task_CaptureGPS;

	//setup array of all  log task
	logtaskarray[logtask1] = &Task_Display;

	//todo: remove once eeprom is available
	simulate_gps();
	DS1631_Start_Continuos_Conversion();

}

int main(void)
{
    //eeprom_init();
	uint8_t istasktorun =0;
	touchValue[1] = 0;
	touchValue[0] = 0;
    while(1){
    	statemachine();
    	if(state == state8){
			Speed_check();
			if(onesecond){
				logtask_trig = 1;
				fasttask_trig = 0;
				midtask_trig = 0;
				slowtask_trig = 0;
				onesecond = 0;
				traveltimer = 0;
			}
			task_scheduler();
			istasktorun = task_Pop(&taskbuffer,&tasktorun);
			if(!istasktorun){
			 tasktorun = &Task_Display;
			}
			tasktorun();
		}
    }
}
