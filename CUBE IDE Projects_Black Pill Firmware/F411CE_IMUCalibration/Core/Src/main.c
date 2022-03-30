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
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;

TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

/* USER CODE BEGIN PV */
extern uint8_t buffer[64]; //receive buffer from USB
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM11_Init(void);
static void MX_TIM9_Init(void);
static void MX_TIM5_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM10_Init(void);
/* USER CODE BEGIN PFP */

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
	MX_USB_DEVICE_Init();
	MX_USART1_UART_Init();
	MX_ADC1_Init();
	MX_I2C1_Init();
	MX_TIM11_Init();
	MX_TIM9_Init();
	MX_TIM5_Init();
	MX_DMA_Init();
	MX_TIM10_Init();
	/* USER CODE BEGIN 2 */

	//Initialization of IMU Variables
	static const uint8_t BNO055_ADDR = 0x28 << 1; //Left shift needed due to 8-bit communication
	static const uint8_t EUL_ADDR = 0x1A; //Found in BNO055 Documentation
	static const uint8_t PWR_MODE = 0x3E; //BNO055 Doc
	static const uint8_t OPR_MODE = 0x3D; //BNO055 Doc
	static const uint8_t UNIT_SEL = 0x3B; //BNO055 Doc
	static const uint8_t AXIS_MAP_SIGN = 0x42; //BNO055 Doc
	static const uint8_t AXIS_MAP_CONFIG = 0x41; //BNO055 Doc
	static const uint8_t GYR_ADDR = 0x14; //Address starting with angular velocity + angular position after 12 bytes
	static const uint8_t CAL_STATUS = 0x35; //BNO055 Doc
	static const uint8_t CAL_CONSTANTS = 0x55;
	static const uint8_t CHIP_ID = 0x00;

	//Simplify this whole section? Should be able to make only one calculation from buf to float value
	int16_t eulheading = 0; //Could I simplify this? probably.. Just make sure it works for now
	int16_t eulroll = 0;
	int16_t eulpitch = 0;

	int16_t gyrx = 0;
	int16_t gyry = 0;
	int16_t gyrz = 0;

	//IMU Parameters:
	float EulerX = 0; //Estimated angular displacement of X axis rotation (gamma)
	float EulerY = 0; //Estimated angular displacement of Y axis rotation (beta)
	float EulerZ = 0; //Estimated angular displacement of Z axis rotation

	float AngularVelX = 0; //Estimated angular velocity of X axis rotation (gamma_dot)
	float AngularVelY = 0; //Estimated angular velocity of Y axis rotation (beta_dot)
	float AngularVelZ = 0; //Estimated angular velocity of Z axis rotation

	HAL_StatusTypeDef ret; //StatusDef to return any errors with IMU communication

	char str[64] = {0}; //for messages to send through I2C

	uint8_t buf[24] = {0}; //Modify size to work with class
	uint8_t calibration = 0;
	char UXinput = 0;

	//Clear buffer and message for next prompt
	memset(buffer, '\0', sizeof(buffer));  // clear the buffer for next message

	HAL_Delay(1000);

	//Rest of initialization
	//Note: Since during system start-up (no multitasking requirement), HAL_Delays are used.

	buf[0] = 0x00; //Put IMU Into Config Mode (How... did I forget this...)

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	HAL_Delay(100);

	buf[0] = 0x00; //Test for PWR MODE

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, PWR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	HAL_Delay(100);

	buf[0] = 0x00; //Set UNIT_SEL for degrees in model

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, UNIT_SEL, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	HAL_Delay(100);

	buf[0] = 0x01; //Configure Axis to be negative sign of both y and z axes due to how BNO055 is attached to platform.

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, AXIS_MAP_SIGN, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	HAL_Delay(100);

	buf[0] = 0x24; //Configure Axis.

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, AXIS_MAP_CONFIG, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	//*====================================*
	// WRITE CALIBRATION CONSTANTS TO IMU
	//*====================================*

	HAL_Delay(100);

	buf[0] = 0x0C; //Put IMU into IMU config mode, starts IMU.

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{

	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{

		HAL_Delay(1000);

		ret = HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, CAL_STATUS, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
		if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
		{
			sprintf(str,"Error, cannot connect to IMU\n");
			CDC_Transmit_FS((uint8_t *) str, strlen(str));
		}
		else
		{
			sprintf(str,"Calibration Register: %u\n", buf[0]);
			CDC_Transmit_FS((uint8_t *) str, strlen(str));
		}

		if (buf[0] == 60)
		{
			sprintf(str,"IMU Mode fully calibrated. Gathering values...\n");
			CDC_Transmit_FS((uint8_t *) str, strlen(str));

			//Set IMU into CONFIG mode:
			buf[0] = 0x00; //Put IMU into IMU config mode, starts IMU.

			ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
			if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
			{
				sprintf(str,"Error, cannot connect to IMU\n");
				CDC_Transmit_FS((uint8_t *) str, strlen(str));
			}

			HAL_Delay(10);

			//Read from calibration constant registers:
			ret = HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, CAL_CONSTANTS, I2C_MEMADD_SIZE_8BIT, buf, 22, HAL_MAX_DELAY);
			if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
			{
				sprintf(str,"Error, cannot connect to IMU\n");
				CDC_Transmit_FS((uint8_t *) str, strlen(str));
			}
			else
			{
				sprintf(str,"Values of Calibration Constants:\n");
				CDC_Transmit_FS((uint8_t *) str, strlen(str));

				for(int i = 0; i < 22; i++)
				{
					sprintf(str,"Buffer [%u]: %u\n", i, buf[i]);
					CDC_Transmit_FS((uint8_t *) str, strlen(str));
					HAL_Delay(20);
				}

				HAL_Delay(10000);

				sprintf(str,"Now, value readouts. Press c to read new values, e to end.\n");
				CDC_Transmit_FS((uint8_t *) str, strlen(str));

				//Set IMU into NDOF mode:
				buf[0] = 0x0C; //Put IMU into NDOF, starts IMU.

				ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
				if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
				{
					sprintf(str,"Error, cannot connect to IMU\n");
					CDC_Transmit_FS((uint8_t *) str, strlen(str));
				}

				HAL_Delay(10);

				while(1)
				{
					HAL_Delay(1000);

					HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_ADDR, I2C_MEMADD_SIZE_8BIT, buf, 12, HAL_MAX_DELAY);

					gyrx = (int16_t)buf[0]+(buf[1] << 8); //Bit-shift for MSB register
					gyry = (int16_t)buf[2]+(buf[3] << 8); //Bit-shift for MSB register
					gyrz = (int16_t)buf[4]+(buf[5] << 8); //Bit-shift for MSB register

					eulheading = (int16_t)buf[6]+(buf[7] << 8); //Bit-shift for MSB register
					eulroll = (int16_t)buf[8]+(buf[9] << 8); //Bit-shift for MSB register
					eulpitch = (int16_t)buf[10]+(buf[11] << 8); //Bit-shift for MSB register

					EulerZ = (float)eulheading/(float)16; //Convert to 16 LSB to 1 Degree
					EulerY = (float)eulroll/(float)16; //Convert to 16 LSB to 1 Degree
					EulerX = -(float)eulpitch/(float)16; //Convert to 16 LSB to 1 Degree

					AngularVelX = -(float)gyrx/(float)16;
					AngularVelY = -(float)gyry/(float)16;
					AngularVelZ = (float)gyrz/(float)16;

					//Stretch what an Interrupt can do to see what's possible
					sprintf(str,"X: %.2f Xdot: %.2f Y: %.2f Ydot: %.2f\n",
							EulerX, AngularVelX, EulerY, AngularVelY);

					CDC_Transmit_FS((uint8_t *) str, strlen(str));

					if (buffer[0] != '\0')
					{

						UXinput = '\0';

						UXinput = buffer[0];

						//Clear buffer and message for next prompt
						memset(buffer, '\0', sizeof(buffer));  // clear the buffer for next message

						if(UXinput == 'c')
						{
							//Read from calibration constant registers:
							ret = HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, CAL_CONSTANTS, I2C_MEMADD_SIZE_8BIT, buf, 22, HAL_MAX_DELAY);
							if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
							{
								sprintf(str,"Error, cannot connect to IMU\n");
								CDC_Transmit_FS((uint8_t *) str, strlen(str));
							}
							else
							{
								sprintf(str,"Values of New Calibration Constants:\n");
								CDC_Transmit_FS((uint8_t *) str, strlen(str));

								for(int i = 0; i < 22; i++)
								{
									sprintf(str,"Buffer [%u]: %u\n", i, buf[i]);
									CDC_Transmit_FS((uint8_t *) str, strlen(str));
									HAL_Delay(5);
								}

								HAL_Delay(10000);
								sprintf(str,"Now, value readouts. Press c to read new values, e to end.\n");
								CDC_Transmit_FS((uint8_t *) str, strlen(str));
							}
						}
						else if (UXinput == 'e')
						{
							sprintf(str,"Program Ending.");
							CDC_Transmit_FS((uint8_t *) str, strlen(str));

							HAL_Delay(1000);

							return;
						}
					}
				}



			}
		}
	}
}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
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
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 4294967295;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief TIM9 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM9_Init(void)
{

  /* USER CODE BEGIN TIM9_Init 0 */

  /* USER CODE END TIM9_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};

  /* USER CODE BEGIN TIM9_Init 1 */

  /* USER CODE END TIM9_Init 1 */
  htim9.Instance = TIM9;
  htim9.Init.Prescaler = 96-1;
  htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim9.Init.Period = 65535;
  htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM9_Init 2 */

  /* USER CODE END TIM9_Init 2 */

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
  htim10.Init.Prescaler = 96-1;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 150-1;
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
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 96 - 1;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 10000 - 1;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

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
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
  /* DMA2_Stream7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

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
  HAL_GPIO_WritePin(GPIOB, TS_LL_Pin|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : TS_LL_Pin PB1 PB2 PB10 */
  GPIO_InitStruct.Pin = TS_LL_Pin|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

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

