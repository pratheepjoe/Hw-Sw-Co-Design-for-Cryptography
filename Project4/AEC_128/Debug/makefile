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
AEC_128_2.elf.size \

ELFCHECK += \
AEC_128_2.elf.elfcheck \


# All Target
all: AEC_128_2.elf secondary-outputs

# Tool invocations
AEC_128_2.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../standalone_bsp_1/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -o"AEC_128_2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

AEC_128_2.elf.size: AEC_128_2.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size AEC_128_2.elf  |tee "AEC_128_2.elf.size"
	@echo Finished building: $@
	@echo ' '

AEC_128_2.elf.elfcheck: AEC_128_2.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck AEC_128_2.elf -hw ../../xps_workspace_cache_hw_platform/system.xml -pe microblaze_0  |tee "AEC_128_2.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) AEC_128_2.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
