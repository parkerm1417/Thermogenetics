################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Downlink.c \
../source/Flash.c \
../source/I2C_Master.c \
../source/Power.c \
../source/TempSensor.c \
../source/Thermogenetics.c \
../source/Timer.c \
../source/Well.c \
../source/crc32.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/Downlink.o \
./source/Flash.o \
./source/I2C_Master.o \
./source/Power.o \
./source/TempSensor.o \
./source/Thermogenetics.o \
./source/Timer.o \
./source/Well.o \
./source/crc32.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/Downlink.d \
./source/Flash.d \
./source/I2C_Master.d \
./source/Power.d \
./source/TempSensor.d \
./source/Thermogenetics.d \
./source/Timer.d \
./source/Well.d \
./source/crc32.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL02Z32CAF4 -DCPU_MKL02Z32CAF4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\drivers" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\utilities" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\CMSIS" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\drivers" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\CMSIS" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\utilities" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\board" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\source" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics" -I"C:\Users\12mcp\Documents\MCUXpressoIDE_11.4.1_6260\workspace2\Thermogenetics\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


