/*
 * TestApp_Peripheral3.c
 *
 *  Created on: Feb 11, 2014
 *      Author: rv4560
 */

#include "xparameters.h"

#include "stdio.h"
#include "xgpio.h"
#include "xtmrctr.h"

#define printf xil_printf
/* Xilinx version of printf - smaller foorprint. */


int main(void){

	printf ("-- Entering main () -- \r\n");

	int status;
	int statusAll = 1;

	XGpio dip, leds;
	int i, dip_check;

	int count=0;

	XTmrCtr XPS_Timer;
	unsigned int cycles, cycles1, cycles2, cycles3;

	status = XTmrCtr_Initialize (&XPS_Timer, XPAR_XPS_TIMER_0_DEVICE_ID);
	if (status != XST_SUCCESS){
		statusAll = 0;
		printf("Timer initialization failure! \r \n");
	}
	else {
		XTmrCtr_SetResetValue (&XPS_Timer, 0, 0x00000000);
		printf("Timer initialization success. \r \n");
	}
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

	int whole, fract;
	float xx;

	if(statusAll) {
	while(1){

		XTmrCtr_Reset (&XPS_Timer, 0);
		XTmrCtr_Start (&XPS_Timer, 0);

		printf("-------------------------------------------------\r\n");

		cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
		printf("Cycles loop 1 - %10d \r\n", cycles1);


		dip_check = XGpio_DiscreteRead(&dip,1);
		printf("\nDIP switches status %x \r\n", dip_check);

		XGpio_DiscreteWrite (&leds, 1, count);

		for(i=0; i<999999; i++);

		cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
		printf("Cycles loop 2 - %10d \r\n", cycles2);
		for(i=0; i<999999; i++);

		count++;

		cycles3 = XTmrCtr_GetValue(&XPS_Timer, 0);
		printf("Cycles loop 3 - %10d \r\n", cycles3);

		cycles = cycles1 + cycles2 + cycles3;
		printf("----------------------------------\r\n");

		printf("Profiling \r\n");

		xx = (float) cycles1/cycles; whole = xx; fract = (xx-whole)*1000;
		printf("Start   -Cycles1 - %d.%3d\r\n", whole, fract);

		xx = (float) cycles2/cycles; whole = xx; fract = (xx-whole)*1000;
		printf("Start   -Cycles2 - %d.%3d\r\n", whole, fract);

		xx = (float) cycles3/cycles; whole = xx; fract = (xx-whole)*1000;
		printf("Start   -Cycles3 - %d.%3d\r\n", whole, fract);

		printf("********************************************\r\n");

		for (i=0; i<999999; i++);
		}
	}
	printf("--Exiting main() -- \r\n");
	return 0;
}
