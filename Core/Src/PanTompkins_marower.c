/**********************************************************************************
	PanTompkins_marower.c
	Author: Marek Zylinski, Dec 2022
	Last Updated: Feb 2021
    License: MIT License
	-------------------------------------------
	-------------------------------------------
	Description:

	This is an float-point implementation of Pan-Tompkins beat detector for ARM
	cores. This code use a CMSIS-DSP library of common signal processing functions
	for use on Cortex-M and Cortex-A processor based devices.

	Usage:
	1. Code use library CMSIS-DSP, it can be download from GitHub repository:
	   https://github.com/ARM-software/CMSIS-DSP
	   Include it into your project
	2. Call arm_PT_init() to initialise variables
	3. Pass samples iterative to the main function arm_PT_ST (sample), function
	   return 0 if no QRS was detected or number of samples delay for detected
	   QRS. For example value 8 mean that QRS was detected 8 sample before
	   actual one

 **********************************************************************************/
#include "PanTompkins_marower.h"

#define NUM_DERIVATIVE_TAPS              5

#define BLOCK_SIZE						 1

#define NUM_IIR_Coefficients			 5

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
/* In that case must be a multiple of 16 based on arm_fir_example_f32.c */
#define NUM_DERIVATIVE_TAPS_ARRAY_SIZE              16
#else
#define NUM_DERIVATIVE_TAPS_ARRAY_SIZE              5
#endif


//Implementation of derivative as FIR filter
//The CMSIS FIR filter function requires the coefficients to be in time reversed order.
//This implements equation from errata of Pan-Tompkins paper:
//y[n] = 2x[n] - x[n-1] - x[n-3] - x[n-4]
#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
const float32_t firDerivativeCoefficients[NUM_DERIVATIVE_TAPS_ARRAY_SIZE] = {
     0.0f, 0.0f, 0.0f, 0.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.0f, 0.0f, 0.0f,-2.0f, -1.0f,  0.0f, +1.0f, +2.0f
};
#else
const float32_t firDerivativeCoefficients[NUM_DERIVATIVE_TAPS_ARRAY_SIZE] = {
		-2.0f, -1.0f, 0.0f, +1.0f, +2.0f
};
#endif

/* -------------------------------------------------------------------
 * Declare State buffer of size (numTaps + blockSize - 1)
 * ------------------------------------------------------------------- */
#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
static float32_t firStateF32[2 * BLOCK_SIZE + NUM_DERIVATIVE_TAPS - 1];
#else
static float32_t firStateF32[BLOCK_SIZE + NUM_DERIVATIVE_TAPS - 1];
#endif

//Instance structure for the floating-point FIR filter:
arm_fir_instance_f32 Derivative;

//Used Biquad Cascade IIR Filters using direct form I for high-pass and low-pass
//filter the ECG signal, filters are design as 5 and 15Hz for 360 Hz
//5 coefficients b0, b1, b2, a1, a2
//y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] + a1 * y[n-1] + a2 * y[n-2]
//Fixed-point Biquad with shift by postShift bits after accumulator
//This essentially scales the filter coefficients by 2^postShift
//the coefficients calculate for postShift == 1 with
//https://www.easycalculation.com/physics/electromagnetism/biquad-calculator.php

const float32_t iirHighPassFilterCoefficients[NUM_IIR_Coefficients] = {
		0.4782f, -0.9564f, 0.4782f,	-0.9546f, 0.45825
};

//Declaration of state array for IIR biquad cascade filter
//Each Biquad stage has 4 state variables x[n-1], x[n-2], y[n-1], and y[n-2]
//I use only one stage
float32_t highPassFilterStateF32[4];

//Instance structure for the floating-point Biquad cascade filter
arm_biquad_casd_df1_inst_f32 highPassFilter;

// for low pass filter by analogy:
//Coefficients:
const float32_t iirLowPassFilterCoefficients[NUM_IIR_Coefficients] = {
		0.00755f, 0.0151f, 0.00755f, -0.85525f, 0.3854
};

//State array:
float32_t lowPassFilterStateF32[4];

//Structure instance:
arm_biquad_casd_df1_inst_f32 lowPassFilter;

//TODO: Implement rest of needed variables: squaring and moving average (with arm)

void arm_PT_init()
{
	arm_fir_init_f32(&Derivative, NUM_DERIVATIVE_TAPS, (float32_t *)&firDerivativeCoefficients[0], &firStateF32[0], BLOCK_SIZE);
	arm_biquad_cascade_df1_init_f32 (&highPassFilter,1, (float32_t *)&iirHighPassFilterCoefficients[0], &highPassFilterStateF32[0]);
	arm_biquad_cascade_df1_init_f32 (&lowPassFilter,1, (float32_t *)&iirLowPassFilterCoefficients[0], &lowPassFilterStateF32[0]);
}


//TODO: Implement algorithm
int16_t arm_PT_ST(dataType sample)
{
	return 0;
}

int16_t arm_get_LPFilter_output()
{

	return 0;
}

int16_t arm_get_HPFilter_output()
{

	return 0;
}

int16_t arm_get_DRFilter_output()
{

	return 0;
}

int16_t arm_get_SQRFilter_output()
{

	return 0;
}

int16_t arm_get_MVFilter_output()
{
	return 0;
}

int16_t arm_get_ThI1_output()
{

	return 0;
}

int16_t arm_get_ThF1_output()
{

	return 0;
}
