#include <stdio.h>
#include <string.h>

void gmultiplication(unsigned int mult_num1[4][4], unsigned int mult_num2[4][4], unsigned int mult_X1[4]);
void gcm_aes_function(struct test_plain_text plain, struct Authentication auth, unsigned int init_vect[4][4], struct cipher_text cipher, unsigned int tag[4][4], unsigned int Key[4][4]);
void encrypt(unsigned int PlainText[4][4], unsigned int Key[4][4], unsigned int CipherText[4][4]) ;

#define toFirst(x)		(((unsigned char)x) << 24)
#define toSecond(x)		(((unsigned char)x) << 16)
#define toThird(x)		(((unsigned char)x) <<  8)
#define toFourth(x)		(((unsigned char)x)		 )


#define first(x)		((unsigned char) (x >> 24))
#define second(x)		((unsigned char) (x >> 16))
#define third(x)		((unsigned char) (x >>  8))
#define fourth(x)		((unsigned char) (x		 ))

unsigned int irreducible_poly[4] = { 0xE1000000, 0x000000000, 0x00000000, 0x00000000 };

unsigned int num1[4] = {0};
unsigned int num2[4] = {0};
unsigned int mult_auth_1[4] = {0};
unsigned int mult_auth_2[4] = {0};
unsigned int mult_auth[4] = {0};
unsigned int mult_X1[4] = {0};
unsigned int mult_X2[4] = {0};
unsigned int mult_X3[4] = {0};
unsigned int mult_X4[4] = {0};
unsigned int GHASH[4] = {0};

/*
unsigned char Key[4][4]        = {  {0x2b, 0x28, 0xab, 0x09},
		{0x7e, 0xae, 0xf7, 0xcf},
		{0x15, 0xd2, 0x15, 0x4f},
		{0x16, 0xa6, 0x88, 0x3c} };
*/
unsigned int Key[4][4];

//    W0    W1    W2    W3
/*unsigned char PlainText[4][4]  = {  {0x32, 0x88, 0x31, 0xe0},
		{0x43, 0x5a, 0x31, 0x37},
		{0xf6, 0x30, 0x98, 0x07},
		{0xa8, 0x8d, 0xa2, 0x34} };
*/
unsigned int PlainText[4][4]  = {  {0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00} };

struct test_plain_text{
	unsigned int Plain_1[4][4];
	unsigned int Plain_2[4][4];
	unsigned int Plain_3[4][4];
	unsigned int Plain_4[4][4];
};

struct cipher_text{
	unsigned int Plain_1[4][4];
	unsigned int Plain_2[4][4];
	unsigned int Plain_3[4][4];
	unsigned int Plain_4[4][4];
};

unsigned int init_vect[4][4];
unsigned int tag[4][4];

struct Authentication{
	unsigned int Auth_1[4];
	unsigned int Auth_2[4];
};
/*
unsigned int Len_1[4][4]  = { {0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x02},
		{0x00, 0x00, 0x00, 0x00} };
*/
unsigned int Len_1[4][4]  = { {0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x01},
		{0x00, 0xa0, 0x00, 0xe0} };


void AES_printf (unsigned int AES_StateArray[][4]);

//void encrypt(unsigned int PlainText[4][4], unsigned int Key[4][4], unsigned int CipherText[4][4]);


int main(void) {

	struct Authentication auth_stream;
	struct cipher_text cipher;
	auth_stream.Auth_1 = {0x00, 0x00, 0x00, 0x00};
	auth_stream.Auth_2 = {0x00, 0x00, 0x00, 0x00};

	unsigned int init_vect[4][4];

	struct test_plain_text plain;
//Test case-3
/*
	plain.Plain_1 = {{0xd9, 0xf8, 0xa5, 0xaf},
			{0x31, 0x84, 0x59, 0xf5},
			{0x32, 0x06, 0x09, 0x26},
			{0x25, 0xe5, 0xc5, 0x9a}};

	plain.Plain_2  = {  {0x86, 0x15, 0x2e, 0x8a},
			{0xa7, 0x34, 0x4c, 0x31},
			{0xa9, 0xf7, 0x30, 0x8a},
			{0x53, 0xda, 0x3d, 0x72} };

	plain.Plain_3  = {  {0x1c, 0x95, 0x2f, 0x49},
			{0x3c, 0x68, 0xcf, 0xa6},
			{0x0c, 0x09, 0x0e, 0xb5},
			{0x95, 0x53, 0x24, 0x25} };

	plain.Plain_4  = {  {0xb1, 0xaa, 0xba, 0x1a},
			{0x6a, 0x0d, 0x63, 0xaf},
			{0xed, 0xe6, 0x7b, 0xd2},
			{0xf5, 0x57, 0x39, 0x55} };

	init_vect =  {  {0xca, 0xfa, 0xde, 0x00},
			{0xfe, 0xce, 0xca, 0x00},
			{0xba, 0xdb, 0xf8, 0x00},
			{0xbe, 0xad, 0x88, 0x00} };
	Key       = {  {0xfe,  0x86,  0x6d,  0x67},
		{0xff, 0x65,  0x6a,  0x30},
		{0xe9, 0x73,  0x8f,  0x83},
		{0x92, 0x1c,  0x94,  0x08} };

	gcm_aes_function(plain, auth_stream, init_vect, cipher, tag, Key);
*/
//Test case-4


	auth_stream.Auth_1  = { 0xfeedface, 0xdeadbeef, 0xfeedface, 0xdeadbeef };
	auth_stream.Auth_2  = { 0xabaddad2, 0x0, 0x0, 0x0 };
	plain.Plain_1 = {{0xd9, 0xf8, 0xa5, 0xaf},
			{0x31, 0x84, 0x59, 0xf5},
			{0x32, 0x06, 0x09, 0x26},
			{0x25, 0xe5, 0xc5, 0x9a}};
	plain.Plain_2  = {  {0x86, 0x15, 0x2e, 0x8a},
			{0xa7, 0x34, 0x4c, 0x31},
			{0xa9, 0xf7, 0x30, 0x8a},
			{0x53, 0xda, 0x3d, 0x72} };

	plain.Plain_3  = {  {0x1c, 0x95, 0x2f, 0x49},
			{0x3c, 0x68, 0xcf, 0xa6},
			{0x0c, 0x09, 0x0e, 0xb5},
			{0x95, 0x53, 0x24, 0x25} };

	plain.Plain_4  = {  {0xb1, 0xaa, 0xba, 0x0},
			{0x6a, 0x0d, 0x63, 0x0},
			{0xed, 0xe6, 0x7b, 0x0},
			{0xf5, 0x57, 0x39, 0x0} };

	init_vect =  {  {0xca, 0xfa, 0xde, 0x00},
			{0xfe, 0xce, 0xca, 0x00},
			{0xba, 0xdb, 0xf8, 0x00},
			{0xbe, 0xad, 0x88, 0x00} };
	Key       = {  {0xfe,  0x86,  0x6d,  0x67},
		{0xff, 0x65,  0x6a,  0x30},
		{0xe9, 0x73,  0x8f,  0x83},
		{0x92, 0x1c,  0x94,  0x08} };



	gcm_aes_function(plain, auth_stream, init_vect, cipher, tag, Key);

	return 0;
}
void gcm_aes_function(struct test_plain_text plain, struct Authentication auth, unsigned int init_vect[4][4], struct cipher_text cipher, unsigned int tag[4][4], unsigned int Key[4][4])
{
    unsigned char i, j;
    unsigned int H[4][4];
	unsigned int E_Y_0[4][4];
	unsigned int E_Y_1[4][4];
	unsigned int E_Y_2[4][4];
	unsigned int E_Y_3[4][4];
	unsigned int E_Y_4[4][4];

	unsigned int Cipher_1[4][4];
	unsigned int Cipher_2[4][4];
	unsigned int Cipher_3[4][4];
	unsigned int Cipher_4[4][4];

	encrypt(PlainText,Key,H);

	unsigned int temp_auth_1[4][4];
	for(i=0; i<4; i++){
			temp_auth_1[0][i] = first(auth.Auth_1[i]);
			temp_auth_1[1][i] = second(auth.Auth_1[i]);
			temp_auth_1[2][i] = third(auth.Auth_1[i]);
			temp_auth_1[3][i] = fourth(auth.Auth_1[i]);
	}
    gmultiplication(temp_auth_1, H, mult_auth_1);

    printf("Val of X1 = %x %x %x %x\n", mult_auth_1[0], mult_auth_1[1], mult_auth_1[2], mult_auth_1[3]);
    if(auth.Auth_2[0] != 0x00000000)
    {
    	for(i=0; i<4; i++)
    		mult_auth_1[i] = mult_auth_1[i] ^ auth.Auth_2[i];
    	unsigned int temp_mult_auth_1[4][4];
    	for(i=0; i<4; i++){
    			temp_mult_auth_1[0][i] = first(mult_auth_1[i]);
    			temp_mult_auth_1[1][i] = second(mult_auth_1[i]);
    			temp_mult_auth_1[2][i] = third(mult_auth_1[i]);
    			temp_mult_auth_1[3][i] = fourth(mult_auth_1[i]);
    	}
    	gmultiplication(temp_mult_auth_1, H, mult_auth_2);
    	for(i=0; i<4; i++)
    		mult_auth[i] = mult_auth_2[i];
    }
    else {
	for(i=0; i<4; i++)
	    mult_auth[i] = mult_auth_1[i];
    }


    printf("Val of X2 = %x %x %x %x\n", mult_auth_2[0], mult_auth_2[1], mult_auth_2[2], mult_auth_2[3]);

    unsigned int Y_0[4][4];
    memcpy(Y_0, init_vect, 16*sizeof(int));

    Y_0[3][3] = 0x01;
    encrypt(Y_0, Key, E_Y_0);

	Y_0[3][3] = 0x02;
	encrypt(Y_0,Key,E_Y_1);

	Y_0[3][3] = 0x03;
	encrypt(Y_0,Key,E_Y_2);

	Y_0[3][3] = 0x04;
	encrypt(Y_0,Key,E_Y_3);

	Y_0[3][3] = 0x05;
	encrypt(Y_0,Key,E_Y_4);

	printf("E(K, Y0)\n");
	AES_printf(E_Y_0);
	printf("E(K, Y1)\n");
	AES_printf(E_Y_1);
	printf("E(K, Y2)\n");
	AES_printf(E_Y_2);
	printf("E(K, Y3)\n");
	AES_printf(E_Y_3);
	printf("E(K, Y4)\n");
	AES_printf(E_Y_4);

	for(i=0; i<4; i++)
		for(j=0; j<4; j++){
			Cipher_1[i][j] = E_Y_1[i][j] ^ plain.Plain_1[i][j];
			Cipher_2[i][j] = E_Y_2[i][j] ^ plain.Plain_2[i][j];
			Cipher_3[i][j] = E_Y_3[i][j] ^ plain.Plain_3[i][j];
			Cipher_4[i][j] = E_Y_4[i][j] ^ plain.Plain_4[i][j];
		}

	if(plain.Plain_4[0][3]==0x00 && plain.Plain_4[1][3]==0x00 && plain.Plain_4[2][3]==0x00 && plain.Plain_4[3][3]==0x00)
	{
		Cipher_4[0][3] = 0x00;
		Cipher_4[1][3] = 0x00;
		Cipher_4[2][3] = 0x00;
		Cipher_4[3][3] = 0x00;
	}
	printf("Ciphertext1\n");
	AES_printf(Cipher_1);
	printf("Ciphertext2\n");
	AES_printf(Cipher_2);
	printf("Ciphertext3\n");
	AES_printf(Cipher_3);
	printf("Ciphertext4\n");
	AES_printf(Cipher_4);

	unsigned temp_mult_auth[4][4]= {0};
	for(i=0; i<4; i++){
		temp_mult_auth[0][i] = first(mult_auth[i]);
		temp_mult_auth[1][i] = second(mult_auth[i]);
		temp_mult_auth[2][i] = third(mult_auth[i]);
		temp_mult_auth[3][i] = fourth(mult_auth[i]);
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			Cipher_1[i][j] ^= temp_mult_auth[i][j];
		}
	}
	gmultiplication(Cipher_1, H, mult_X1);


	// MULT X2

	unsigned int temp_cipher[4]= {0};
	for(i =0; i<4; i++){
		temp_cipher[i] = toFirst(Cipher_2[0][i]) | toSecond(Cipher_2[1][i]) | toThird(Cipher_2[2][i]) | toFourth(Cipher_2[3][i]);
	}

	for(i=0; i<4; i++)
		temp_cipher[i] = temp_cipher[i] ^ mult_X1[i];

	for(i=0; i<4; i++){
		Cipher_2[0][i] = first(temp_cipher[i]);
		Cipher_2[1][i] = second(temp_cipher[i]);
		Cipher_2[2][i] = third(temp_cipher[i]);
		Cipher_2[3][i] = fourth(temp_cipher[i]);
	}

	gmultiplication(Cipher_2, H, mult_X2);

	// MULT X3

	unsigned int temp_cipher1[4]= {0};
	for(i =0; i<4; i++){
		temp_cipher1[i] = toFirst(Cipher_3[0][i]) | toSecond(Cipher_3[1][i]) | toThird(Cipher_3[2][i]) | toFourth(Cipher_3[3][i]);
	}

	for(i=0; i<4; i++)
		temp_cipher1[i] = temp_cipher1[i] ^ mult_X2[i];

	for(i=0; i<4; i++){
		Cipher_3[0][i] = first(temp_cipher1[i]);
		Cipher_3[1][i] = second(temp_cipher1[i]);
		Cipher_3[2][i] = third(temp_cipher1[i]);
		Cipher_3[3][i] = fourth(temp_cipher1[i]);
	}

	gmultiplication(Cipher_3, H, mult_X3);

	// MULT X4

	unsigned int temp_cipher2[4]= {0};
		for(i =0; i<4; i++){
			temp_cipher2[i] = toFirst(Cipher_4[0][i]) | toSecond(Cipher_4[1][i]) | toThird(Cipher_4[2][i]) | toFourth(Cipher_4[3][i]);
		}

			for(i=0; i<4; i++)
				temp_cipher2[i] = temp_cipher2[i] ^ mult_X3[i];

			for(i=0; i<4; i++){
				Cipher_4[0][i] = first(temp_cipher2[i]);
				Cipher_4[1][i] = second(temp_cipher2[i]);
				Cipher_4[2][i] = third(temp_cipher2[i]);
				Cipher_4[3][i] = fourth(temp_cipher2[i]);
			}

			gmultiplication(Cipher_4, H, mult_X4);

			printf("Val of X3 = %x %x %x %x\n", mult_X1[0], mult_X1[1], mult_X1[2], mult_X1[3]);
			printf("Val of X4= %x %x %x %x\n", mult_X2[0], mult_X2[1], mult_X2[2], mult_X2[3]);
			printf("Val of X5= %x %x %x %x\n", mult_X3[0], mult_X3[1], mult_X3[2], mult_X3[3]);
			printf("Val of X6= %x %x %x %x\n", mult_X4[0], mult_X4[1], mult_X4[2], mult_X4[3]);


	// lenth xor

			unsigned int temp_Lenth[4]= {0};
				for(i =0; i<4; i++){
					temp_Lenth[i] = toFirst(Len_1[0][i]) | toSecond(Len_1[1][i]) | toThird(Len_1[2][i]) | toFourth(Len_1[3][i]);
				}

			for(i=0; i<4; i++)
				temp_Lenth[i] = temp_Lenth[i] ^ mult_X4[i];

			unsigned int TempLenth[4][4]= {0};
			for(i=0; i<4; i++){
				TempLenth[0][i] = first(temp_Lenth[i]);
				TempLenth[1][i] = second(temp_Lenth[i]);
				TempLenth[2][i] = third(temp_Lenth[i]);
				TempLenth[3][i] = fourth(temp_Lenth[i]);
			}

			gmultiplication(TempLenth, H, GHASH);

			printf("Val of GHASH= %x %x %x %x\n", GHASH[0], GHASH[1], GHASH[2], GHASH[3]);
	// Final Tag

			unsigned int temp_Tag[4]= {0};
				for(i =0; i<4; i++){
					temp_Tag[i] = toFirst(E_Y_0[0][i]) | toSecond(E_Y_0[1][i]) | toThird(E_Y_0[2][i]) | toFourth(E_Y_0[3][i]);
				}

			for(i=0; i<4; i++)
				temp_Tag[i] = temp_Tag[i] ^ GHASH[i];

			printf("Val of Tag= %x %x %x %x\n", temp_Tag[0], temp_Tag[1], temp_Tag[2], temp_Tag[3]);

}




void AES_printf (unsigned int AES_StateArray[][4])
{
    int i;
    printf("   W0  W1  W2  W3\n\n");
    for(i=0; i<4; i++)
        printf("   %02x  %02x  %02x  %02x\n",
                AES_StateArray[i][0], AES_StateArray[i][1],
                AES_StateArray[i][2], AES_StateArray[i][3]);
    printf("\n");
}




void right_shift(void)
{
    unsigned char i;
    unsigned int temp[3] = {0};
    for (i=0; i<3; i++)
	temp[i] = num1[i] & 0x01;
    num1[0] = num1[0]>>1;
    for (i=1; i<4; i++)
        num1[i] = (num1[i]>>1)| temp[i-1]<<31;
}

void left_shift(void)
{
    unsigned char i;
    unsigned int temp[4] = {0};
    for (i=0; i<4; i++)
	temp[i] = num2[i] & 0x80000000;
    num2[3] = num2[3]<<1;
    for (i=0; i<3; i++)
        num2[i] = ((num2[i]<<1)| temp[i+1]>>31)&0xFFFFFFFF;
}

void mod_function()
{
    unsigned char i;
    for(i=0; i<4; i++)
	num1[i] = num1[i]^irreducible_poly[i];
}

void gmultiplication(unsigned int mult_num1[4][4], unsigned int mult_num2[4][4], unsigned int mult_result[4]) {

		unsigned int OutOfRange;
		unsigned int i,j;

	    for(i =0; i<4; i++){
			num1[i] = toFirst(mult_num1[0][i]) | toSecond(mult_num1[1][i]) | toThird(mult_num1[2][i]) | toFourth(mult_num1[3][i]);
			num2[i] = toFirst(mult_num2[0][i]) | toSecond(mult_num2[1][i]) | toThird(mult_num2[2][i]) | toFourth(mult_num2[3][i]);
		}
        for (i = 0; i < 128; i++) {
                if (num2[0] & 0x80000000)
		{
                       for(j=0; j<4; j++)
		            mult_result[j] = mult_result[j] ^ num1[j];
		}
		OutOfRange = (num1[3] & 0x1);
                right_shift();
                if (OutOfRange)
                        mod_function();
                left_shift();

        }
}
