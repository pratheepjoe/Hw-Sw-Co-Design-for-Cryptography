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
Hardware_gprof.elf.size \

ELFCHECK += \
Hardware_gprof.elf.elfcheck \


# All Target
all: Hardware_gprof.elf secondary-outputs

# Tool invocations
Hardware_gprof.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -pg -L../../standalone_bsp_1/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.a -mno-xl-soft-mul -o"Hardware_gprof.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

Hardware_gprof.elf.size: Hardware_gprof.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size Hardware_gprof.elf  |tee "Hardware_gprof.elf.size"
	@echo Finished building: $@
	@echo ' '

Hardware_gprof.elf.elfcheck: Hardware_gprof.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck Hardware_gprof.elf -hw ../../xps_workspace_hw_platform/system.xml -pe microblaze_0  |tee "Hardware_gprof.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) Hardware_gprof.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
