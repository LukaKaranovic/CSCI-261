################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/armds_lab1.c 

S_SRCS += \
../src/lab1.s 

C_DEPS += \
./src/armds_lab1.d 

OBJS += \
./src/armds_lab1.o \
./src/lab1.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Arm C Compiler for Embedded 6'
	armclang --target=aarch64-arm-none-eabi -mcpu=cortex-a53+nocrypto -O0 -g -MD -MP -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Arm Assembler 6'
	armclang --target=aarch64-arm-none-eabi -mcpu=cortex-a53+nocrypto -g -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/armds_lab1.d ./src/armds_lab1.o ./src/lab1.o

.PHONY: clean-src

