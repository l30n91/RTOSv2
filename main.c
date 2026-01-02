
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "rtx_os.h"
#include "rtx_lib.h"
#include "stm32f4xx.h"                  // Device header
#include "cmsis_os2.h"

#ifdef __cplusplus
extern "C" {
#endif

 void Led_Init(void);
 void Led_createBlinkTask();
 void Usart_Init(USART_TypeDef*, uint32_t);

#ifdef __cplusplus
}
#endif

int main (void)
{
  RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
  GPIOA->MODER &= ~0x00000C00;    /* clear pin mode */
  GPIOA->MODER |=  0x00000400;    /* set pin to output mode */
  GPIOA->MODER |=  (1U << (6 * 2));  // set PA6 come output
  GPIOA->MODER |=  (1U << (7 * 2));  // set PA7 come output
  GPIOA->MODER |=  (1U << (5 * 2));  // set PA5 come output
  //kernel init
  osKernelInitialize();
  Usart_Init(USART2, RCC_APB1ENR_USART2EN);
  Led_Init();
  Led_createBlinkTask();
  osKernelStart(); 
  for(;;) {}
}