#include "Usart.h"
#include "stm32f4xx.h"




void Usart:: Usart_Write(uint8_t* p_string){
  while(*p_string !='\0')
   {
     while(!(port_->SR & USART_SR_TXE)); /* wait until TX is enabled*/
     
     port_->DR= *p_string;
     
     p_string ++;       
   }
 
}


void Usart::Usart_Init(uint8_t rcc_usart_en){
    RCC-> APB1ENR |= rcc_usart_en/*rcc_usart_en = RCC_APB1ENR_USART2EN;*/;

    // UART: 8N1, no flow control
    port_->CR1 = 0;
    port_->CR2 = 0;
    port_->CR3 = 0;

    //Scegli il BRR giusto per il tuo PCLK1
     port_->BRR = 0x08B;  // 115200 @ PCLK1=16 MHz
    //USART2->BRR = 0x16D;     // 115200 @ PCLK1=42 MHz

    port_->CR1 |= USART_CR1_TE | USART_CR1_RE;  // << abilita TX e RX
    port_->CR1 |= USART_CR1_UE;                 // abilita USART
 
}
