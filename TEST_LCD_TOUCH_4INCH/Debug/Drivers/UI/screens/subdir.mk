################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI/screens/ui_AutoScreen.c \
../Drivers/UI/screens/ui_CalibrationScreen.c \
../Drivers/UI/screens/ui_InfoScreen.c \
../Drivers/UI/screens/ui_MainMenu.c \
../Drivers/UI/screens/ui_ManualScreen.c \
../Drivers/UI/screens/ui_SettingScreen.c \
../Drivers/UI/screens/ui_ViewDataScreen.c 

OBJS += \
./Drivers/UI/screens/ui_AutoScreen.o \
./Drivers/UI/screens/ui_CalibrationScreen.o \
./Drivers/UI/screens/ui_InfoScreen.o \
./Drivers/UI/screens/ui_MainMenu.o \
./Drivers/UI/screens/ui_ManualScreen.o \
./Drivers/UI/screens/ui_SettingScreen.o \
./Drivers/UI/screens/ui_ViewDataScreen.o 

C_DEPS += \
./Drivers/UI/screens/ui_AutoScreen.d \
./Drivers/UI/screens/ui_CalibrationScreen.d \
./Drivers/UI/screens/ui_InfoScreen.d \
./Drivers/UI/screens/ui_MainMenu.d \
./Drivers/UI/screens/ui_ManualScreen.d \
./Drivers/UI/screens/ui_SettingScreen.d \
./Drivers/UI/screens/ui_ViewDataScreen.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI/screens/%.o Drivers/UI/screens/%.su Drivers/UI/screens/%.cyclo: ../Drivers/UI/screens/%.c Drivers/UI/screens/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/UI" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl/examples" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI-2f-screens

clean-Drivers-2f-UI-2f-screens:
	-$(RM) ./Drivers/UI/screens/ui_AutoScreen.cyclo ./Drivers/UI/screens/ui_AutoScreen.d ./Drivers/UI/screens/ui_AutoScreen.o ./Drivers/UI/screens/ui_AutoScreen.su ./Drivers/UI/screens/ui_CalibrationScreen.cyclo ./Drivers/UI/screens/ui_CalibrationScreen.d ./Drivers/UI/screens/ui_CalibrationScreen.o ./Drivers/UI/screens/ui_CalibrationScreen.su ./Drivers/UI/screens/ui_InfoScreen.cyclo ./Drivers/UI/screens/ui_InfoScreen.d ./Drivers/UI/screens/ui_InfoScreen.o ./Drivers/UI/screens/ui_InfoScreen.su ./Drivers/UI/screens/ui_MainMenu.cyclo ./Drivers/UI/screens/ui_MainMenu.d ./Drivers/UI/screens/ui_MainMenu.o ./Drivers/UI/screens/ui_MainMenu.su ./Drivers/UI/screens/ui_ManualScreen.cyclo ./Drivers/UI/screens/ui_ManualScreen.d ./Drivers/UI/screens/ui_ManualScreen.o ./Drivers/UI/screens/ui_ManualScreen.su ./Drivers/UI/screens/ui_SettingScreen.cyclo ./Drivers/UI/screens/ui_SettingScreen.d ./Drivers/UI/screens/ui_SettingScreen.o ./Drivers/UI/screens/ui_SettingScreen.su ./Drivers/UI/screens/ui_ViewDataScreen.cyclo ./Drivers/UI/screens/ui_ViewDataScreen.d ./Drivers/UI/screens/ui_ViewDataScreen.o ./Drivers/UI/screens/ui_ViewDataScreen.su

.PHONY: clean-Drivers-2f-UI-2f-screens

