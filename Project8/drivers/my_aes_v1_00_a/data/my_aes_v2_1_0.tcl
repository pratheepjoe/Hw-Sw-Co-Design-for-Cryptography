##############################################################################
## Filename:          C:\Rajeev\Lab9a/drivers/my_aes_v1_00_a/data/my_aes_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sun May 18 02:49:37 2014 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "my_aes" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
