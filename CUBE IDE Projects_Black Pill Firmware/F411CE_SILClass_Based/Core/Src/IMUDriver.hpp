/*
 * IMUDriver.h
 *
 *  Created on: Feb 17, 2022
 *      Author: sjman
 */

#ifndef SRC_IMUDRIVER_HPP_
#define SRC_IMUDRIVER_HPP_

#include "stm32f4xx_hal.h" //Important!
#include "usbd_cdc_if.h"

class IMUDriver {

	private:

		//Initialization of IMU Address Variables - defined addresses in the BNO055 Documentation
		static const uint8_t BNO055_ADDR = 0x28 << 1; //Left shift needed due to 8-bit communication
		static const uint8_t EUL_ADDR = 0x1A; //Found in BNO055 Documentation
		static const uint8_t PWR_MODE = 0x3E; //BNO055 Doc
		static const uint8_t OPR_MODE = 0x3D; //BNO055 Doc
		static const uint8_t UNIT_SEL = 0x3B; //BNO055 Doc
		static const uint8_t AXIS_MAP_SIGN = 0x42; //BNO055 Doc
		static const uint8_t AXIS_MAP_CONFIG = 0x41; //BNO055 Doc
		static const uint8_t GYR_ADDR = 0x14; //Address starting with angular velocity + angular position after 12 bytes
		static const uint8_t CAL_STATUS = 0x35; //BNO055 Doc
		static const uint8_t CAL_CONSTANTS = 0x55; //Constants to write over for calibration
		static const uint8_t CHIP_ID = 0x00; //BNO055 Doc

		//Used as an inbetween for converting the buf values into the float
		int16_t eulheading = 0; //Z rotation of IMU
		int16_t eulroll = 0; //Y rotation of IMU
		int16_t eulpitch = 0; //X rotation of IMU

		int16_t gyrx = 0; //Gyroscope readout for x direction
		int16_t gyry = 0; //Gyroscope readout for y direction
		int16_t gyrz = 0; //Gyroscope readout for z direction

		HAL_StatusTypeDef ret; //StatusDef to return any errors with IMU communication
		I2C_HandleTypeDef* hi2c; //Inputted I2C channel to use to communicate with IMU
		TIM_HandleTypeDef* htim; //Inputted Timer channel to handle communication timing with IMU
		uint8_t buf[20] = {0}; //DMA for the IMU writes directly to this memory buffer
		uint8_t calibconstants[24] = {0, 0, 124, 255, 1, 0, 198, 0, 161, 0, 14, 0, 255, 255, 253, 255, 255, 255, 232, 3, 98, 1};

	public:

		//IMU Parameters:
		float EulerX = 0; //Estimated angular displacement of X axis rotation (gamma)
		float EulerY = 0; //Estimated angular displacement of Y axis rotation (beta)
		float EulerZ = 0; //Estimated angular displacement of Z axis rotation

		float AngularVelX = 0; //Estimated angular velocity of X axis rotation (gamma_dot)
		float AngularVelY = 0; //Estimated angular velocity of Y axis rotation (beta_dot)
		float AngularVelZ = 0; //Estimated angular velocity of Z axis rotation

		uint8_t ErrorFlg = 0; //Flag to designate the error states of the IMU for main/UI.

		IMUDriver(I2C_HandleTypeDef* hi2cinput, TIM_HandleTypeDef* htiminput);
		void Initialization(void);
		void PollOrientation(void);
		void ConvertOrientation(void);
		void Calibration(void);

};

#endif /* SRC_IMUDRIVER_HPP_ */
