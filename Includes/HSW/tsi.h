/*
 * tsi.h
 *
 *  Created on: Nov 29, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_FIRMWARE_I_TSI_H_
#define INCLUDES_FIRMWARE_I_TSI_H_

void touch_init(uint32_t channel_mask);
int touch_data(int channel);
inline static void scan_start(int channel);
inline static uint16_t scan_data(void);
void TSI0_IRQHandler(void);



#endif /* INCLUDES_FIRMWARE_I_TSI_H_ */
