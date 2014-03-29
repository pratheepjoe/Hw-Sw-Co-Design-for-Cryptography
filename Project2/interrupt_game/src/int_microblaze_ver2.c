/*
 * int_microblaze_ver2.c
 *
 *  Created on: Feb 13, 2014
 *      Author: rv4560
 */
#include "xtmrctr.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include "xparameters.h"
#include "mb_interface.h"
#include <stdio.h>

#define printf xil_printf

/* Xilinx version of printf - smaller foorprint. */

unsigned int timer_count0 = 2;
unsigned int timer_count1 = 8;

unsigned int count0 = 0;
unsigned int count1 = 0;

//Interrupt Service Routines for the timers.

void int_handler (void *baseaddr_p) {
	unsigned int csr;

	csr = XTmrCtr_GetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0);
	/*if the interrupt occur from the timer0 then increment count0 else count1*/
	if(csr & XTC_CSR_INT_OCCURED_MASK )
	{
		printf("\n\n\r Interrupt 0 - Count0 = %d", count0);
		count0++;
		/*clear the timer interrupt*/
		XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0, csr);
		/*INTC = acknowledge interrupt*/
		XIntc_AckIntr(XPAR_XPS_INTC_0_BASEADDR, XPAR_XPS_TIMER_0_INTERRUPT_MASK);  //0x02
	}

	csr = XTmrCtr_GetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0);
	if(csr & XTC_CSR_INT_OCCURED_MASK )
	{
			printf("\n\n\r Interrupt 1 - Count1 = %d", count1);
			count1++;
			/*clear the timer interrupt*/
			XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0, csr);
			/*INTC = acknowledge interrupt*/
			XIntc_AckIntr(XPAR_XPS_INTC_0_BASEADDR, XPAR_XPS_TIMER_1_INTERRUPT_MASK);  //0x02
	}

	printf("\n\rGoing back to main 0()");
}


int main(void){

	/*Start the interrupt Controller.*/
	XIntc_MasterEnable(XPAR_XPS_INTC_0_BASEADDR);
	XIntc_EnableIntr(XPAR_XPS_INTC_0_BASEADDR, XPAR_XPS_TIMER_0_INTERRUPT_MASK | XPAR_XPS_TIMER_1_INTERRUPT_MASK);

	/*Set the number of cycles the timer counts before interrupting.*/

	XTmrCtr_SetLoadReg(XPAR_XPS_TIMER_0_BASEADDR, 0, timer_count0 * 125000000);
	XTmrCtr_SetLoadReg(XPAR_XPS_TIMER_1_BASEADDR, 0, timer_count1 * 125000000);

	/*Reset the timer and clear interrupts.	 */

	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0, XTC_CSR_INT_OCCURED_MASK | XTC_CSR_LOAD_MASK);
	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0, XTC_CSR_INT_OCCURED_MASK | XTC_CSR_LOAD_MASK);

	/*Enable timer interrupt in the interrupt controller*/
	XIntc_EnableIntr(XPAR_XPS_TIMER_0_BASEADDR, XPAR_XPS_TIMER_0_INTERRUPT_MASK);
	XIntc_EnableIntr(XPAR_XPS_TIMER_1_BASEADDR, XPAR_XPS_TIMER_1_INTERRUPT_MASK);

	/*Star the timers */

	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0, XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK);
	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0, XTC_CSR_ENABLE_TMR_MASK | XTC_CSR_ENABLE_INT_MASK | XTC_CSR_AUTO_RELOAD_MASK | XTC_CSR_DOWN_COUNT_MASK);

	microblaze_register_handler((XInterruptHandler)int_handler, (void *)0);
	microblaze_enable_interrupts();

	/* Wait for interrupt to occur*/

	int i = 0;

	while(1){
		printf(".");
		for(i=0; i<99999; i++);
	}
}
