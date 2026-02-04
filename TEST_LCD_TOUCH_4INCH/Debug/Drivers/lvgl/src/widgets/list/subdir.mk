################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/widgets/list/lv_list.c 

OBJS += \
./Drivers/lvgl/src/widgets/list/lv_list.o 

C_DEPS += \
./Drivers/lvgl/src/widgets/list/lv_list.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/widgets/list/%.o Drivers/lvgl/src/widgets/list/%.su Drivers/lvgl/src/widgets/list/%.cyclo: ../Drivers/lvgl/src/widgets/list/%.c Drivers/lvgl/src/widgets/list/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/UI" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl/examples" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-list

clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-list:
	-$(RM) ./Drivers/lvgl/src/widgets/list/lv_list.cyclo ./Drivers/lvgl/src/widgets/list/lv_list.d ./Drivers/lvgl/src/widgets/list/lv_list.o ./Drivers/lvgl/src/widgets/list/lv_list.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-widgets-2f-list

