#ifndef _PANTOMPKINS_MAROWER_
#define _PANTOMPKINS_MAROWER_

#include <stdint.h>
#include "arm_math.h"

void arm_PT_init();
int16_t arm_PT_ST(int16_t datum);

/**********************************************************************
Debugging Functions
 **********************************************************************/
float32_t arm_get_LPFilter_output();
float32_t arm_get_HPFilter_output();
float32_t arm_get_DRFilter_output();
float32_t arm_get_SQRFilter_output();
float32_t arm_get_MVFilter_output();
float32_t arm_get_ThI1_output();
float32_t arm_get_ThF1_output();
#endif
