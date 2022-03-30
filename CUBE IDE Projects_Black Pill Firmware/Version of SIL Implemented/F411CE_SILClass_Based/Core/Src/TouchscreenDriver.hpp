/*
 * TouchscreenDriver.h
 *
 *  Created on: Feb 13, 2022
 *      Author: sjman
 */

#ifndef SRC_TOUCHSCREENDRIVER_HPP_
#define SRC_TOUCHSCREENDRIVER_HPP_

#include <stdint.h>
#include "stm32f4xx_hal.h" //Important!
#include "usbd_cdc_if.h"

class TouchscreenDriver {

private:
		//5-pin Touchscreen Internal Position Parameters:
		uint16_t xposADC[100] = {0}; //Array of ADC values when reading the touchscreen x position.
		uint16_t xposADCReading = 0; //Oversampled average reading for xpos
		float prevxpos[3] = {0}; //Previous registered touchscreen position to register for ball x velocity.
		float xslope = 0.154755; //Based on previous calibration (did not include zero)
		float xbias = -304.374202; //Based on previous calibration (did not include zero)

		uint16_t yposADC[100] = {0}; //Array of ADC values when reading the touchscreen y position.
		uint16_t yposADCReading = 0; //Oversampled average reading for ypos
		float prevypos[3] = {0}; //Previous registered touchscreen position to register for ball y velocity.
		float yslope = 0.117449; //Based on previous calibration (did not include zero)
		float ybias = -231.425424; //Based on previous calibration (did not include zero)

		uint32_t currtime = 0; //Current time to be utilized by the delT calculations
		uint32_t prevtime = 0; //Previous time for delT calculations
		float delT = 0; //Time delta between last oversampled position versus current oversampled position

		float tempxvel = 0;
		float tempyvel = 0;

		float prevxvel[3] = {0}; //Could be Used for filtering velocity noise?
		float prevyvel[3] = {0}; //Could be Used for filtering velocity noise?

		//State Variable:
		unsigned int i = 0; //Counter for for loops
		uint8_t n = 0; //Counter for number of
		uint8_t tsstate = 0; //Necessary because touchscreen requires alternating between reading x and y.

		//Necessary STM Parameters:
		ADC_HandleTypeDef* hadc; //Passthrough of hadc address pointer used for touchscreen reading/activation
		TIM_HandleTypeDef* htimdel; //Passthrough of htim address pointer used for settling time of touchscreen (timer channel set to 100-150 ticks at 1 us)
		TIM_HandleTypeDef* htimvel; //Passthrough of htim address pointer used for ball velocity (timer channel set to 12-bit max 65535 at 1 us)

		uint32_t PinArray[5] = {0}; //Array of touchscreen pins fed into initialization, formatted as: [LL, UL, LR, UR].
		GPIO_TypeDef* PinPort[5] = {0}; //Array of touchscreen ports fed into initialization, formatted as: [LL, UL, LR, UR].

public:

	float xpos = 0; //Current listed xpos reported to Host PC or used for on-board controller
	float xvel = 0; //Current listed xvel reported to Host PC or used for on-board controller

	float ypos = 0; //Current listed ypos reported to Host PC or used for on-board controller
	float yvel = 0; //Current listed yvel reported to Host PC or used for on-board controller

	uint8_t tsflg = 0; //Used for logic of calculations

	TouchscreenDriver(ADC_HandleTypeDef* hadcinput, TIM_HandleTypeDef* htimdelay, TIM_HandleTypeDef* htimvelocity, uint32_t pinarr[],
			          GPIO_TypeDef* portarr[]);
	void Initialization(void);
	void ADC_Callback(void);
	void TIM_Callback(void);
	void ProcessPositionData(void);
	void Calibration(void);



};

#endif /* SRC_TOUCHSCREENDRIVER_HPP_ */
