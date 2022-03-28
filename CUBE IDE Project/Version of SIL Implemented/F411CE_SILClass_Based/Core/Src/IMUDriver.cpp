/*
 * IMUDriver.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: sjman
 */

#include "IMUDriver.hpp"
#include "stm32f4xx_hal.h" //Important!
#include "usbd_cdc_if.h"

IMUDriver::IMUDriver(I2C_HandleTypeDef* hi2cinput, TIM_HandleTypeDef* htiminput) {

	//Capture I2C channel used for IMU
	hi2c = hi2cinput;
	htim = htiminput;

}

void IMUDriver::Initialization(void)
{
	//Rest of initialization
	//Note: Since during system start-up (no multitasking requirement), HAL_Delays are used.

	buf[0] = 0x00; //Put IMU Into Config Mode

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 1;
	}

	HAL_Delay(100);

	buf[0] = 0x00; //Put into normal power mode

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, PWR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 2;
	}

	HAL_Delay(100);

	buf[0] = 0x00; //Set UNIT_SEL for degrees in model

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, UNIT_SEL, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 3;
	}

	HAL_Delay(100);

	buf[0] = 0x01; //Configure Axis to have negative Z axes due to how BNO055 is attached to platform.

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, AXIS_MAP_SIGN, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 4;
	}

	HAL_Delay(100);

	buf[0] = 0x24; //Configure Axis to orientation that works

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, AXIS_MAP_CONFIG, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 5;
	}

	HAL_Delay(100);

	//*====================================*
	// WRITE CALIBRATION CONSTANTS TO IMU
	//*====================================*
    ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, CAL_CONSTANTS, I2C_MEMADD_SIZE_8BIT, calibconstants, 22, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
		{
			strcpy((char*) buf, "Error Tx AXIS_MAP_CONFIG\r\n");
			CDC_Transmit_FS(buf, strlen((char*)buf));
		}

	HAL_Delay(100);

	buf[0] = 0x0C; //Put IMU into NDOF fusion mode, starts IMU. (Note: IMU mode is 0x08, NDOF mode is 0x0C)

	ret = HAL_I2C_Mem_Write(hi2c, BNO055_ADDR, OPR_MODE, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY);
	if ( ret != HAL_OK ) //If BNO055 Device is not found, throw error. Will be important for debugging
	{
		ErrorFlg = 6;
	}

	HAL_TIM_Base_Start_IT(htim); //IMU timing based on timer channel (10 ms)
}

//Gets Orientation from IMU, stores raw binary into buf.
void IMUDriver::PollOrientation()
{

	HAL_I2C_Mem_Read_DMA(hi2c, BNO055_ADDR, GYR_ADDR, I2C_MEMADD_SIZE_8BIT, buf, 12); //Runs DMA-based mem read of IMU buffer, non-blocking

}

//Converts buf data into floats to be read by host PC or on-board controller.
void IMUDriver::ConvertOrientation(void)
{

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

}

//Since it is during UI phase (no multitasking), code can be blocking
void IMUDriver::Calibration()
{

	HAL_I2C_Mem_Read(hi2c, BNO055_ADDR, CAL_STATUS, I2C_MEMADD_SIZE_8BIT, buf, 1, HAL_MAX_DELAY); //Runs IT-based mem read of IMU buffer, non-blocking

}
