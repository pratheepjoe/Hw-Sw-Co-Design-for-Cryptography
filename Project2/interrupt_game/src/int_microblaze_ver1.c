/*
 * int_microblaze_ver1.c
 *
 *  Created on: Feb 13, 2014
 *      Author: rv4560
 */
#include "xtmrctr.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include "xparameters.h"
#if 0
#define printf xil_printf

/* Xilinx version of printf - smaller foorprint. */

unsigned int timer_count0 = 1;
unsigned int timer_count1 = 4;

unsigned int count0 = 0;
unsigned int count1 = 0;

//Interrupt Service Routines for the timers.

void timer0_int_handler (void *baseaddr_p) {
	unsigned int csr;

	printf("\n\n\r Interrupt 0 - Count0 = %d", count0);
	count0++;
	printf("\n\rGoing back to main 0()");
	/*Clear the timer interrupt - read timer 0 CSR and assign it back*/

	csr = XTmrCtr_GetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0);
	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_0_BASEADDR, 0, csr);
}


void timer1_int_handler (void *baseaddr_p) {
	unsigned int csr;

	printf("\n\n\r Interrupt 1 - Count1 = %d", count1);
	count1++;
	printf("\n\rGoing back to main 1()");
	/*Clear the timer interrupt - read timer 1 CSR and assign it back*/

	csr = XTmrCtr_GetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0);
	XTmrCtr_SetControlStatusReg(XPAR_XPS_TIMER_1_BASEADDR, 0, csr);
}

int main0(void){

	/*Register the Timer interrupt handler in the vector table*/
	XIntc_RegisterHandler(XPAR_XPS_INTC_0_BASEADDR, XPAR_XPS_INTC_0_XPS_TIMER_0_INTERRUPT_INTR, (XInterruptHandler) timer0_int_handler, (void *) XPAR_XPS_TIMER_0_BASEADDR);
	XIntc_RegisterHandler(XPAR_XPS_INTC_0_BASEADDR, XPAR_XPS_INTC_0_XPS_TIMER_1_INTERRUPT_INTR, (XInterruptHandler) timer1_int_handler, (void *) XPAR_XPS_TIMER_1_BASEADDR);

	/*Start the interrupt Controller.*/
	XIntc_MasterEnable(XPAR_XPS_INTC_0_BASEADDR);
	XIntc_EnableIntr(XPAR_XPS_INTC_0_BASEADDR, 0x3);   //03 = 0011 to enable both interrupt.

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

	microblaze_enable_interrupts();

	/* Wait for interrupt to occur*/

	int i = 0;

	while(1){
		printf(".");
		for(i=0; i<999999; i++);
	}
}
#endif
