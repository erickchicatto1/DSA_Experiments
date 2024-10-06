
#include "stm32f446xx_tim.h"


void TIM_ClkCtrl(TIM_RegDef_t *pTIMx, uint8_t status){

	if(status == ENABLE){
		if(pTIMx == TIM1){
			TIM1_EN_CLK();
		}
		else if(pTIMx == TIM2){
			TIM2_EN_CLK();
		}
	}
	else if(status == DISABLE){
		if(pTIMx == TIM1){
			TIM1_EN_CLK();
		}
		else if(pTIMx == TIM2){
			TIM2_EN_CLK();
		}
	}


}

void TIM_TimeBaseInit(TIM_Handle_t *pTimHandle){
//Habilitar el Clk
	TIM_ClkCtrl(pTimHandle->pTIMx , ENABLE);
	pTimHandle->pTIMx->ARR = pTimHandle->TIM_TimeBase.TIM_Period;
	pTimHandle->pTIMx->PSC = pTimHandle->TIM_TimeBase.TIM_Prescaler;
	pTimHandle->pTIMx->EGR=1;
}

void TIM_Cmd(TIM_RegDef_t *pTIMx, uint8_t status){

	if(status==ENABLE){
		pTIMx->CR1 |= (1<<TIM_CR1_CEN);
	}
	else if(status==DISABLE){
		pTIMx->CR1 &= ~(1<<TIM_CR1_CEN);
	}

}

void TIM_ITConfig(TIM_RegDef_t *pTIMx, uint16_t IT_type,uint8_t status ){

	if(status==ENABLE){
		pTIMx->DIER |= IT_Type;
	}
	else if(status==DISABLE){
		pTIMx->DIER &= ~IT_Type;
	}

}





