################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.c \
../Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.c 

OBJS += \
./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.o \
./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.o 

C_DEPS += \
./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.d \
./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/drivers/opengles/opengl_shader/%.o Drivers/lvgl/src/drivers/opengles/opengl_shader/%.su Drivers/lvgl/src/drivers/opengles/opengl_shader/%.cyclo: ../Drivers/lvgl/src/drivers/opengles/opengl_shader/%.c Drivers/lvgl/src/drivers/opengles/opengl_shader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/UI" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl/examples" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers/lvgl" -I"F:/Git_Clone/STM32_UI_Designer_LVGL/TEST_LCD_TOUCH_4INCH/Drivers" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-opengl_shader

clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-opengl_shader:
	-$(RM) ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.cyclo ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.d ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.o ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_manager.su ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.cyclo ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.d ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.o ./Drivers/lvgl/src/drivers/opengles/opengl_shader/lv_opengl_shader_program.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-drivers-2f-opengles-2f-opengl_shader

