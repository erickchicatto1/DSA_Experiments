
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

uint8_t TIM_GetITStatus(TIM_RegDef_t *pTIMx,uint16_t TIM_IT){

	uint16_t IT_Status=0 , IT_Enable = 0;

	IT_Status = pTIMx->SR & TIM_IT; // Es una mascara de bits se hace solamente para que en el registro se le atine a los valores que nos interesa
	IT_Enable = pTIMx->DIER & TIM_IT;

	//Ahora revisamos el status, debido a que son pocos registros
	if( (IT_Status != (uint16_t)RESET) && (IT_Enable!=(uint16_t) RESET) ){
		return SET;
	}

	return RESET;
}


void TIM_ClearITPendingBit(TIM_RegDef_t *pTIMx,uint16_t TIM_IT){

	pTIMx->SR = (uint16_t)~TIM_IT;

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
		pTIMx->DIER |= IT_type;
	}
	else if(status==DISABLE){
		pTIMx->DIER &= ~IT_type;
	}

}


void TIM_IRQHandler(TIM_Handle_t *pTIMHandle){
	//To check the status
	if(TIM_GetITStatus(pTIMHandle->pTIMx, ITM_IT_UI)){
		TIM_ClearITPendingBit(pTIMHandle->pTIMx, ITM_IT_UI);
	}

}

__attribute__((weak))  void TIM_EventCallback(TIM_Handle_t *pTimHandle,TIM_Event_t event){

}













