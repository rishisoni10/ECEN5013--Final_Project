/*
 * tsi.h
 *
 *  Created on: Nov 29, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_FIRMWARE_I_TSI_H_
#define INCLUDES_FIRMWARE_I_TSI_H_

/********************************************************************/
/*description: this function initializes the specified TSI channel.	*/
/*parameter: channel   		 								        */
/*return:    void								                    */
/********************************************************************/
void touch_init(uint32_t channel_mask);

/********************************************************************/
/*description: this function reads the value from specified TSI channel.	*/
/*parameter: channel   		 								        */
/*return:    void								                    */
/********************************************************************/
int touch_data(int channel);

/********************************************************************/
/*description: this function starts the conversion for specified TSI channel.	*/
/*parameter: channel   		 								        */
/*return:    void								                    */
/********************************************************************/
inline static void scan_start(int channel);
inline static uint16_t scan_data(void);
void TSI0_IRQHandler(void);



#endif /* INCLUDES_FIRMWARE_I_TSI_H_ */
