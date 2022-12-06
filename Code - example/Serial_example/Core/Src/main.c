/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "usbd_cdc_if.h"
#include "PanTompkins_hooman650.h"
#include "PanTompkins_rafaelmmoreira.h"
#include "PanTompkins_marower.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct State{
	uint8_t dataType;
	uint8_t selectedImplementation;
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define intasString 0x31
#define int16asBytes 0x32

#define hoomam650 0x31
#define rafalmmoreira 0x32
#define marower 0x33

#define changeDataFormat 0x41
#define changeSelectedAlgorithm 0x42

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim16;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

struct State applicationState;

unsigned char str[250];

uint8_t USBBuffer[2048];
uint8_t USBReciveBuffer[2048];
uint16_t USBBuffer_index = 0;

void sendUSBData (uint8_t* Buf, uint16_t Len)
{
	memcpy(&USBBuffer[USBBuffer_index], Buf, Len);
	USBBuffer_index += Len;
	if (USBBuffer_index>2000)
	{
		while (CDC_Transmit_FS(USBBuffer, USBBuffer_index)!= USBD_OK){};
		USBBuffer_index = 0;
	}
}

uint16_t findStrEnd ()
{
	uint16_t end = 10;
	while (str[end]!='\0')
	{
		end++;
		if (end == 250)
		{
			break;
		}
	}
	return end;
}



void parseLine (uint8_t* Buf, uint32_t Len)
{//Function parse one line from serial port
	//In line can be command or data
	if (Len>6)
	{//command mast be longer than 6 bytes
		if (Buf[0]==0x2B && Buf[1]==0x2B && Buf[2]==0x2B)
		{//three ++ indicate command
			switch (Buf[3])
			{
			case changeDataFormat:
				applicationState.dataType = Buf[4];
				sprintf(str,"OK, done.   \r\n");
				while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
				break;
			case changeSelectedAlgorithm:
				applicationState.selectedImplementation = Buf[4];
				if (applicationState.selectedImplementation == hoomam650)
				{
					PT_init();
					sprintf(str,"OK, done.   \r\n");
					while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
				}
				if (applicationState.selectedImplementation == rafalmmoreira)
				{
					Rafael_init();
					sprintf(str,"OK, done.   \r\n");
					while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
				}
				if (applicationState.selectedImplementation == marower)
				{
					arm_PT_init();
					sprintf(str,"OK, done.   \r\n");
					while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
				}
				break;
			default:
				sprintf(str,"error...\r\n");
				while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
				break;
			}
			return;
		}
	}

	int16_t dataSample;
	switch (applicationState.dataType)
	{//decode data
	case int16asBytes:
		dataSample = (Buf[0]<<8)|Buf[1];

		break;
	case intasString:
		dataSample = atoi (Buf);

		break;
	default:
		sprintf(str,"error...\r\n");
		while (CDC_Transmit_FS(str, findStrEnd())!= USBD_OK){};
		return;
		break;
	}

	int16_t delay;
	int16_t s1;
	int16_t s2;
	int16_t s3;
	uint16_t s4;
	uint16_t s5;
	int16_t ThI1;
	int16_t ThF1;

	float32_t s1_f32;
	float32_t s2_f32;
	float32_t s3_f32;
	float32_t s4_f32;
	float32_t s5_f32;
	float32_t ThI1_f32;
	float32_t ThF1_f32;
	switch (applicationState.selectedImplementation)
	{//decode data
	case hoomam650:
		delay = PT_StateMachine (dataSample);
		s1 = PT_get_LPFilter_output();
		s2 = PT_get_HPFilter_output();
		s3 = PT_get_DRFilter_output();
		s4 = PT_get_SQRFilter_output();
		s5 = PT_get_MVFilter_output();
		ThI1 = PT_get_ThI1_output();
		ThF1 = PT_get_ThF1_output();
		sprintf(str,"%d,%d,%d,%d,%u,%u,%u,%d\r\n", delay, s1, s2, s3, s4, s5, ThI1, ThF1);
		sendUSBData (str, findStrEnd());
		break;
	case rafalmmoreira:
		delay = Rafael_PanTompkins(dataSample);
		s1 = Rafael_get_LPFilter_output();
		s2 = Rafael_get_HPFilter_output();
		s3 = Rafael_get_DRFilter_output();
		s4 = Rafael_get_SQRFilter_output();
		s5 = Rafael_get_MVFilter_output();
		ThI1 = Rafael_get_ThI1_output();
		ThF1 = Rafael_get_ThF1_output();
		sprintf(str,"%d,%d,%d,%d,%d,%d,%d,%d\r\n", delay, s1, s2, s3, s4, s5, ThI1, ThF1);
		sendUSBData (str, findStrEnd());
		break;
	case marower:
		delay = arm_PT_ST(dataSample);
		s1_f32 = arm_get_LPFilter_output();
		s2_f32 = arm_get_HPFilter_output();
		s3_f32 = arm_get_DRFilter_output();
		s4_f32 = arm_get_SQRFilter_output();
		s5_f32 = arm_get_MVFilter_output();
		ThI1_f32 = arm_get_ThI1_output();
		ThF1_f32 = arm_get_ThF1_output();
		sprintf(str,"%d,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f\r\n", delay, s1_f32, s2_f32, s3_f32, s4_f32, s5_f32, ThI1_f32, ThF1_f32);
		sendUSBData (str, findStrEnd());
		break;
	default:
		return;
		break;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  applicationState.dataType = int16asBytes;
  applicationState.selectedImplementation = marower;
  arm_PT_init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_Device_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  extern uint32_t byteInBuffer;
  extern uint8_t* bufferPointer;
  extern uint8_t bufferFlag;
  HAL_TIM_Base_Start_IT(&htim16);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if ((byteInBuffer>0) && (bufferFlag == 1))
	 	  {
		  	  memcpy(&USBReciveBuffer[0],bufferPointer, byteInBuffer);
		  	  uint32_t dataCount = byteInBuffer;
		  	  byteInBuffer = 0;
	 		  uint32_t count = 0;
	 		  uint32_t i = 0;
	 		  uint32_t index = 0;
	 		  do
	 		  {
	 			  i++;
	 			  count++;
	 			  if (USBReciveBuffer[i]=='\n')
	 			  {
	 				 count++;
	 				 parseLine (&USBReciveBuffer[index], count);
	 				 index += count;
	 				 i++;
	 				 count = 0;
	 			  }
	 		  }while (i<dataCount);

	 	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 639;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 100;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim16)
  {
	  if (USBBuffer_index> 0)
	  {
		  while (CDC_Transmit_FS(USBBuffer, USBBuffer_index)!= USBD_OK){};
		  USBBuffer_index = 0;
	  }
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
