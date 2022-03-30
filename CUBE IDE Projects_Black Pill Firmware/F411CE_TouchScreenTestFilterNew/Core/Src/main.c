/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim10;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */
void insertionSort(unsigned int arr[], int n);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USB_DEVICE_Init();
  MX_TIM10_Init();
  /* USER CODE BEGIN 2 */

  	//Start Touchscreen
	HAL_ADC_Start(&hadc1);

	unsigned int xposADC[4] = {0};
	unsigned int xposADCCurrent = 0;
	float xpos = 0;
	float prevxpos = 0;
	float xvel = 0;
	unsigned int yposADC[4] = {0};
	unsigned int yposADCCurrent = 0;
	float ypos = 0;
	float prevypos = 0;
	float yvel = 0;
	float delT = 0;

	uint32_t prevtime = 0;
	uint32_t currtime = 0;
	uint8_t contact = 0;
	uint8_t state = 0;

	uint8_t samplenum = 0;
	const int totalsamples = 4;

	//Sprintf test:
	char str[80];
	uint8_t buf[128];

	//Touchscreen Initialization: Start with right side energized.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET); //Pin B0 corresponds to LL
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); // Pin B1 corresponds to UL
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET); // Pin B2 corresponds to LR
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); //Pin B10 corresponds to UR

	HAL_Delay(5000);

	HAL_TIM_Base_Start(&htim10); //Remember to include this to start timer channel

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		//Blinking To Verify Integrity
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

		//TouchScreen Test
		xposADC[samplenum] = HAL_ADC_GetValue(&hadc1);

		//Toggle necessary pins to change to measure Y Value, changing to have top HIGH and bottom LOW
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1); // Pin A2 corresponds to UL
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2); // Pin A4 corresponds to LR

		delay_us(150);

		yposADC[samplenum] = HAL_ADC_GetValue(&hadc1);

		//Detection if in contact:
		if (xposADC[samplenum] < 750 && yposADC[samplenum] < 750)
		{
			contact = 0;
		}
		else
		{
			//Initialize variables
			contact = 1;
		}

		//Toggle back to measure X.
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1); // Pin A2 corresponds to UL
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2); // Pin A4 corresponds to LR


		//State machine for touchscreen logic
		if(state == 0)
		{

			//Detection if in contact:
			if (contact == 0)
			{
				sprintf((char*)buf,"No Contact\r\n");
				CDC_Transmit_FS(buf, strlen((char*)buf));
			}
			else
			{
				//Initialize variables
				state = 1;

				prevxpos = xposADC[samplenum]*0.154755+(-304.374202);
				prevypos = yposADC[samplenum]*0.117449+(-231.425424); //DO LIBRARY, TRUST

				samplenum++;

				prevtime = HAL_GetTick();

				sprintf((char*)buf,"Position (mm): %02f, %02f,\nVelocity (mm/s): %02f, %02f\n",xpos,ypos,xvel,yvel);
				CDC_Transmit_FS(buf, strlen((char*)buf));
			}

		}
		else if (state == 1)
		{
			if (contact == 1)
			{
				samplenum++;

				if ((int) samplenum == totalsamples)
				{
					sprintf((char*)buf,"First couple X: %u, %u, %u, %u\n",
							xposADC[0],xposADC[1],xposADC[2],xposADC[3]);

					CDC_Transmit_FS(buf, strlen((char*)buf)); //Output to PC

					//Implement Insertion Sorting Method for now, https://www.geeksforgeeks.org/insertion-sort/:

					//Try merge or quick sort**
					insertionSort(xposADC, totalsamples);
					insertionSort(yposADC, totalsamples);

					sprintf((char*)buf,"First couple X post Sort: %u, %u, %u, %u\n",
							xposADC[0],xposADC[1],xposADC[2],xposADC[3]);

					CDC_Transmit_FS(buf, strlen((char*)buf)); //Output to PC

					//Average inner values
					xposADCCurrent = (xposADC[2]+xposADC[3])/((uint16_t)2);

					yposADCCurrent = (yposADC[2]+yposADC[3])/((uint16_t)2);

					xpos = xposADCCurrent*0.160190+(-312.850151);
					ypos = yposADCCurrent*0.120061+(-237.119838);

					currtime = HAL_GetTick();

					delT = (currtime-prevtime)/(float)1000;

					xvel = (xpos-prevxpos)/(delT);
					yvel = (ypos-prevypos)/(delT);

					sprintf((char*)buf,"Position (mm): %.2f, %.2f,\nVelocity (mm/s): %.2f, %.2f\nxposADC: %u\nTicks: %u\n"
							,xpos,ypos,xvel,yvel,xposADCCurrent,currtime);

					CDC_Transmit_FS(buf, strlen((char*)buf));

					samplenum = 0;
					prevxpos = xpos;
					prevypos = ypos;
					prevtime = currtime;
					__HAL_TIM_SET_COUNTER(&htim10,0);  // set the counter value a 0
				}

			}
			else
			{
				sprintf((char*)buf,"No Contact\r\n");
				CDC_Transmit_FS(buf, strlen((char*)buf));
			}
		}

		HAL_Delay(500);

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief TIM10 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM10_Init(void)
{

  /* USER CODE BEGIN TIM10_Init 0 */

  /* USER CODE END TIM10_Init 0 */

  /* USER CODE BEGIN TIM10_Init 1 */

  /* USER CODE END TIM10_Init 1 */
  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 16 - 1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 65536 - 1;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM10_Init 2 */

  /* USER CODE END TIM10_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

//From: https://www.geeksforgeeks.org/insertion-sort/
void insertionSort(unsigned int arr[], int n)
{

	uint8_t buf[128];

    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    sprintf((char*)buf,"First couple X/Y in Sort After: %u, %u, %u, %u\n",
			arr[0],arr[1],arr[2],arr[3]);

    CDC_Transmit_FS(buf, strlen((char*)buf));

}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim10,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim10) < us);  // wait for the counter to reach the us input in the parameter
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

