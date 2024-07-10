/**
 ******************************************************************************
 * @file           : task_init.c
 * @brief          : Task Init
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include  "FreeRTOS.h"
#include "queue.h"


void vmainTask(void const *argument);
void fft_task(void const *argument);
static void GlobalError(uint16_t err);

QueueHandle_t xQueue_fft;

/**
 * @brief  The application entry point.
 * @retval int
 */
uint8_t Task_Init(void)
{
  BaseType_t xReturned;

  /* Creat Startup Task */
  xReturned = xTaskCreate(vmainTask, "Main_Task", 400U, NULL, (tskIDLE_PRIORITY + 1U), NULL);

  if (xReturned != pdPASS)
  {
    GlobalError(1);
  }

  /* Creat FFT Task */
  xReturned = xTaskCreate(fft_task, "FFT_Task", 400U, NULL, (tskIDLE_PRIORITY + 1U), NULL);

  if (xReturned != pdPASS)
  {
    GlobalError(1);
  }

  /* Create a queue capable of containing 10 unsigned long values. */
  xQueue_fft = xQueueCreate(10, sizeof(uint32_t));

  if (xQueue_fft == NULL)
  {
    GlobalError(1);
  }

  return 0;

}


/**
 *
 */
static void GlobalError(uint16_t err)
{

  switch (err)
  {

  case 1:
  {
    while (1);
  }

  default:
  {
    while (1);
  }

  }

}



