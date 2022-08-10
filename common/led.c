/*
 * led.c - g030J6 nucleo LED setup
 */

#include "led.h"

/*
 * Initialize the LED
 */
void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : LED_GREEN_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
}

/*
 * Turn on LED
 */
void LEDOn(void)
{
	LED_GPIO_Port->BSRR = LED_Pin;
}

/*
 * Turn off LED
 */
void LEDOff(void)
{
	LED_GPIO_Port->BSRR = LED_Pin;
}

/*
 * Toggle LED
 */
void LEDToggle(void)
{
	LED_GPIO_Port->ODR ^= LED_Pin;
}

