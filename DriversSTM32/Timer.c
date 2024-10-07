#include "stm32F4xx.h"


void USART2_init(void);
void USART2_write(int ch);


int main(void){
    USART2_init();

    while(1){
        USART_write('Y');
        USART_write('e');
        USART_write('s');

        delayMS(10);
    }


}

void USART2_write(int ch){
    while (!(USART2->SR & 0x0080)) {} // wait until Tx buffer empty
    USART2->DR = (ch & 0xFF);
}


void USART2_init (void) {
RCC->AHB1ENR |= 1; /* Enable GPIOA clock */
RCC->APB1ENR |= 0x20000; /* Enable USART2 clock */
/* Configure PA2 for USART2_TX */
GPIOA->AFR[0] &= ~0x0F00;
GPIOA->AFR[0] |= 0x0700; /* alt7 for USART2 */
GPIOA->MODER &= ~0x0030;
GPIOA->MODER |= 0x0020; /* enable alternate function for PA2 */
USART2->BRR = 0x0683; /* 9600 baud @ 16 MHz */
USART2->CR1 = 0x0008;/* enable Tx, 8-bit data */ 
USART2->CR2 = 0x0000; /* 1 stop bit */
USART2->CR3 = 0x0000; /* no flow control */ 
USART2->CR1 |= 0x2000;
/* enable USART2 */
}