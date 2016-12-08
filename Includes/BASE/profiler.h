/*
 * profile.h
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */

#ifndef SOURCES_PROFILE_H_
#define SOURCES_PROFILE_H_

#include <stdint.h>

#define DATA_LEN_MAX    5000

/********************************************************************/
/*description: this function initializes and configures
 * the timer used for task scheme      								*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void TaskTimer_init(void);

/********************************************************************/
/*description: this function stops the task scheme timer			*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void stop_TaskTimer(void);

#endif /* SOURCES_PROFILE_H_ */
