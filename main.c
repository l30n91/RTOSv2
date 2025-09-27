
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "rtx_os.h"
#include "rtx_lib.h"
#include "stm32f4xx.h"                  // Device header
#include "cmsis_os2.h"


extern void SystemCoreClockConfigure(void);
extern void USART2_init(void);
extern void USART2_Write(uint8_t*);

#ifdef __cplusplus
extern "C" {
#endif

void Led_Init(void);
void Led_createBlinkTask(uint32_t periodMs);

#ifdef __cplusplus
}
#endif


//static osSemaphoreId_t sem1; // turno Task1
//static osSemaphoreId_t sem2; // turno Task2
//static osSemaphoreId_t sem3; // turno Task2












int main (void)
{
  
  RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
  GPIOA->MODER &= ~0x00000C00;    /* clear pin mode */
  GPIOA->MODER |=  0x00000400;    /* set pin to output mode */
  GPIOA->MODER |=  (1U << (6 * 2));  // set PA6 come output
  GPIOA->MODER |=  (1U << (7 * 2));  // set PA6 come output
  USART2_init();                  /* initialize USART2 */
  
  //kernel init
  osKernelInitialize();
  
  Led_Init();
  Led_createBlinkTask(2000);
  
  
  //sem1 = osSemaphoreNew(1, 1, NULL);
  //sem2 = osSemaphoreNew(1, 0, NULL);
  //sem3 = osSemaphoreNew(1, 0, NULL);


  osKernelStart(); 
  for(;;) {}
}