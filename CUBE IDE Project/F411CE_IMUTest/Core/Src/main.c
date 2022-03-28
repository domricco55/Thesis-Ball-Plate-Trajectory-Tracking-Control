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
#include <string.h> //For strcpy
#include <stdio.h> //For sprintf (even though use it w/o)
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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static const uint8_t BNO055_ADDR = 0x28 << 1; //Left shift needed due to 8-bit communication
static const uint8_t EUL_ADDR = 0x1A; //Found in BNO055 Documentation
static const uint8_t PWR_MODE = 0x3E; //BNO055 Doc
static const uint8_t OPR_MODE = 0x3D; //BNO055 Doc
static const uint8_t UNIT_SEL = 0x3B; //BNO055 Doc
static const uint8_t AXIS_MAP_SIGN = 0x42; //BNO055 Doc
static const uint8_t AXIS_MAP_CONFIG = 0x41; //BNO055 Doc
static const uint8_t GYR_ADDR = 0x14; //Address starting with angular velocity + angular position after 12 bytes
static const uint8_t CAL_STATUS = 0x35; //BNO055 Doc
static const uint8_t CHIP_ID = 0x00;
static const uint8_t CAL_CONSTANTS = 0x55;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  HAL_StatusTypeDef ret;
  uint8_t buf[20]; //This is for UART

  int16_t gyrx = 0;
  float gyrxout = 0;

  int16_t gyry = 0;
  float gyryout = 0;

  int16_t gyrz = 0;
  float gyrzout = 0;

  int16_t eulheading = 0;
  float eulheadingout = 0;

  int16_t eulroll = 0;
  float eulrollout = 0;

  int16_t eulpitch = 0;
  float eulpitchout = 0;

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  HAL_Delay(1000);

  buf[0] = 0x00; //Test for PWR MODE

  ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, PWR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
  if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
  		{
  			strcpy((char*) buf, "Error Tx PWR MODE\r\n");
  			CDC_Transmit_FS(buf, strlen((char*)buf));
  		}

  HAL_Delay(1000);

  buf[0] = 0x00; //Put IMU Into Config Mode (How... did I forget this...)

  ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
  if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
  		{
  			strcpy((char*) buf, "Error Tx CONFIG\r\n");
  			CDC_Transmit_FS(buf, strlen((char*)buf));
  		}

  HAL_Delay(1000);

  buf[0] = 0x00; //Set UNIT_SEL for radians in model

   ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, UNIT_SEL, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
   if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
   		{
   			strcpy((char*) buf, "Error Tx UNIT_SEL\r\n");
   			CDC_Transmit_FS(buf, strlen((char*)buf));
   		}

  HAL_Delay(1000);

  buf[0] = 0x01; //Configure Axis to be negative sign of both y and z axes due to how BNO055 is attached to platform.

	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, AXIS_MAP_SIGN, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
		{
			strcpy((char*) buf, "Error Tx AXIS_MAP_SIGN\r\n");
			CDC_Transmit_FS(buf, strlen((char*)buf));
		}

  HAL_Delay(1000);

  buf[0] = 0x24; //Configure Axis.

  	ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, AXIS_MAP_CONFIG, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
  	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
  		{
  			strcpy((char*) buf, "Error Tx AXIS_MAP_CONFIG\r\n");
  			CDC_Transmit_FS(buf, strlen((char*)buf));
  		}

    HAL_Delay(1000);

    //Change based on what is found from calibration project.
    uint8_t calibconstants[24] = {0, 0, 124, 255, 1, 0, 198, 0, 161, 0, 14, 0, 255, 255, 253, 255, 255, 255, 232, 3, 98, 1};

    ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, CAL_CONSTANTS, I2C_MEMADD_SIZE_8BIT, calibconstants, 22, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
		{
			strcpy((char*) buf, "Error Tx AXIS_MAP_CONFIG\r\n");
			CDC_Transmit_FS(buf, strlen((char*)buf));
		}

	HAL_Delay(1000);

    buf[0] = 0x0C; //Test for OPR MODE

    ret = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
    if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
    		{
    			strcpy((char*) buf, "Error Tx OPR MODE\r\n");
    			CDC_Transmit_FS(buf, strlen((char*)buf));
    		}
    HAL_Delay(1000);
  //===========================================//
  //ALL CODE EXECUTED BASED ON TUTORIALS AND BNO055 DOCUMENTATION
  //Tutorial: https://www.youtube.com/watch?v=isOekyygpR8
  //BNO055 Documentation: https://cdn-shop.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf
  //Product Page: https://www.dfrobot.com/product-1793.html
  //===========================================//

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	//======INFININTELY SAMPLE REGISTER===============

	//buf[0] = EUL_ADDR;
//	buf[0] = CAL_STATUS;
//	buf[0] = EUL_ADDR;
//
//	ret = HAL_I2C_Master_Transmit(&hi2c1, BNO055_ADDR, buf, 1, HAL_MAX_DELAY); //Returns value
//
//	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
//	{
//		strcpy((char*) buf, "Error Tx 1\r\n");
//	}
//	else //Proceed with getting the angle information
//	{
//
//		ret = HAL_I2C_Master_Receive(&hi2c1, BNO055_ADDR, buf, 1, HAL_MAX_DELAY); //Think about changing size from 2 to 6 to get all Euler angles in one receive.
//		if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
//		{
//			strcpy((char*) buf, "Error Tx 2\r\n");
//		}
//		else //Translate values into angle, using Page 35
//		{
//
//		//------EULER ANGLE-------
//			eulval = ((int16_t)buf[0] << 8) | (buf[1] >> 8);
//
//			if ( eulval > 0x7FF ) {
//				eulval |= 0xF000;
//			}
//
//			eulpitch = eulval / 16;
//			sprintf((char*)buf,
//					"Pitch: %u.%02u deg\r\n",
//					((unsigned int) eulpitch / 100),
//					((unsigned int) eulpitch % 100));
//		}
//	}
//
//	//strcpy((char*)buf, "Hello!\r\n"); //For Alternate UART method
//
//	// Send out Buffer
//	CDC_Transmit_FS(buf, strlen((char*)buf));
//	HAL_Delay(1500);


  //=================Testing of MEM_READ===================

	  	//buf[0] = CHIP_ID;
//
//	  	ret = HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, EUL_ADDR, I2C_MEMADD_SIZE_8BIT, buf, 6, HAL_MAX_DELAY);
//		if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
//		{
//			strcpy((char*) buf, "Error Rx\r\n");
//		}
//		else
//		{
//
//		//Attempt to incorporate reading eul angle:
//		eulheading = (int16_t)buf[0]+(buf[1] << 8); //Bit-shift for MSB register
//		eulroll = (int16_t)buf[2]+(buf[3] << 8); //Bit-shift for MSB register
//		eulpitch = (int16_t)buf[4]+(buf[5] << 8); //Bit-shift for MSB register
//
//		eulheadingout = eulheading/16; //Convert to 16 LSB to 1 Degree
//		eulrollout = eulroll/16; //Convert to 16 LSB to 1 Degree
//		eulpitchout = eulpitch/16; //Convert to 16 LSB to 1 Degree
//
//		sprintf((char*)buf,
//				"X: %i, Y: %i, Z: %i\n",
//				(int) eulheadingout, (int) eulrollout, (int) eulpitchout);
//
////			//Normal code (works for reading registers):
////			eulval = (int16_t)buf[0];
////			sprintf((char*)buf,
////					"Chip ID: %u\r\n",
////					 eulval);
//		}

		//Full Angular Position/Velocity Reading

	  	ret = HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_ADDR, I2C_MEMADD_SIZE_8BIT, buf, 12, HAL_MAX_DELAY);
		if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
		{
			strcpy((char*) buf, "Error Rx\r\n");
		}
		else
		{

		//Attempt to incorporate reading eul angle:

		gyrx = (int16_t)buf[0]+(buf[1] << 8); //Bit-shift for MSB register
		gyry = (int16_t)buf[2]+(buf[3] << 8); //Bit-shift for MSB register
		gyrz = (int16_t)buf[4]+(buf[5] << 8); //Bit-shift for MSB register

		eulheading = (int16_t)buf[6]+(buf[7] << 8); //Bit-shift for MSB register
		eulroll = (int16_t)buf[8]+(buf[9] << 8); //Bit-shift for MSB register
		eulpitch = (int16_t)buf[10]+(buf[11] << 8); //Bit-shift for MSB register

		eulheadingout = (float)eulheading/(float)16; //Convert to 16 LSB to 1 Degree
		eulrollout = (float)eulroll/(float)16; //Convert to 16 LSB to 1 Degree
		eulpitchout = (float)eulpitch/(float)16; //Convert to 16 LSB to 1 Degree

		gyrxout = (float)gyrx/(float)16;
		gyryout = (float)gyry/(float)16;
		gyrzout = (float)gyrz/(float)16;

		sprintf((char*)buf,
				"X: %.2f, Y: %.2f, Z: %.2f\nXdot: %.5f, Ydot %.5f, Zdot %.5f\n",
				eulpitchout, eulrollout, eulheadingout,
				gyrxout, gyryout, gyrzout);

		}

		// Send out Buffer
		CDC_Transmit_FS(buf, strlen((char*)buf));
		HAL_Delay(500);

	/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
