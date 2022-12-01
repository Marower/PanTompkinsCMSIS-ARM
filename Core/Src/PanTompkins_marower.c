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

	Include:
	1. Code use library CMSIS-DSP, it can be download from GitHub repository:
	   https://github.com/ARM-software/CMSIS-DSP
	   Include it into your project. You'll need to add the paths: Include,
	   PrivateInclude and selected files from source. In each source folder (like
	   BasicMathFunctions), you'll see files with no _datatype suffix and no ARM
	   prefix (like BasicMathFunctions.c and BasicMathFunctionsF16.c).
	Usage:
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


//Time constants of Pan-Tompkins Algorith
//Moving Average window
//150ms for 360 Sa/s
#define MovingAverageSampleCount 54
//Latency after QRS
//200ms for 360Sa/s
#define latencyDelayTreshold 72
//Emergency restart in oryginal paper this was implemented as look-back
//sample count corresponding to 4000ms for 360Sa/s
#define latencyTreshold 1440

//Instance structure for the floating-point FIR filter:
arm_fir_instance_f32 Derivative;
//derivative filter
float32_t derivativeBuffer[NUM_DERIVATIVE_TAPS_ARRAY_SIZE];
float32_t derivativeOutput[0];

//Used Biquad Cascade IIR Filters using direct form I for high-pass and low-pass
//filter the ECG signal, filters are design as 5 and 15Hz for 360 Hz
//5 coefficients b0, b1, b2, a1, a2
//y[n] = b0 * x[n] + b1 * x[n-1] + b2 * x[n-2] - a1 * y[n-1] - a2 * y[n-2]
//Fixed-point Biquad with shift by postShift bits after accumulator
//This essentially scales the filter coefficients by 2^postShift
//the coefficients calculate for postShift == 1 with
//https://www.easycalculation.com/physics/electromagnetism/biquad-calculator.php
//a1 and a2 has different sign in calculator and CMSIS-DSP

const float32_t iirHighPassFilterCoefficients[NUM_IIR_Coefficients] = {
		0.4782f, -0.9564f, 0.4782f,	0.9546f, -0.45825
};

//Declaration of state array for IIR biquad cascade filter
//Each Biquad stage has 4 state variables x[n-1], x[n-2], y[n-1], and y[n-2]
//I use only one stage
float32_t highPassFilterStateF32[4];

//Instance structure for the floating-point Biquad cascade filter
arm_biquad_casd_df1_inst_f32 highPassFilter;

float32_t highPassFilterResult;

// for low pass filter by analogy:
//Coefficients:
const float32_t iirLowPassFilterCoefficients[NUM_IIR_Coefficients] = {
		0.00755f, 0.0151f, 0.00755f, 0.85525f, -0.3854
};

//State array:
float32_t lowPassFilterStateF32[4];

//Structure instance:
arm_biquad_casd_df1_inst_f32 lowPassFilter;

float32_t lowPassFilterResult;

//square value
float32_t squaredValue;

//moving average buffer
int movingAverageBufferIndex = 0;
float32_t movingAverageBuffer[MovingAverageSampleCount];
float32_t meanValue;

void putOnMovingAverageBuffer (float32_t sample)
{
	movingAverageBuffer[movingAverageBufferIndex] = sample;
	movingAverageBufferIndex++;
	if (movingAverageBufferIndex==MovingAverageSampleCount)
	{
		movingAverageBufferIndex = 0;
	}
}

void arm_PT_init()
{
	//Initiate filter function
	arm_fir_init_f32(&Derivative, NUM_DERIVATIVE_TAPS, (float32_t *)&firDerivativeCoefficients[0], &firStateF32[0], BLOCK_SIZE);
	arm_biquad_cascade_df1_init_f32 (&highPassFilter,1, (float32_t *)&iirHighPassFilterCoefficients[0], &highPassFilterStateF32[0]);
	arm_biquad_cascade_df1_init_f32 (&lowPassFilter,1, (float32_t *)&iirLowPassFilterCoefficients[0], &lowPassFilterStateF32[0]);
	//Reset buffors
	for (int i = 0; i<NUM_DERIVATIVE_TAPS_ARRAY_SIZE; i++)
	{
		derivativeBuffer[i]=0;
	}
	movingAverageBufferIndex=0;
	for (int i = 0; i<MovingAverageSampleCount; i++)
	{
		movingAverageBuffer[i] = 0;
	}
}

float previousMean = 0, TresholdI = 0, SignalLevelI = 0, NoiseLevelI = 0;
float previousSignalPeak = 0, TresholdF = 0, SignalLevelF = 0, NoiseLevelF = 0;
uint16_t peakTimeDelay = 0, latencyDelay = 0;
int16_t arm_PT_ST(int16_t sample)
{
	float32_t newSample = (float)sample;
	//low pass filter operation
	arm_biquad_cascade_df1_f32 (&lowPassFilter, &newSample,&lowPassFilterResult,1);
	//high pass filter operation
	arm_biquad_cascade_df1_f32 (&highPassFilter, &lowPassFilterResult,&highPassFilterResult,1);
	//Derivative with FIR filter
	//putOnMovingAverageBuffer(lowPassFilterResult);

	//Store potential peak value (QRS can be also minimum or maximum)
	float potentialPeak = lowPassFilterResult*lowPassFilterResult;
	if (potentialPeak>previousSignalPeak)
	{//Store maximum of squared signal
		previousSignalPeak = potentialPeak;
		peakTimeDelay = 0;
	}
	peakTimeDelay++;
	if (latencyDelay < latencyTreshold)
	{
		latencyDelay++;
	}
	else
	{//If peak wasn't find in given time restart
		latencyDelay = 0;
		arm_PT_init();
	}
	arm_fir_f32 (&Derivative,&lowPassFilterResult,&derivativeOutput[0],BLOCK_SIZE);
	//Square the value
	squaredValue = derivativeOutput[0] * derivativeOutput[0];
	//Compute moving average
	putOnMovingAverageBuffer(squaredValue);
	arm_mean_f32 (&movingAverageBuffer[0], MovingAverageSampleCount, &meanValue);

	//Detection of maximum in moving average signal
	if (meanValue>previousMean)
	{//This is not maximum
		previousMean = meanValue;
	}
	else
	{//Lets analysis maximum in integration signal
		if ((previousMean > TresholdI) && (latencyDelay > latencyDelayTreshold))
		{//It's potential QRS
			if (previousSignalPeak>TresholdF)
			{//If peak is above threshold it's QRS
				SignalLevelF = 0.125*previousSignalPeak + 0.875*SignalLevelF;
				TresholdF = NoiseLevelF + 0.25 * (SignalLevelF - NoiseLevelF);

				SignalLevelI = 0.125*meanValue + 0.875*SignalLevelI;
				TresholdI = NoiseLevelI + 0.25 * (SignalLevelI - NoiseLevelI);
				previousSignalPeak = 0;
				previousMean = 0;
				latencyDelay = 0;
				return peakTimeDelay;

			}
			else
			{//It's noise peak
				NoiseLevelF = 0.125*previousSignalPeak + 0.875*NoiseLevelI;
				TresholdF = NoiseLevelF + 0.25 * (SignalLevelF - NoiseLevelF);

				NoiseLevelI = 0.125*meanValue + 0.875*NoiseLevelI;
				TresholdI = NoiseLevelI + 0.25 * (SignalLevelI - NoiseLevelI);

				previousSignalPeak = 0;
				previousMean = 0;
			}
		}
		else
		{//It's just noise
			NoiseLevelF = 0.125*previousSignalPeak + 0.875*NoiseLevelI;
			TresholdF = NoiseLevelF + 0.25 * (SignalLevelF - NoiseLevelF);

			NoiseLevelI = 0.125*meanValue + 0.875*NoiseLevelI;
			TresholdI = NoiseLevelI + 0.25 * (SignalLevelI - NoiseLevelI);

			previousSignalPeak = 0;
			previousMean = 0;
		}
	}

	return 0;
}

float32_t arm_get_LPFilter_output()
{

	return lowPassFilterResult;
}

float32_t arm_get_HPFilter_output()
{

	return highPassFilterResult;
}

float32_t arm_get_DRFilter_output()
{

	return derivativeOutput[0];
}

float32_t arm_get_SQRFilter_output()
{

	return squaredValue;
}

float32_t arm_get_MVFilter_output()
{
	return meanValue;
}

float32_t arm_get_ThI1_output()
{

	return TresholdI;
}

float32_t arm_get_ThF1_output()
{

	return TresholdF;
}
