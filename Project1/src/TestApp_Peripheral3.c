/*
 * TestApp_Peripheral3.c
 *
 *  Created on: Feb 4, 2014
 *      Author: rv4560
 */


#include "xparameters.h"

#include "stdio.h"
#include "xgpio.h"

#define printf xil_printf
/* Xilinx version of printf - smaller foorprint. */


int main(void){

	printf ("-- Entering main () -- \r\n");

	int status;
	int statusAll = 1;
	XGpio dip, leds;
	int i, dip_check;

	int count=0;

	status = XGpio_Initialize (&dip, XPAR_DIP_SWITCHES_8BIT_DEVICE_ID);
	if (status != XST_SUCCESS){
		statusAll = 0;
		printf("DIP switch initialization failure! \r \n");
	}
	else {
		XGpio_SetDataDirection (&dip, 1, 0xffffffff);\
		printf("DIP switch initialization success. \r \n");
	}
	status = XGpio_Initialize(&leds, XPAR_LEDS_8BIT_DEVICE_ID);
	if (status != XST_SUCCESS){
			statusAll = 0;
			printf("LEDs initialization failure! \r \n");
		}
	else {
		XGpio_SetDataDirection (&leds, 1, 0x00000000);
		printf("LEDs initialization Success! \r \n");
	}
	while(1){

		dip_check = XGpio_DiscreteRead(&dip,1);
		printf("Prog2: DIP switches status %x \r\n", dip_check);

		XGpio_DiscreteWrite (&leds, 1, count);

		for(i=0; i<999999; i++);

		count++;
	}

	printf("--Exiting main() -- \r\n");
	return 0;
}

