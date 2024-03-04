################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraduationProject_SmartHome/MCAL/ADC/ADC_Program.c 

OBJS += \
./GraduationProject_SmartHome/MCAL/ADC/ADC_Program.o 

C_DEPS += \
./GraduationProject_SmartHome/MCAL/ADC/ADC_Program.d 


# Each subdirectory must supply rules for building sources it contributes
GraduationProject_SmartHome/MCAL/ADC/%.o: ../GraduationProject_SmartHome/MCAL/ADC/%.c GraduationProject_SmartHome/MCAL/ADC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


