/*
 * TestApp_Peripheral1.c
 *
 *  Created on: Jan 30, 2014
 *      Author: rv4560
 */

#include "xparameters.h"

#include "stdio.h"
#include "xgpio.h"

#define printf xil_printf
/* Xilinx version of printf - smaller footprint*/

int main1(void) {

	printf("-- Entering main () -- \r\n");

	XGpio dip;
	int i, dip_check;

	XGpio_Initialize(&dip, XPAR_DIP_SWITCHES_8BIT_DEVICE_ID);
	XGpio_SetDataDirection (&dip, 1, 0xffffffff);

	while(1){

		dip_check = XGpio_DiscreteRead (&dip, 1);
		printf("DIP switches status %x \r\n", dip_check);

		for (i=0; i<999999; i++);
	}

	printf("-- Exitiing main () -- \r\n");
	return 0;
}
