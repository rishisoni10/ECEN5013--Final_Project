/*
 * ds1631.h
 *
 *  Created on: 20-Nov-2016
 *      Author: Vikhyat
 */

#ifndef DS1631_H_
#define DS1631_H_

#define DS1631_SLAVE_ID 0x48
#define CMD_START_CONVERSION 0x51
#define CMD_READ_TEMP 0xAA

void DS1631_Start_Continuos_Conversion (void);
float DS1631_Read_Temperature (void);


#endif
