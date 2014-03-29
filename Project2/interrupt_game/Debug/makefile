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
interrupt_game.elf.size \

ELFCHECK += \
interrupt_game.elf.elfcheck \


# All Target
all: interrupt_game.elf secondary-outputs

# Tool invocations
interrupt_game.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,--no-relax -Wl,-T -Wl,../src/lscript.ld -L../../int_microblaze_ver1.c_bsp/microblaze_0/lib -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -o"interrupt_game.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

interrupt_game.elf.size: interrupt_game.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size interrupt_game.elf  |tee "interrupt_game.elf.size"
	@echo Finished building: $@
	@echo ' '

interrupt_game.elf.elfcheck: interrupt_game.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck interrupt_game.elf -hw ../../Lab2_workspace_hw_platform/system.xml -pe microblaze_0  |tee "interrupt_game.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) interrupt_game.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
