#include "main.h"
//#include <fastmath.h>
#include <math.h>

void exit(int code);
static void SystemClock_Config(void);
static void Error_Handler(void);


int main(void)
{

  int i;

  HAL_Init();
  SystemClock_Config();

  __GPIOC_CLK_ENABLE();

  // LEDs on Discovery F0
  GPIO_InitTypeDef GPIO_InitTypeDefStruct;
  GPIO_InitTypeDefStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8;
  GPIO_InitTypeDefStruct.Mode= GPIO_MODE_OUTPUT_PP;
  GPIO_InitTypeDef* GPIO_Init= & GPIO_InitTypeDefStruct;
  HAL_GPIO_Init(GPIOC,GPIO_Init);



    while (1) {
	for (i = 1000000; i > 0; i--);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
    }



  /* Infinite loop */
  exit (1);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 8000000
  *            PREDIV                         = 1
  *            PLLMUL                         = 6
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    Error_Handler();
  }

}


static void Error_Handler(void)
{
  __asm("BKPT #0\n") ; // Break into the debugger
  while(1)
  {
  }
}

void exit(int code) {
    while (1);
}
