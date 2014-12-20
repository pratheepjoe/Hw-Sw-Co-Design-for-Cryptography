#include "xparameters.h"
#include "my_aes.h"

Xuint32* my_aes_baseaddr = (Xuint32*) XPAR_MY_AES_0_BASEADDR;

int main (void) {

  Xuint32 Reg32Value0;
  Xuint32 Reg32Value1, Reg32Value2, Reg32Value3, Reg32Value4;
  Xuint32 Reg32Value5, Reg32Value6, Reg32Value7, Reg32Value8;
  Xuint32 Reg32Value9, Reg32Value10, Reg32Value11, Reg32Value12;
  
// Clear the screen
  xil_printf("%c[2J",27);

  xil_printf("Starting test of the AES 128 based on FIPS-197 (Appendix - B)\r\n\n");
  xil_printf(" --- Sending the key --- \r\n");
  xil_printf("\n*************************\r\n");
  
  MY_AES_mWriteSlaveReg1(XPAR_MY_AES_0_BASEADDR, 0, 0x2b7e1516);
  MY_AES_mWriteSlaveReg2(XPAR_MY_AES_0_BASEADDR, 0, 0x28aed2a6);
  MY_AES_mWriteSlaveReg3(XPAR_MY_AES_0_BASEADDR, 0, 0xabf71588);
  MY_AES_mWriteSlaveReg4(XPAR_MY_AES_0_BASEADDR, 0, 0x09cf4f3c);

  
  xil_printf(" --- Sending the command - expand the key\r\n");
  MY_AES_mWriteSlaveReg0(XPAR_MY_AES_0_BASEADDR, 0, 0x00000001);
  // Reset control
  MY_AES_mWriteSlaveReg0(XPAR_MY_AES_0_BASEADDR, 0, 0x00000000); 

  xil_printf("\n*************************\r\n");
  xil_printf(" --- Sending the PT --- \r\n");
  xil_printf("\n*************************\r\n");

  MY_AES_mWriteSlaveReg5(XPAR_MY_AES_0_BASEADDR, 0, 0x3243f6a8);
  MY_AES_mWriteSlaveReg6(XPAR_MY_AES_0_BASEADDR, 0, 0x885a308d);
  MY_AES_mWriteSlaveReg7(XPAR_MY_AES_0_BASEADDR, 0, 0x313198a2);
  MY_AES_mWriteSlaveReg8(XPAR_MY_AES_0_BASEADDR, 0, 0xe0370734);

  xil_printf(" --- Sending the command - encrypt\r\n");
  MY_AES_mWriteSlaveReg0(XPAR_MY_AES_0_BASEADDR, 0, 0x00000010);
  // Reset control
  MY_AES_mWriteSlaveReg0(XPAR_MY_AES_0_BASEADDR, 0, 0x00000000);
  
  Reg32Value9  = MY_AES_mReadSlaveReg9(XPAR_MY_AES_0_BASEADDR, 0);
  Reg32Value10 = MY_AES_mReadSlaveReg10(XPAR_MY_AES_0_BASEADDR, 0);
  Reg32Value11 = MY_AES_mReadSlaveReg11(XPAR_MY_AES_0_BASEADDR, 0);
  Reg32Value12 = MY_AES_mReadSlaveReg12(XPAR_MY_AES_0_BASEADDR, 0);

  xil_printf("\n*************************\r\n");
  xil_printf(" --- Reading the CT --- \r\n\n");

  xil_printf("%02x %02x %02x %02x\n\r", (Xuint8) (Reg32Value9  >> 24), (Xuint8) (Reg32Value10 >> 24), 
                                        (Xuint8) (Reg32Value11 >> 24), (Xuint8) (Reg32Value12 >> 24) );
  xil_printf("%02x %02x %02x %02x\n\r", (Xuint8) (Reg32Value9  >> 16), (Xuint8) (Reg32Value10 >> 16), 
                                        (Xuint8) (Reg32Value11 >> 16), (Xuint8) (Reg32Value12 >> 16) );
  xil_printf("%02x %02x %02x %02x\n\r", (Xuint8) (Reg32Value9  >> 8),  (Xuint8) (Reg32Value10 >> 8),  
                                        (Xuint8) (Reg32Value11 >> 8),  (Xuint8) (Reg32Value12 >> 8) );
  xil_printf("%02x %02x %02x %02x\n\r", (Xuint8) (Reg32Value9  >> 0),  (Xuint8) (Reg32Value10 >> 0),  
                                        (Xuint8) (Reg32Value11 >> 0),  (Xuint8) (Reg32Value12 >> 0) );

  xil_printf("\n*************************\r\n");

  xil_printf("\n");
  xil_printf(" --- End of test  --- \r\n");
  xil_printf("\n");
}

