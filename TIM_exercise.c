#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"

//For the timer every 100 ms using polling
void delay(uint32_t cnt)
{
	while(cnt)
		cnt--;
}

GPIO_handle_t LED;
TIM_Handle_t htim_Tim;

void GPIO_LED_Init(void)
{
	LED.pGPIOx = GPIOA;
	LED.GPIO_config.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_config.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_config.GPIO_Pin = GPIO_PIN_5;
	LED.GPIO_config.GPIO_PuPd = GPIO_PuPd_NONE;
	LED.GPIO_config.GPIO_Speed = GPIO_Speed_LOW;

	GPIO_Init(&LED);
}

void TIM_Setup(void){

	htim_Tim.pTIMx = TIM6;
	htim_Tim.TIM_TimeBase.TIM_Period = 63999;
	htim_Tim.TIM_TimeBase.TIM_Prescaler= 24;

	TIM_TimeBaseInit(&htim_Tim);
}



int main(void)
{
	GPIO_LED_Init();
	TIM_Setup();

	TIM_Cmd(htim_Tim.pTIMx, ENABLE);

	while(1){
		if(TIM6->SR & TIM_UIF_FLAG){
			TIM6->SR &= ~TIM_UIF_FLAG;
			GPIO_TogglePin(LED.pGPIOx, GPIO_PIN_5);
		}
	}

	//while(1){
		//GPIO_TogglePin(LED.pGPIOx, GPIO_PIN_5);
		//delay(500000);
	//}
}

void UART4_IRQHandler(void)
{

}
