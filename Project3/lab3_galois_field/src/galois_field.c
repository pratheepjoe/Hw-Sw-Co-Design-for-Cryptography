/*
 * Copyright (c) 2009 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld without cache.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "xgpio.h"
#include "xtmrctr.h"
#include "xparameters.h"

unsigned int cycles2,cycles1,cycles3;
XTmrCtr XPS_Timer;

// routine to find the addition of two polynomials
unsigned char poly_addition(unsigned char inpB_1,unsigned char inpB_2)
{
	unsigned char outb;

	outb = inpB_1 ^ inpB_2;
	return(outb);
}

// routine to find the multiplication of two polynomials
unsigned char poly_multiplication(unsigned char inpB_1,unsigned char inpB_2){

	unsigned char irreducible_poly = 0x1b;
	unsigned char i;
    unsigned char outB = 0x00;
	for (i=0; i<9; i++)
	{
		unsigned char b;
		b = (inpB_2>>i)&1;
		if(i==0){
			outB = b*(inpB_1);
		}
		else
		{
			outB = outB ^((b*(inpB_1<<i))^ irreducible_poly);
		}
	}
		return(outB);
}

typedef struct div_result
{
    unsigned char a;
    unsigned char b;
} result;

// routine to find the division of two polynomials
result division(unsigned char inpB_1,unsigned char inpB_2){
	int i,diff,count1 = 0,count2 = 0;
	unsigned char a,b,temp_inpB_2,qot=1,qot1=0;
	    result div;
	while(inpB_1 >= inpB_2){

		for(i=0;i<8;i++){
			a = (inpB_1>>i)&1;
			b = (inpB_2>>i)&1;
			if(b)
				count2 =i;
			if(a)
				count1 =i;
		}
		diff = count1-count2;
		temp_inpB_2 = inpB_2<<diff;
		qot1 ^= qot<<diff;
		inpB_1 = inpB_1 ^ temp_inpB_2;
	}
	div.a = qot1;
	div.b = inpB_1;
    return div;
}


// routine for extended euclids algorithm to find the multiplicative inverse
unsigned char extended_euclid(unsigned char inpB_1, unsigned char inpB_2){

	unsigned char a, b;
	if(inpB_1 >= inpB_2)
	{
		b = inpB_2;
		a = inpB_1;
	}
	else
	{
		b = inpB_1;
		a = inpB_2;
	}
	unsigned char aux = 0x00;
	unsigned char rem = 0x00;
	unsigned char qot = 0x00;

	unsigned char aux_previous = 0x01;
	unsigned char aux_prev_to_prev = 0x00;

	while(rem!=1){
		result div = division(a,b);
		if(div.b == 0)
		{
			//printf("\nSorry! The multiplicative inverse is not possible.");
			aux =0;
			break;
		}
		else{
			qot = div.a;
			rem = div.b;
			aux= poly_multiplication(qot,aux_previous)^ aux_prev_to_prev;
			a=b;
			b=rem;
			aux_prev_to_prev = aux_previous;
			aux_previous = aux;
		}
	}
	return(aux);
}

int main()
{
	int status;
	int statusAll = 1;
	status = XTmrCtr_Initialize (&XPS_Timer, XPAR_XPS_TIMER_0_DEVICE_ID);
	if (status != XST_SUCCESS){
		statusAll = 0;
		printf("Timer initialization failure! \r \n");
	}
	else {
		XTmrCtr_SetResetValue (&XPS_Timer, 0, 0x00000000);
		printf("Timer initialization success. \r \n");
	}

	if(statusAll) {

		XTmrCtr_Reset (&XPS_Timer, 0);
		XTmrCtr_Start (&XPS_Timer, 0);
		unsigned char mult,inv,add;
		int i;


		init_platform();
				print("\nHello World without cache.\n\r\n\n");
				unsigned short inpB_1 = 0x1A;
				unsigned short inpB_2 = 0x05;

	// Addition of 2 poly
				// reset and start timer
				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);

				// capture initial timer value
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);

					add = poly_addition(inpB_1, inpB_2);

				// capture final timer value
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				printf("Polynomial addition of  0x%x and 0x%x is\n", inpB_2, inpB_1);
				printf("Addition is = 0x%x\n", add);
				printf("Total Cycles for 1 time addition- %10d \r\n", (cycles2-cycles1));

				// reset and start timer
				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);

				// capture initial timer value
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
				for(i=0;i<100;i++)
					add = poly_addition(inpB_1, inpB_2);
				// capture final timer value
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				cycles3 = cycles2 - cycles1;
				printf("Total Cycles for 100-times Addition- %10d \r\n", cycles3);
				printf("Actual Cycles for one time Addition- %10d \r\n\n\n", cycles3/100);


	//Extended Euclid algo for finding inverse
				// reset and start timer
				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);

				// capture initial timer value
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);

				inv = extended_euclid(inpB_1, inpB_2);

				// capture final timer value
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);

				printf("Polynomials is = 0x%x and irreducible plynomial = 0x%x\n", inpB_2, inpB_1);
				printf("Multiplicative inverse is = 0x%x\n", inv);
				printf("Total Cycles for 1 time extended Euclid Algo- %10d \r\n", (cycles2-cycles1));

				// reset and start timer
				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);

				// capture initial timer value
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
				for(i=0;i<100;i++)
					inv = extended_euclid(inpB_1, inpB_2);
				// capture final timer value
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				cycles3 = cycles2 - cycles1;
				printf("Total Cycles for 100-times extended Euclid Algo- %10d \r\n", cycles3);
				printf("Actual Cycles for one time extended Euclid Algo- %10d \r\n", cycles3/100);

	//Multiplication of two poly
				inpB_1 = 0x5F;
				inpB_2 = 0x05;

				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
				mult = poly_multiplication(inpB_1, inpB_2);
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				printf("\n\nInput polynomials are : 0x%x and 0x%x\n", inpB_1, inpB_2);
				printf("Multiplication result is = 0x%x\n", mult);
				printf("Total Cycles for one time multiplication- %10d \r\n", (cycles2-cycles1));

				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
				for(i=0;i<100;i++)
					mult = poly_multiplication(inpB_1, inpB_2);
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				cycles3 = cycles2 - cycles1;
				printf("Total Cycles for 100 times multiplication- %10d \r\n", cycles3);
				printf("Actual Cycles for one time multiplication- %10d \r\n", cycles3/100);


	//Division of two poly
				inpB_1 = 0x5F;
				inpB_2 = 0x05;

				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);

				result div = division(inpB_1, inpB_2);

				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				printf("\n\nInput polynomials are : 0x%x and 0x%x\n", inpB_1, inpB_2);
				printf("quotient is = 0x%x\n", div.a);
				printf("Remainder is = 0x%x\n", div.b);
				printf("Total Cycles for one time Division- %10d \r\n", (cycles2-cycles1));

				XTmrCtr_Reset (&XPS_Timer, 0);
				XTmrCtr_Start (&XPS_Timer, 0);
				cycles1 = XTmrCtr_GetValue(&XPS_Timer, 0);
				for(i=0;i<100;i++)
					div = division(inpB_1, inpB_2);
				cycles2 = XTmrCtr_GetValue(&XPS_Timer, 0);
				cycles3 = cycles2 - cycles1;
				printf("Total Cycles for 100 times Division- %10d \r\n", cycles3);
				printf("Actual Cycles for one time Division- %10d \r\n", cycles3/100);



	}
    return 0;
}
