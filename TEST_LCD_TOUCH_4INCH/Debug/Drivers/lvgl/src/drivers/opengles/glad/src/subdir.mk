################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/opengles/glad/src/egl.c \
../Drivers/lvgl/src/drivers/opengles/glad/src/gles2.c 

OBJS += \
./Drivers/lvgl/src/drivers/opengles/glad/src/egl.o \
./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.o 

C_DEPS += \
./Drivers/lvgl/src/drivers/opengles/glad/src/egl.d \
./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/opengles/glad/src/%.o Drivers/lvgl/src/drivers/opengles/glad/src/%.su Drivers/lvgl/src/drivers/opengles/glad/src/%.cyclo: ../Drivers/lvgl/src/drivers/opengles/glad/src/%.c Drivers/lvgl/src/drivers/opengles/glad/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/UI" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl/examples" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-glad-2f-src

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-glad-2f-src:
	-$(RM) ./Drivers/lvgl/src/drivers/opengles/glad/src/egl.cyclo ./Drivers/lvgl/src/drivers/opengles/glad/src/egl.d ./Drivers/lvgl/src/drivers/opengles/glad/src/egl.o ./Drivers/lvgl/src/drivers/opengles/glad/src/egl.su ./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.cyclo ./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.d ./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.o ./Drivers/lvgl/src/drivers/opengles/glad/src/gles2.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-glad-2f-src

