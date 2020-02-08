/**
 * @file 	interrupts.c
 * @brief 	GPIO interrupt handler implementation example
 * @note 	Platform and system dependent 
 * @date 	8 feb 2020 г.
 * @author 	Peter Borisenko
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

extern SemaphoreHandle_t s_xSemaphoreSpi;

void EXTI_IRQ9_5Handler(void)
{
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
  if ((EXTI->IMR & EXTI_Line6) && (EXTI->PR & EXTI_Line6))
  {
    EXTI_ClearITPendingBit(0x007FFFFF); // Очищаем все флаги
    xSemaphoreGiveFromISR( s_xSemaphoreSpi, &xHigherPriorityTaskWoken);
  }
  // Switch tasks if necessary. */
  if( xHigherPriorityTaskWoken != pdFALSE )
  {
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
  }
}

