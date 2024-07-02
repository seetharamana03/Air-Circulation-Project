################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../qe_gen/ble/app_main.c \
../qe_gen/ble/qe_ble_profile.c \
../qe_gen/ble/r_ble_evktempctrls.c \
../qe_gen/ble/r_ble_gapc.c \
../qe_gen/ble/r_ble_gaps.c \
../qe_gen/ble/r_ble_gats.c \
../qe_gen/ble/r_ble_rtcs.c \
../qe_gen/ble/r_ble_senss.c 

C_DEPS += \
./qe_gen/ble/app_main.d \
./qe_gen/ble/qe_ble_profile.d \
./qe_gen/ble/r_ble_evktempctrls.d \
./qe_gen/ble/r_ble_gapc.d \
./qe_gen/ble/r_ble_gaps.d \
./qe_gen/ble/r_ble_gats.d \
./qe_gen/ble/r_ble_rtcs.d \
./qe_gen/ble/r_ble_senss.d 

OBJS += \
./qe_gen/ble/app_main.o \
./qe_gen/ble/qe_ble_profile.o \
./qe_gen/ble/r_ble_evktempctrls.o \
./qe_gen/ble/r_ble_gapc.o \
./qe_gen/ble/r_ble_gaps.o \
./qe_gen/ble/r_ble_gats.o \
./qe_gen/ble/r_ble_rtcs.o \
./qe_gen/ble/r_ble_senss.o 

SREC += \
AirCirculationRTOS.srec 

MAP += \
AirCirculationRTOS.map 


# Each subdirectory must supply rules for building sources it contributes
qe_gen/ble/%.o: ../qe_gen/ble/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/src" -I"." -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/fsp/inc" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/fsp/inc/api" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/fsp/inc/instances" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/fsp/src/rm_freertos_port" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/aws/FreeRTOS/FreeRTOS/Source/include" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra_gen" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra_cfg/fsp_cfg/bsp" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra_cfg/fsp_cfg" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra_cfg/aws" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/ra/renesas/wireless/da14xxx/r_ble_gtl" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/qe_gen" -I"C:/Users/a5150930/e2_studio/workspace/AirCirculationRTOS/qe_gen/ble" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

