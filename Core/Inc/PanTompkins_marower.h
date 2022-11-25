#ifndef _PANTOMPKINS_MAROWER_
#define _PANTOMPKINS_MAROWER_

#include "arm_math.h"
#include <stdint.h>
typedef int16_t dataType;

void arm_PT_init();
int16_t arm_PT_ST(dataType datum);

/**********************************************************************
Debugging Functions
 **********************************************************************/
int16_t arm_get_LPFilter_output();
int16_t arm_get_HPFilter_output();
int16_t arm_get_DRFilter_output();
int16_t arm_get_SQRFilter_output();
int16_t arm_get_MVFilter_output();
int16_t arm_get_ThI1_output();
int16_t arm_get_ThF1_output();
#endif
