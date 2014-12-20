################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
AES_128_2.elf.size \

ELFCHECK += \
AES_128_2.elf.elfcheck \


# All Target
all: AES_128_2.elf secondary-outputs

# Tool invocations
AES_128_2.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../standalone_bsp_1/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -o"AES_128_2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

AES_128_2.elf.size: AES_128_2.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size AES_128_2.elf  |tee "AES_128_2.elf.size"
	@echo Finished building: $@
	@echo ' '

AES_128_2.elf.elfcheck: AES_128_2.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck AES_128_2.elf -hw ../../xps_workspace_cache32_hw_platform/system.xml -pe microblaze_0  |tee "AES_128_2.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) AES_128_2.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
