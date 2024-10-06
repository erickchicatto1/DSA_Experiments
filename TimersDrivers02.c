#include <stm32f446xx.h>
#include "stm32f446xx_gpio.h"
#include "stm32f446xx_tim.h"
#include "stm32f446xx_nvic.h"

//For the interrupt timer

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


	TIM_ITConfig(htim_Tim.pTIMx,TIM_IT_UI, ENABLE);
	TIM_Cmd(htim_Tim.pTIMx, ENABLE);
	//Primero habilitmos la interrupcion en el NVIC
	NVIC_IRQ_Enable(IRQ_TIM6_DAC);


}

//Despues utilizamos un manejador de interrupciones
void TIM6_DAC_IRQHandler(void){
	TIM_IRQHandler(&htim_Tim);
}
//Por ultimo utilizamos un callback
void TIM_EventCallback(TIM_Handle_t *pTimHandle,TIM_Event_t event){
	if(event == TIM_EVENT_UI){
		GPIO_TogglePin(LED.pGPIOx,GPIO_PIN_5);
	}
}



