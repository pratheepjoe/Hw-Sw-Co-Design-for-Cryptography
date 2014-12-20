/*
 * AES_128.h
 *
 *  Created on: Mar 11, 2014
 *      Author: rv4560
 */

#ifndef AES_128_H_
#define AES_128_H_

#include "stdio.h"
#include "string.h"

/**
*Debug levels
*/

//#define AES_PRINT_MAIN    (0<<0)
//#define AES_PRINT_DETAILS (0<<1)

#define AES_PRINT_MAIN    1
#define AES_PRINT_DETAILS 1

#define AES_PRINT (AES_PRINT_MAIN | AES_PRINT_DETAILS)

/**********************************************************
* Functions for key encryption
***********************************************************/

void ExpandKey (unsigned char Key[][4], unsigned char ExpandKey[][4][4]);
void AddRoundKey (unsigned char Key[][4], unsigned char StateArray[][4]);

/**********************************************************
* Functions for AES encryption
***********************************************************/

void SubBytes (unsigned char StateArray[][4]);
void ShiftRows (unsigned char StateArray[][4]);
void MixColumns (unsigned char StateArray[][4]);

unsigned char SubBytesCalculated (unsigned char loc);

/**********************************************************
* Functions for AES decryption
***********************************************************/

void InvSubBytes (unsigned char StateArray[][4]);
void InvShiftRows (unsigned char StateArray[][4]);
void InvMixColumns (unsigned char StateArray[][4]);

/**********************************************************
* Miscellaneous Functions
***********************************************************/

void AES_printf (unsigned char StateArray[][4]);

#endif /* AES_128_H_ */
