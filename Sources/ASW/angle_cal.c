
#include "ASW/angle_cal.h"
#include "main.h"

extern signed short resultx, resulty, resultz;
extern int16_t orientation;

void angle_calculation(void)
 {
	if(resulty < 0){
		orientation = 15;
	}
	else {
		orientation = 85;
	}
 }

