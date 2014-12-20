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
 * helloworld.c: simple test application
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "PLB46S_addrmap.h"

void print(char *str);

unsigned GoldenCipherText[4][4] = {  {0x39, 0x02, 0xdc, 0x19},
		{0x25, 0xdc, 0x11, 0x6a},
		{0x84, 0x09, 0x85, 0x0b},
		{0x1d, 0xfb, 0x97, 0x32}};

unsigned Key[4][4]        = {  {0x2b, 0x28, 0xab, 0x09},
		{0x7e, 0xae, 0xf7, 0xcf},
		{0x15, 0xd2, 0x15, 0x4f},
		{0x16, 0xa6, 0x88, 0x3c} };

//    W0    W1    W2    W3
unsigned PlainText[4][4]  = {  {0x32, 0x88, 0x31, 0xe0},
		{0x43, 0x5a, 0x31, 0x37},
		{0xf6, 0x30, 0x98, 0x07},
		{0xa8, 0x8d, 0xa2, 0x34} };

int main()
{
	init_platform();
/*
	printf("status => ");
	printf("done: %u  ",XEncrypt_IsDone());
	printf("idle: %u\n",XEncrypt_IsIdle());
*/
	int i,j;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			microblaze_bwrite_datafsl(PlainText[i][j], 0) ;
			microblaze_bwrite_datafsl(Key[i][j], 1) ;
		}
	}

//	printf("wrote data\n");

	unsigned CipherText[4][4];
	XEncrypt_Start();

	unsigned val;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			microblaze_bread_datafsl(val, 2) ;
			CipherText[i][j] = val;
		}
	}
/*
	printf("status => ");
	printf("done: %u  ",XEncrypt_IsDone());
	printf("idle: %u\n",XEncrypt_IsIdle());
*/
	//check
	int errors = 0;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			if(CipherText[i][j] != GoldenCipherText[i][j]) {
//				printf("Error! Calculated key does NOT match golden key at index: [%d][%d] !!!\n",i,j);
				errors++;
			}
		}
	}

//	printf("-- CipherText Check Completed - Found %d errors.\n",errors);

//	print("Hello World\n\r");

	cleanup_platform();

	return 0;
}
