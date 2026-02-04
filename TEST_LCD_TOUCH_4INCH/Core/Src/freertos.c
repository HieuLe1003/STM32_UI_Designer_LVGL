/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "lvgl.h"
// UI labels để update counter hiển thị
extern lv_obj_t * ui_NumSP1;
extern lv_obj_t * ui_NumSP2;
extern lv_obj_t * ui_NumSP3;/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
extern void Set_Servo_Angle(int angle);
extern int current_angle;
extern bool is_Auto_Running;extern void Set_Servo_Angle(int angle);
extern int current_angle;
extern bool is_Auto_Running;
extern void Write_Led_PE3(int state);
extern void Auto_Mode_1();
extern void Auto_Mode_2();
extern void Auto_Mode_3();

bool auto_mode_1 = false;
bool auto_mode_2 = false;
bool auto_mode_3 = false;
bool start_auto = false;
int32_t Angle;

int counter_mode1 = 0;
int counter_mode2 = 0;
int counter_mode3 = 0;

// State tracking để increment counter chỉ 1 lần khi mode hoàn thành
static int last_auto_mode_1 = false;
static int last_auto_mode_2 = false;
static int last_auto_mode_3 = false;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_UI */
osThreadId_t Task_UIHandle;
const osThreadAttr_t Task_UI_attributes = {
  .name = "Task_UI",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityHigh,  // Tăng priority để UI luôn được xử lý
};
/* Definitions for Task_Robot */
osThreadId_t Task_RobotHandle;
const osThreadAttr_t Task_Robot_attributes = {
  .name = "Task_Robot",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,  // Hạ xuống NORMAL để không starve UI
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void UI_Task_Func(void *argument);
void RobotControlTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_UI */
  Task_UIHandle = osThreadNew(UI_Task_Func, NULL, &Task_UI_attributes);

  /* creation of Task_Robot */
  Task_RobotHandle = osThreadNew(RobotControlTask, NULL, &Task_Robot_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_UI_Task_Func */
/**
  * @brief  Function implementing the Task_UI thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_UI_Task_Func */
void UI_Task_Func(void *argument)
{
  /* USER CODE BEGIN UI_Task_Func */
  /* Infinite loop */
  static int last_counter_mode1 = -1, last_counter_mode2 = -1, last_counter_mode3 = -1;
  static int last_angle = -1;
  static lv_obj_t * angle_label = NULL;
  
  for(;;)
  {
    lv_timer_handler(); // Xử lý LVGL
    
    // Update counter labels nếu giá trị thay đổi
    if(last_counter_mode1 != counter_mode1 && ui_NumSP1)
    {
      lv_label_set_text_fmt(ui_NumSP1, "%d", counter_mode1);
      last_counter_mode1 = counter_mode1;
    }
    if(last_counter_mode2 != counter_mode2 && ui_NumSP2)
    {
      lv_label_set_text_fmt(ui_NumSP2, "%d", counter_mode2);
      last_counter_mode2 = counter_mode2;
    }
    if(last_counter_mode3 != counter_mode3 && ui_NumSP3)
    {
      lv_label_set_text_fmt(ui_NumSP3, "%d", counter_mode3);
      last_counter_mode3 = counter_mode3;
    }
    
    // Cập nhật angle hiển thị (nếu có label angle)
    // Note: Cần UI designer add label cho current_angle
    // For now, ta chỉ track giá trị
    if(last_angle != current_angle)
    {
      last_angle = current_angle;
      // TODO: Cập nhật UI label nếu có
    }
    
    osDelay(5);
  }
  /* USER CODE END UI_Task_Func */
}

/* USER CODE BEGIN Header_RobotControlTask */
/**
* @brief Function implementing the Task_Robot thread.
* @param argument: Not used
* @retval None
*/
void RobotControlTask(void *argument)
{
  /* USER CODE BEGIN RobotControlTask */
  
  // Bật PWM nếu cần (như bài trước em nhắc)
  // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  /* Infinite loop */
  for(;;)
  {
    // Cập nhật trạng thái chạy
    if((auto_mode_1 || auto_mode_2 || auto_mode_3) && start_auto)
      is_Auto_Running = true;
    else
      is_Auto_Running = false;
    
    // --- LOGIC ĐẾM CHU KỲ ---
    if(is_Auto_Running)
    {
       if(auto_mode_1)
       {
          // 1. Robot thực hiện hành động (Hàm này có osDelay bên trong nên sẽ tốn thời gian)
          Auto_Mode_1(); 
          
          // 2. Chạy xong hàm trên nghĩa là xong 1 chu kỳ -> Cộng luôn!
          counter_mode1++; 
       }
       else if(auto_mode_2)
       {
          Auto_Mode_2();
          counter_mode2++;
       }
       else if(auto_mode_3)
       {
          Auto_Mode_3();
          counter_mode3++;
       }
       
       // Thêm 1 chút delay nhỏ giữa các chu kỳ nếu cần (để robot thở)
       osDelay(100); 
    }
    else
    {
       // Chế độ Manual
       Set_Servo_Angle(Angle); 
       osDelay(20);
    }
  }
  /* USER CODE END RobotControlTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

