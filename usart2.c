
#include "stm32f4xx.h"

#define BAUDRATE_115200     0x008B
#define BAUDRATE_9600       0x0683



/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
// *----------------------------------------------------------------------------*/
//void USART2_init (void) {
//    RCC->AHB1ENR |= 1;                         /* Enable GPIOA clock */
//    RCC->APB1ENR |= 0x00020000;               /* Enable USART2 clock */

//    /* Configure PA3 for USART2 RX */
//    GPIOA->AFR[0] &= ~0xF000;
//    GPIOA->AFR[0] |=  0x7000;              /* alt1 for USART2 */
//    GPIOA->MODER  &= ~0x00C0;
//    GPIOA->MODER  |=  0x0080;            /* enable alternate function for PA3 */

//    USART2->BRR =     BAUDRATE_115200; /* 115200 baud @ 16MHz */
//    USART2->CR1 =     0x0004;         /* enable Rx, 8-bit data */
//    USART2->CR2 =     0x0000;        /* 1 stop bit */
//    USART2->CR3 =     0x0000;       /* no flow control */
//    USART2->CR1 |=    0x2000;      /* enable USART2 */
//}




///* Write a character to USART2 */
//void USART2_write (int ch) {
//    while (!(USART2->SR & 0x0080)) {}   /* wait until Tx buffer empty*/
//    USART2->DR = (ch & 0xFF);
//}
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