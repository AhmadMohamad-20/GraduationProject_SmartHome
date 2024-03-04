################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GraduationProject_SmartHome/HAL/EEPROM/DIO_Program.c \
../GraduationProject_SmartHome/HAL/EEPROM/EEPROM_Program.c \
../GraduationProject_SmartHome/HAL/EEPROM/IIC_Program.c \
../GraduationProject_SmartHome/HAL/EEPROM/main.c 

OBJS += \
./GraduationProject_SmartHome/HAL/EEPROM/DIO_Program.o \
./GraduationProject_SmartHome/HAL/EEPROM/EEPROM_Program.o \
./GraduationProject_SmartHome/HAL/EEPROM/IIC_Program.o \
./GraduationProject_SmartHome/HAL/EEPROM/main.o 

C_DEPS += \
./GraduationProject_SmartHome/HAL/EEPROM/DIO_Program.d \
./GraduationProject_SmartHome/HAL/EEPROM/EEPROM_Program.d \
./GraduationProject_SmartHome/HAL/EEPROM/IIC_Program.d \
./GraduationProject_SmartHome/HAL/EEPROM/main.d 


# Each subdirectory must supply rules for building sources it contributes
GraduationProject_SmartHome/HAL/EEPROM/%.o: ../GraduationProject_SmartHome/HAL/EEPROM/%.c GraduationProject_SmartHome/HAL/EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g3 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


