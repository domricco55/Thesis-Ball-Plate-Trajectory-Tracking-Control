/*
 * TouchscreenDriver.cpp
 *
 *  Created on: Feb 13, 2022
 *      Author: sjman
 */

#include "TouchscreenDriver.hpp"
#include "stm32f4xx_hal.h" //Important!
#include "usbd_cdc_if.h"
#include <math.h>
#include <stdlib.h>
#include<algorithm>
using namespace std;

#define ADC_BUF_LEN 100

//DOXYGEN COMMENTING
TouchscreenDriver::TouchscreenDriver(ADC_HandleTypeDef* hadcinput, TIM_HandleTypeDef* htimdelay, TIM_HandleTypeDef* htimvelocity, uint32_t pinarr[],
        							 GPIO_TypeDef* portarr[])
{
	//Attach inputted hadc to object
	hadc = hadcinput;
	htimvel = htimvelocity; //Ensure timer channel is set for required delay (100-150 us)
	htimdel = htimdelay; //Ensure timer channel is set for required delay (100-150 us)

	//Attach all pin definitions to private arrays
	for (i = 0; i<5; i++)
	{
		PinArray[i] = pinarr[i];
		PinPort[i] = portarr[i];
	}

}

void TouchscreenDriver::Initialization(void)
{


	//To switch configuration for which corner is the 0,0 corner of the touch panel, just flip these values.

	//Touchscreen Initialization: Start with right side energized.
	HAL_GPIO_WritePin(PinPort[0], PinArray[0], GPIO_PIN_SET); //Pin B0 corresponds to LL
	HAL_GPIO_WritePin(PinPort[1], PinArray[1], GPIO_PIN_SET); // Pin B1 corresponds to UL
	HAL_GPIO_WritePin(PinPort[2], PinArray[2], GPIO_PIN_RESET); // Pin B2 corresponds to LR
	HAL_GPIO_WritePin(PinPort[3], PinArray[3], GPIO_PIN_RESET); //Pin B10 corresponds to UR

	HAL_Delay(5);

/*
	//Just as a check (remove later)
	HAL_GPIO_WritePin(PinPort[4], PinArray[4], GPIO_PIN_RESET); //Set as a verification light for assigned correctly...
															  //Works! Woot!
*/
	HAL_TIM_Base_Start(htimvel); //Start velocity timer for time delta
	prevtime = __HAL_TIM_GET_COUNTER(htimvel); //save initial time as starting time
	HAL_ADC_Start_DMA(hadc, (uint32_t*)xposADC, ADC_BUF_LEN); //Starts assigned hadc channel to start taking ADC readings.
}

// DOXYGEN COMMENTING
void TouchscreenDriver::ADC_Callback(void)
{
	//Toggle the touchscreen to read the opposite direction (x->y or y->x)
	HAL_GPIO_TogglePin(PinPort[1], PinArray[1]); // Pin B1 corresponds to UL
	HAL_GPIO_TogglePin(PinPort[2], PinArray[2]); // Pin B2 corresponds to LR

	HAL_TIM_Base_Start_IT(htimdel); //Allow touchscreen settling time to transition before starting DMA again

}

void TouchscreenDriver::TIM_Callback(void)
{
	//Logic handler for touchscreen after settling time reached to get both sides of buffer filled
	switch(tsstate)
	{
		case 0: //X-position 1st half of buff filled, switch to 1st half of y buff
			tsstate = 1;
			HAL_TIM_Base_Stop_IT(htimdel);
			HAL_ADC_Start_DMA(hadc, (uint32_t*)yposADC, ADC_BUF_LEN);
			break;
		case 1: //Y-position 1st half of x buff filled, set flag for 1st half update, switch to handling when X is re-found, trigger conversions
			tsstate = 0;
			tsflg = 1;
			HAL_TIM_Base_Stop_IT(htimdel);
			break;
	}
}

void TouchscreenDriver::Calibration(void)
{
	//Placeholder
}

void TouchscreenDriver::ProcessPositionData(void)
{
	//Initialization of necessary functions/structs
	void mergeSort(uint16_t arr[], uint16_t l, uint16_t r);
	uint16_t xposADCcontact[ADC_BUF_LEN] = {0};
	uint16_t yposADCcontact[ADC_BUF_LEN] = {0};
	uint16_t sizecontact = 0;
	uint16_t sizemidpt = 0;
	float absxvel = 0;
	float absyvel = 0;
	float diffx = 0;
	float diffy = 0;
	float xposcurrent = 0;
	float yposcurrent = 0;
	float tempaccelx = 0;
	float tempaccely = 0;

	//Filter incoming ADC signal for points of no-contact
	for(i = 0; i<ADC_BUF_LEN; i++)
	{
		if(xposADC[i] < 750 || yposADC[i] < 750)
		{
			//Do nothing
		}
		else
		{
			xposADCcontact[sizecontact] = xposADC[sizecontact];
			yposADCcontact[sizecontact] = yposADC[sizecontact];
			sizecontact++;
		}
	}

	if(sizecontact >= round(ADC_BUF_LEN*.75)) //Check for a minimum amount of contact points (75%)
	{
		sizemidpt = round(sizecontact*(.5)); //Find midpoint of array size

		//Sort the filtered list using merge sort
		mergeSort(xposADCcontact, 0, sizecontact);
		mergeSort(yposADCcontact, 0, sizecontact);

		//Average inner values (can change to increase/decrease
		xposADCReading = (xposADCcontact[sizemidpt-1]+xposADCcontact[sizemidpt]+xposADCcontact[sizemidpt-2])/((uint16_t)3);
		yposADCReading = (yposADCcontact[sizemidpt-1]+yposADCcontact[sizemidpt]+yposADCcontact[sizemidpt-2])/((uint16_t)3);

		//Convert ADC values to position values
		xposcurrent = xposADCReading*xslope+(xbias);
		yposcurrent = yposADCReading*yslope+(ybias);

		//Check for difference between current and previous position
		currtime = __HAL_TIM_GET_COUNTER(htimvel);

		delT = ((float)currtime-(float)prevtime); //Delta time between previous points

		//If Delta T overflows, increase current time by register amount
		if (delT<0)
		{
			currtime = currtime+65535; //account for timer overflow/reset
		}

		delT = (currtime-prevtime)/(float)1000000; //Timer counter ticks are relative to microseconds, so need to convert to seconds.

		//add previous velocity for use as comparison/saving?
		tempxvel = (xposcurrent-xpos)/(delT); //in mm/s
		tempyvel = (yposcurrent-ypos)/(delT); //units of mm/s

		//Look at the acceleration between points
//		tempaccelx = abs(tempxvel/(delT));
//		tempaccely = abs(tempyvel/(delT));


		absxvel = abs(tempxvel);
		absyvel = abs(tempyvel);

		//Check if velocity is within reasonable magnitude:
		if(absxvel <= 800 && absyvel <= 800) //If velocity is below 800 mm/s (found through energy conservation)
		{
			n = 0; //Reset data points
			xpos = xposcurrent;
			ypos = yposcurrent;
//
//			//Try looking at acceleration to smooth velocity
//			if(tempaccelx < 20000 && tempaccely < 20000)
//			{
			xvel = tempxvel; //Set velocity in the x and y directions to the temp velocity
			yvel = tempyvel;
//			}

			prevtime = currtime; //set previous time as the new time
		}
		else //Check for rapid changes in position
		{
			if (n == 0) //if at reset, place the original xpos and ypos in the zero position of the prevpos array
			{
				prevxpos[0] = xpos;
				prevypos[0] = ypos;
				n++;
			}

			//save current x and y pos
			prevxpos[n] = xposcurrent;
			prevypos[n] = yposcurrent;
			n++;

			if (n >= 3) //if 2 samples are saved in a row:
			{
				//Get difference in xposition and y position between points
				diffx = abs(abs(prevxpos[1]) - abs(prevxpos[2]));
				diffy = abs(abs(prevypos[1]) - abs(prevypos[2]));

				if (diffx <= 5 && diffy <= 5) //If points are within 5 mm apart, save over xpos and ypos
				{
					//Rewrite new xpos and ypos values
					xpos = (prevxpos[0]+prevxpos[1])/(float)2;
					ypos = (prevypos[0]+prevypos[1])/(float)2;

					tempxvel = (xpos-prevxpos[0])/(delT); //in mm/s
					tempyvel = (ypos-prevypos[0])/(delT); //units of mm/s

//					tempaccelx = abs(tempxvel/(delT));
//					tempaccely = abs(tempyvel/(delT));
//
//					//Set previous time to this time stamp
//					if(tempaccelx < 20000 && tempaccely < 20000)
//					{
					xvel = tempxvel;
					yvel = tempyvel;
//					}

					prevtime = currtime;
				}

				n = 0;

			}
		}
	}
	else
	{
		//Nothing?
//		xpos = prevxpos[0];
//		ypos = prevypos[0];
	}

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_SET);

	//End with starting DMA for now:
	HAL_ADC_Start_DMA(hadc, (uint32_t*)xposADC, ADC_BUF_LEN);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,GPIO_PIN_RESET);
}

//==============Accessory Functions:==================

// From: https://www.geeksforgeeks.org/merge-sort/
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(uint16_t arr[], uint16_t l, uint16_t m, uint16_t r)
{
	uint16_t i, j, k;
	uint16_t n1 = m - l + 1;
	uint16_t n2 = r - m;

    /* create temp arrays */
	uint16_t L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(uint16_t arr[], uint16_t l, uint16_t r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        uint16_t m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

