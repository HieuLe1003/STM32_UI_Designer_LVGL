/**
 * @file lv_port_indev.c
 *
 */
#if 1 

/*********************
 * INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "touch.h"      // <--- QUAN TRỌNG: Gọi thư viện cũ của sếp
#include "main.h"

/*********************
 * DEFINES
 *********************/

/**********************
 * TYPEDEFS
 **********************/

/**********************
 * STATIC PROTOTYPES
 **********************/
static void touchpad_init(void);
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data);

/**********************
 * STATIC VARIABLES
 **********************/
lv_indev_t * indev_touchpad;

/**********************
 * MACROS
 **********************/

/**********************
 * GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /*----------------------------------------------------
     * 1. Khởi tạo phần cứng Touch (Dùng hàm cũ của sếp)
     *----------------------------------------------------*/
    touchpad_init();

    /*----------------------------------------------------
     * 2. Đăng ký driver input cho LVGL (LVGL v9)
     *----------------------------------------------------*/
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);
}

/**********************
 * STATIC FUNCTIONS
 **********************/

/*----------------------------------------------------------------------
 * Hàm khởi tạo (Wrapper)
 *--------------------------------------------------------------------*/
static void touchpad_init(void)
{
    // Gọi hàm TP_Init() trong file touch.c của sếp
    // Hàm này sẽ init GPIO I2C mềm và chip FT6336
    TP_Init(); 
}

/*----------------------------------------------------------------------
 * Hàm đọc cảm ứng (LVGL gọi liên tục)
 *--------------------------------------------------------------------*/
static void touchpad_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    // 1. Quét cảm ứng (Gọi hàm Scan trong touch.c)
    // Biến tp_dev.scan là con trỏ hàm trỏ tới FT6336_Scan
    if(tp_dev.scan) tp_dev.scan(); 

    // 2. Kiểm tra trạng thái
    // TP_PRES_DOWN (0x80) nghĩa là đang có ngón tay nhấn
    if(tp_dev.sta & TP_PRES_DOWN)
    {
        data->state = LV_INDEV_STATE_PRESSED;
        
        // 3. Lấy tọa độ
        // Code FT6336_Scan cũ của sếp đã xử lý xoay màn hình rồi
        // nên ta cứ lấy thẳng x[0], y[0] gán vào thôi
        data->point.x = tp_dev.x[0];
        data->point.y = tp_dev.y[0];
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

#else /*Enable this file at the top*/

typedef int keep_pedantic_happy;

#endif