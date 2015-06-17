################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/CPU.c" \
"../Sources/LED.c" \
"../Sources/SD.c" \
"../Sources/Transceiver.c" \
"../Sources/main.c" \
"../Sources/spi.c" \
"../Sources/storage.c" \

C_SRCS += \
../Sources/CPU.c \
../Sources/LED.c \
../Sources/SD.c \
../Sources/Transceiver.c \
../Sources/main.c \
../Sources/spi.c \
../Sources/storage.c \

OBJS += \
./Sources/CPU_c.obj \
./Sources/LED_c.obj \
./Sources/SD_c.obj \
./Sources/Transceiver_c.obj \
./Sources/main_c.obj \
./Sources/spi_c.obj \
./Sources/storage_c.obj \

OBJS_QUOTED += \
"./Sources/CPU_c.obj" \
"./Sources/LED_c.obj" \
"./Sources/SD_c.obj" \
"./Sources/Transceiver_c.obj" \
"./Sources/main_c.obj" \
"./Sources/spi_c.obj" \
"./Sources/storage_c.obj" \

C_DEPS += \
./Sources/CPU_c.d \
./Sources/LED_c.d \
./Sources/SD_c.d \
./Sources/Transceiver_c.d \
./Sources/main_c.d \
./Sources/spi_c.d \
./Sources/storage_c.d \

C_DEPS_QUOTED += \
"./Sources/CPU_c.d" \
"./Sources/LED_c.d" \
"./Sources/SD_c.d" \
"./Sources/Transceiver_c.d" \
"./Sources/main_c.d" \
"./Sources/spi_c.d" \
"./Sources/storage_c.d" \

OBJS_OS_FORMAT += \
./Sources/CPU_c.obj \
./Sources/LED_c.obj \
./Sources/SD_c.obj \
./Sources/Transceiver_c.obj \
./Sources/main_c.obj \
./Sources/spi_c.obj \
./Sources/storage_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/CPU_c.obj: ../Sources/CPU.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/CPU.args" -ObjN="Sources/CPU_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/LED_c.obj: ../Sources/LED.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/LED.args" -ObjN="Sources/LED_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SD_c.obj: ../Sources/SD.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SD.args" -ObjN="Sources/SD_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Transceiver_c.obj: ../Sources/Transceiver.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Transceiver.args" -ObjN="Sources/Transceiver_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/spi_c.obj: ../Sources/spi.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/spi.args" -ObjN="Sources/spi_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/storage_c.obj: ../Sources/storage.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/storage.args" -ObjN="Sources/storage_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


