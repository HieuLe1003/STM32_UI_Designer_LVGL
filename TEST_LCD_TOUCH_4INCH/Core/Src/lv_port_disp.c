/**
 * @file lv_port_disp.c
 */
#if 1

/*********************
 * INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "main.h"
#include "lcd.h"
#include "spi.h" 

/*********************
 * DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    #define MY_DISP_HOR_RES    480
#endif

#ifndef MY_DISP_VER_RES
    #define MY_DISP_VER_RES    320
#endif

#define BUFF_SIZE (MY_DISP_HOR_RES * 48)

/**********************
 * STATIC PROTOTYPES
 **********************/
static void disp_init(void);
static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/* Hàm này giờ là static, chỉ nằm nội bộ file này, rất gọn */
static void transfer_complete_cb(SPI_HandleTypeDef *hspi);

/**********************
 * STATIC VARIABLES
 **********************/
static lv_display_t * disp_drv; 

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /* 1. Init phần cứng và đăng ký Callback trước */
    disp_init();

    /* 2. Tạo đối tượng màn hình */
    disp_drv = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_color_format(disp_drv, LV_COLOR_FORMAT_RGB565_SWAPPED);
    lv_display_set_rotation(disp_drv, LV_DISPLAY_ROTATION_0);
    lv_display_set_flush_cb(disp_drv, disp_flush);

    /* 3. Cấu hình Buffer */
    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_1[BUFF_SIZE * 2];
    LV_ATTRIBUTE_MEM_ALIGN
    static uint8_t buf_2[BUFF_SIZE * 2];

    lv_display_set_buffers(disp_drv, buf_1, buf_2, sizeof(buf_1), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/**********************
 * STATIC FUNCTIONS
 **********************/

static void disp_init(void)
{
    // 1. Init LCD
    LCD_Init(); 
    HAL_Delay(500);

    // 2. ĐĂNG KÝ CALLBACK (QUAN TRỌNG)
    // Sếp nhớ bật #define USE_HAL_SPI_REGISTER_CALLBACKS 1 trong stm32h7xx_hal_conf.h
    // Nếu không bật, hàm này sẽ báo lỗi biên dịch
    if(HAL_SPI_RegisterCallback(&hspi2, HAL_SPI_TX_COMPLETE_CB_ID, transfer_complete_cb) != HAL_OK)
    {
        // Xử lý lỗi nếu đăng ký thất bại (thường ít khi vào đây)
        Error_Handler();
    }
}

/* Hàm callback này giờ nằm gọn trong file này, cực kỳ an toàn */
static void transfer_complete_cb(SPI_HandleTypeDef *hspi)
{
    if(hspi->Instance == SPI2) 
    {
        LCD_CS_SET;
        
        // Vì disp_drv là biến static trong file này, ta gọi được luôn
        // mà không cần extern lằng nhằng
        if(disp_drv) lv_display_flush_ready(disp_drv);
    }
}

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    // Chờ SPI rảnh
    while((hspi2.Instance->SR & (1 << 12)) != 0);

    // Set tọa độ
    LCD_SetWindows(area->x1, area->y1, area->x2, area->y2);

    // Chờ SPI rảnh lần 2
    while((hspi2.Instance->SR & (1 << 12)) != 0);

    // Delay nhỏ cho CS
    for(volatile int i=0; i<50; i++) { __NOP(); }

    LCD_CS_CLR;     
    LCD_RS_SET;     

    uint32_t width = (area->x2 - area->x1 + 1);
    uint32_t height = (area->y2 - area->y1 + 1);
    uint32_t size = width * height * 2;

    // Clean Cache
    SCB_CleanDCache_by_Addr((uint32_t*)px_map, (size + 31) & ~0x1F);

    // Bắn DMA
    if(HAL_SPI_Transmit_DMA(&hspi2, px_map, size) != HAL_OK)
    {
        LCD_CS_SET;
        lv_display_flush_ready(disp);
    }
}

#else 
typedef int keep_pedantic_happy;
#endif