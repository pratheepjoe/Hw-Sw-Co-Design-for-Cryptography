################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/int_microblaze_ver1.c \
../src/int_microblaze_ver2.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/int_microblaze_ver1.o \
./src/int_microblaze_ver2.o 

C_DEPS += \
./src/int_microblaze_ver1.d \
./src/int_microblaze_ver2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../int_microblaze_ver1.c_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


