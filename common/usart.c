/*
 * usart.c - usart diag support for g081_audio
 * 10-10-2021 E. Brombaugh
 */

#include "usart.h"

UART_HandleTypeDef huart2;

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Hang forever */
  while(1)
  {
  }
}

/* USART setup */
void setup_usart(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Setup USART GPIO */
    __HAL_RCC_GPIOA_CLK_ENABLE();
	
    /*
	 * USART2 GPIO Configuration
     * PA14-BOOT0 (pin 8)    ------> USART2_TX
	 * PA2/NRST   (pin 4)    ------> USART2_TX
	 * Note that at one time this was being set up for
	 * Open-drain and 1/2 duplex to avoid constant contention
	 * with the SWCK driver on pin 8. That doesn't work well though
	 * so going with normal PP and full duplex plus driving SWCK
	 * to HI-Z or with some resistance is better.
     */
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Setup USART */
    __HAL_RCC_USART2_CLK_ENABLE();

	/* USART = 115k-8-N-1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * output for tiny printf
 */
void usart_putc(void* p, char c)
{
	while((USART2->ISR & USART_ISR_TXE_TXFNF) == 0)
	{
	}
	USART2->TDR = c;
}
