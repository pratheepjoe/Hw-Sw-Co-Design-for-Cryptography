/*
 * AES_128_main.c
 *
 *  Created on: Mar 11, 2014
 *      Author: rv4560
 */
#include "xparameters.h"
#include "string.h"
#include "stdio.h"
#include "platform.h"
#include "xtmrctr.h"

#include "AES_128.h"

//====================================================
unsigned int encryption_start_time, encryption_end_time,
			ExpandKey_start_time, ExpandKey_end_time, 
			AddRoundKey_start_time, AddRoundKey_end_time, 
			SubBytes_start_time, SubBytes_end_time,
			ShiftRows_start_time, ShiftRows_end_time,
			MixColumns_start_time, MixColumns_end_time,
			Initialization_start_time, Initialization_end_time,
			avgRound_start_time, avgRound_end_time;
			
XTmrCtr XPS_Timer;
unsigned char StateArray [4][4];
unsigned char ExpandedKey [11][4][4];

// W0  W1   W2   W3

unsigned char Key[4][4]  = {{0x2b, 0x28, 0xab, 0x09},
							{0x7e, 0xae, 0xf7, 0xcf},
							{0x15, 0xd2, 0x15, 0x4f},
							{0x16, 0xa6, 0x88, 0x3c} };

// W0   W1   W2   W3

unsigned char PlainText[4][4] = { {0x32, 0x88, 0x31, 0xe0},
								  {0x43, 0x5a, 0x31, 0x37},
								  {0xf6, 0x30, 0x98, 0x07},
								  {0xa8, 0x8d, 0xa2, 0x34}};

// To set all the bytes in a block of memory to a perticular value, use memset().
// The function prototype is void * memset(void *dest, int c, size_t count);

void encrypt(void);
void decrypt(void);

int main(void){

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
		Initialization_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
		init_platform();
		Initialization_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);

		xil_printf("\n\n\n");
		xil_printf("-- Starting AES software test based on FIPS-197 (Appendix B) \r\n\n");
		XTmrCtr_Reset (&XPS_Timer, 0);
		XTmrCtr_Start (&XPS_Timer, 0);
	//----------------------------------------------
	//-------Encrypt Function-----------------------
	//----------------------------------------------

		encryption_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
		encrypt();
		encryption_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	
	//----------------------------------------------
	//-------Decrypt Function-----------------------
	//----------------------------------------------
		/*XTmrCtr_Reset (&XPS_Timer, 0);
		XTmrCtr_Start (&XPS_Timer, 0);
		cycles3 = XTmrCtr_GetValue(&XPS_Timer, 0);
		decrypt();
		cycles4 = XTmrCtr_GetValue(&XPS_Timer, 0);
		*/
	//----------------------------------------------
	//-------Display Results------------------------
	//----------------------------------------------

		xil_printf("Initialization time - %10d \r\n", (Initialization_end_time-Initialization_start_time));
		xil_printf("ExpandKey Execution time - %10d \r\n", (ExpandKey_end_time-ExpandKey_start_time));
		xil_printf("AddRoundKey Execution time - %10d \r\n", (AddRoundKey_end_time-AddRoundKey_start_time));
		xil_printf("SubBytes Execution time - %10d \r\n", (SubBytes_end_time-SubBytes_start_time));
		xil_printf("ShiftRows Execution time - %10d \r\n", (ShiftRows_end_time-ShiftRows_start_time));
		xil_printf("MixColumns time - %10d \r\n", (MixColumns_end_time-MixColumns_start_time));
		xil_printf("Avg Round time - %10d \r\n", (avgRound_end_time-avgRound_start_time)/10);

		xil_printf("Total Execution time - %10d \r\n", (encryption_end_time-encryption_start_time));
	xil_printf("*************************************\r\n");

	xil_printf("-- Exiting main() --\r\n");
	cleanup_platform();
	return 0;
	}
	return -1;
}

void encrypt(){
	bzero(StateArray, 4*4*sizeof(unsigned char));
	bzero(ExpandedKey, 11*4*sizeof(unsigned char));

#if (AES_PRINT & AES_PRINT_MAIN)
	xil_printf("-- Test Encyption Key \r\n\n");
	AES_printf(Key);
	xil_printf("-------------------------\r\n\n");

	xil_printf("-- Test Plaintext \r\n\n");
	AES_printf(PlainText);
	xil_printf("-------------------------\r\n\n");
#endif

#if (AES_PRINT & AES_PRINT_MAIN)
	xil_printf("-- Starting Key Expension   \r\n\n");
#endif
	
	ExpandKey_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	ExpandKey(Key, ExpandedKey);  //
	ExpandKey_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	
#if (AES_PRINT & AES_PRINT_MAIN)
	xil_printf("-- Starting Encryption  \r\n\n");
#endif

	long int x;
	for(x=0; x<1; x++){
		memcpy(StateArray, PlainText, 4*4*sizeof(unsigned char));

#if (AES_PRINT & AES_PRINT_DETAILS)
	xil_printf("-- Test State - Start of Round 0 \r\n\n");
	AES_printf(StateArray);
	xil_printf("-------------------------\r\n\n");
#endif
	AddRoundKey_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	AddRoundKey(ExpandedKey[0], StateArray);  //
	AddRoundKey_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	
#if (AES_PRINT & AES_PRINT_DETAILS)
	xil_printf("-- Test State - Start of Round 0 \r\n\n");
	AES_printf(StateArray);
	xil_printf("-------------------------\r\n\n");
#endif

	int i;
	avgRound_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	//Rounds
	for(i=1; i<=10; i++){
		if(i == 1)
		{
			SubBytes_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
			SubBytes(StateArray);
			SubBytes_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
		}
		else
			SubBytes(StateArray);
	#if (AES_PRINT & AES_PRINT_DETAILS)
		xil_printf("-- Test State - Round %d after SubBytes \r\n\n", i);
		AES_printf(StateArray);
		xil_printf("-------------------\r\n\n");
	#endif

		if(i == 1)
		{
			ShiftRows_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
			ShiftRows(StateArray);
			ShiftRows_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
		}
		else
			ShiftRows(StateArray);
			#if (AES_PRINT & AES_PRINT_DETAILS)
				xil_printf("-- Test State - Round %d after shiftRows \r\n\n", i);
				AES_printf(StateArray);
				xil_printf("-----------------------------\r\n\n");
			#endif

		if(i != 10){
			if(i == 1)
			{
				MixColumns_start_time = XTmrCtr_GetValue(&XPS_Timer, 0);
				MixColumns(StateArray);
				MixColumns_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
			}
			else
				MixColumns(StateArray);
		#if (AES_PRINT & AES_PRINT_DETAILS)
			xil_printf("-- Test State - Round %d after MixColumns \r\n\n", i);
			AES_printf(StateArray);
			xil_printf("-----------------------------\r\n\n");
		#endif
		}

		AddRoundKey(ExpandedKey[i], StateArray);
	#if (AES_PRINT & AES_PRINT_DETAILS)
		xil_printf("-- Test State - Round %d after RoundKeyValue \r\n\n", i);
		AES_printf(StateArray);
		xil_printf("-----------------------------\r\n\n");
	#endif
	}
	avgRound_end_time = XTmrCtr_GetValue(&XPS_Timer, 0);
	}

#if (AES_PRINT & AES_PRINT_DETAILS)
	xil_printf("-- AES key expansion and encryption test completed.   \r\n\n");
	xil_printf("-- Test State - End  \r\n\n");
	AES_printf(StateArray);
	xil_printf("-----------------------------\r\n\n");
#endif

	xil_printf("****************Encryption*********************\r\n");

}


void decrypt(){
	unsigned char Ciphertext[4][4];
	memcpy(Ciphertext, StateArray, 4*4*sizeof(unsigned char));
#if (AES_PRINT & AES_PRINT_MAIN)
	xil_printf("-- Starting Decryption   \r\n\n");
#endif
     // TODO:  Code here.
}

