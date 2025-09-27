
#include "stm32f4xx.h"

#define BAUDRATE_115200     0x008B
#define BAUDRATE_9600       0x0683




void USART2_init(void) {
    // Clock GPIOA e USART2
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    // PA2 = TX (AF7), PA3 = RX (AF7)
    GPIOA->MODER &= ~((3U<<(2*2)) | (3U<<(2*3)));   // clear PA2, PA3
    GPIOA->MODER |=  ((2U<<(2*2)) | (2U<<(2*3)));   // Alternate Function
    GPIOA->AFR[0] &= ~((0xFU<<(4*2)) | (0xFU<<(4*3)));
    GPIOA->AFR[0] |=  ((7U  <<(4*2)) | (7U  <<(4*3))); // AF7

    // UART: 8N1, no flow control
    USART2->CR1 = 0;
    USART2->CR2 = 0;
    USART2->CR3 = 0;

    // Scegli il BRR giusto per il tuo PCLK1
     USART2->BRR = 0x08B;  // 115200 @ PCLK1=16 MHz
    //USART2->BRR = 0x16D;     // 115200 @ PCLK1=42 MHz

    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;  // << abilita TX e RX
    USART2->CR1 |= USART_CR1_UE;                 // abilita USART
}

void USART2_Write(uint8_t* p_string){

   while(*p_string !='\0')
   {
     while(!(USART2->SR & USART_SR_TXE)); /* wait until TX is enabled*/
     
     USART2->DR= *p_string;
     
     p_string ++;       
   }
}