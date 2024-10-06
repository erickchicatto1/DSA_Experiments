/*
 * stm32f446xx_systemConfig.c
 *
 *  Created on: Aug 26, 2024
 *      Author: robo1
 */
#include "stm32f446xx_systemConfig.h"


void MemModeSetting(Mem_Mode_t settings){


	//*((volatile uint32_t *)0x40013800) = 0x01;
	//*((volatile uint32_t *)0x40013800) = 0x02;
	//*((volatile uint32_t *)0x40013800) = 0x03;
	//*((volatile uint32_t *)0x40013800) = 0x04;

	if(settings==MainFlashMemory){
		//SYSCFG |= 0x00;
		SYSCFG  |= 0x00;
		//SYSCFG |= (1<<pin);
	}

	else if(settings==SystemFlashMemoryMapped){
		//SYSCFG |= (1<<0);
		//SYSCFG |= (1<<pin);
		SYSCFG  |= 0x01;
	}

	else if(settings==FMCBank1){
			//SYSCFG |= (1<<1);
			//SYSCFG |= (1<<pin);
		SYSCFG  |= 0x02;
	 }
	else if(settings==EmbeddedSRam){
		//SYSCFG |= (1<<3);//000->100
		//SYSCFG |= (1<<pin);
		SYSCFG  |= 0x03; //0011
	 }
	else if(settings==FMC_SDRAM){
		//SYSCFG |= (1<<3);
		//SYSCFG |= (1<<pin);
			SYSCFG  |= 0x04;
		 }

}



