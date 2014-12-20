/*****************************************************************************
* Filename:          C:\Rajeev\Lab9a/drivers/my_aes_v1_00_a/src/my_aes.h
* Version:           1.00.a
* Description:       my_aes Driver Header File
* Date:              Sun May 18 02:49:37 2014 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef MY_AES_H
#define MY_AES_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 * -- SLV_REG0 : user logic slave module register 0
 * -- SLV_REG1 : user logic slave module register 1
 * -- SLV_REG2 : user logic slave module register 2
 * -- SLV_REG3 : user logic slave module register 3
 * -- SLV_REG4 : user logic slave module register 4
 * -- SLV_REG5 : user logic slave module register 5
 * -- SLV_REG6 : user logic slave module register 6
 * -- SLV_REG7 : user logic slave module register 7
 * -- SLV_REG8 : user logic slave module register 8
 * -- SLV_REG9 : user logic slave module register 9
 * -- SLV_REG10 : user logic slave module register 10
 * -- SLV_REG11 : user logic slave module register 11
 * -- SLV_REG12 : user logic slave module register 12
 */
#define MY_AES_USER_SLV_SPACE_OFFSET (0x00000000)
#define MY_AES_SLV_REG0_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000000)
#define MY_AES_SLV_REG1_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000004)
#define MY_AES_SLV_REG2_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000008)
#define MY_AES_SLV_REG3_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x0000000C)
#define MY_AES_SLV_REG4_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000010)
#define MY_AES_SLV_REG5_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000014)
#define MY_AES_SLV_REG6_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000018)
#define MY_AES_SLV_REG7_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x0000001C)
#define MY_AES_SLV_REG8_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000020)
#define MY_AES_SLV_REG9_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000024)
#define MY_AES_SLV_REG10_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000028)
#define MY_AES_SLV_REG11_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x0000002C)
#define MY_AES_SLV_REG12_OFFSET (MY_AES_USER_SLV_SPACE_OFFSET + 0x00000030)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a MY_AES register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the MY_AES device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MY_AES_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define MY_AES_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a MY_AES register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the MY_AES device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 MY_AES_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define MY_AES_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Write/Read 32 bit value to/from MY_AES user logic slave registers.
 *
 * @param   BaseAddress is the base address of the MY_AES device.
 * @param   RegOffset is the offset from the slave register to write to or read from.
 * @param   Value is the data written to the register.
 *
 * @return  Data is the data from the user logic slave register.
 *
 * @note
 * C-style signature:
 * 	void MY_AES_mWriteSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Value)
 * 	Xuint32 MY_AES_mReadSlaveRegn(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define MY_AES_mWriteSlaveReg0(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG0_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg1(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG1_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg2(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG2_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg3(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG3_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg4(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG4_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg5(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG5_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg6(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG6_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg7(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG7_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg8(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG8_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg9(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG9_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg10(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG10_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg11(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG11_OFFSET) + (RegOffset), (Xuint32)(Value))
#define MY_AES_mWriteSlaveReg12(BaseAddress, RegOffset, Value) \
 	Xil_Out32((BaseAddress) + (MY_AES_SLV_REG12_OFFSET) + (RegOffset), (Xuint32)(Value))

#define MY_AES_mReadSlaveReg0(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG0_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg1(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG1_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg2(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG2_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg3(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG3_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg4(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG4_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg5(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG5_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg6(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG6_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg7(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG7_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg8(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG8_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg9(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG9_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg10(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG10_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg11(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG11_OFFSET) + (RegOffset))
#define MY_AES_mReadSlaveReg12(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (MY_AES_SLV_REG12_OFFSET) + (RegOffset))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the MY_AES instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus MY_AES_SelfTest(void * baseaddr_p);

#endif /** MY_AES_H */
