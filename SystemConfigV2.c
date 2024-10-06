/*
 * stm32f446xx_systemConfig.c
 *
 *  Created on: Aug 26, 2024
 *      Author: robo1
 */
#include "stm32f446xx_systemConfig.h"
#include "stm32f446xx.h"

//Macro to enable the clk

void MemModeSetting(Mem_Mode_t settings){

	//Need to enable the clk

	//For the 3 firsts bits
	if(settings == MainFlashMemory){
		SYSCFG2->SYSCFG_MEMRMP |= (1<<MEM_MODE_0);
	}

	else if(settings == SystemFlashMemoryMapped){
		SYSCFG2->SYSCFG_MEMRMP |= (1<<MEM_MODE_1);
	}

	else if(settings == FMCBank1){
		SYSCFG2->SYSCFG_MEMRMP |= (1<<MEM_MODE_2);
	}

	else if(settings == EmbeddedSRam){
		SYSCFG2->SYSCFG_MEMRMP |= (1<<MEM_MODE_0) | (1<<MEM_MODE_1);
	}

}



//Generic functions to help
void SetAbit(int *byte,int position){
	*byte |= (1<<position);
}


void ClearAbit(int *byte,int position){
	*byte &=~(1<<position);
}


void ToggleBit(int *byte,int position){
	*byte ^=(1<<position);
}


void WriteAByte(int *address , int value){
	*address = value;
}
