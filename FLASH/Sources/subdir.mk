################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/cpu.c" \
"../Sources/led.c" \
"../Sources/main.c" \
"../Sources/sd.c" \
"../Sources/spi.c" \
"../Sources/transceiver.c" \

C_SRCS += \
../Sources/cpu.c \
../Sources/led.c \
../Sources/main.c \
../Sources/sd.c \
../Sources/spi.c \
../Sources/transceiver.c \

OBJS += \
./Sources/cpu_c.obj \
./Sources/led_c.obj \
./Sources/main_c.obj \
./Sources/sd_c.obj \
./Sources/spi_c.obj \
./Sources/transceiver_c.obj \

OBJS_QUOTED += \
"./Sources/cpu_c.obj" \
"./Sources/led_c.obj" \
"./Sources/main_c.obj" \
"./Sources/sd_c.obj" \
"./Sources/spi_c.obj" \
"./Sources/transceiver_c.obj" \

C_DEPS += \
./Sources/cpu_c.d \
./Sources/led_c.d \
./Sources/main_c.d \
./Sources/sd_c.d \
./Sources/spi_c.d \
./Sources/transceiver_c.d \

C_DEPS_QUOTED += \
"./Sources/cpu_c.d" \
"./Sources/led_c.d" \
"./Sources/main_c.d" \
"./Sources/sd_c.d" \
"./Sources/spi_c.d" \
"./Sources/transceiver_c.d" \

OBJS_OS_FORMAT += \
./Sources/cpu_c.obj \
./Sources/led_c.obj \
./Sources/main_c.obj \
./Sources/sd_c.obj \
./Sources/spi_c.obj \
./Sources/transceiver_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/cpu_c.obj: ../Sources/cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/cpu.args" -ObjN="Sources/cpu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/led_c.obj: ../Sources/led.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/led.args" -ObjN="Sources/led_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/sd_c.obj: ../Sources/sd.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/sd.args" -ObjN="Sources/sd_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/spi_c.obj: ../Sources/spi.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/spi.args" -ObjN="Sources/spi_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/transceiver_c.obj: ../Sources/transceiver.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/transceiver.args" -ObjN="Sources/transceiver_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


