
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "rtx_os.h"
#include "rtx_lib.h"
#include "stm32f4xx.h"                  // Device header
#include "cmsis_os2.h"

extern void SystemCoreClockConfigure(void);
extern void  USART2_init(void);

static void TaskBlink(void *arg);
static void TaskUART(void *arg);

static const osThreadAttr_t blinkAttr = {
  .name = "Blink",
  .stack_size = 512,         // bytes (aumenta se usi printf ecc.)
  .priority = osPriorityNormal
};

static const osThreadAttr_t uartAttr = {
  .name = "UART",
  .stack_size = 768,
  .priority = osPriorityBelowNormal
};


static void TaskBlink(void *arg)
{
  (void)arg;
  for (;;)
  {
    //HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    osDelay(500);             // 500 ms (usa il tick di RTOS)
  }
}

void delayMs(int n){
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 2000; i++) ;
}
void LED_blink(int value) {
    value %= 16;                    /* cap the max count at 15 */

    for (; value > 0; value--) {
        GPIOA->BSRR = 0x00000020;   /* turn on LED */
        delayMs(200);
        GPIOA->BSRR  = 0x00200000;   /* turn off LED */
        delayMs(200);
    }
    delayMs(800);
}




int osKernelConfigStatus;
int main (void)
{
  
  RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
    GPIOA->MODER &= ~0x00000C00;    /* clear pin mode */
    GPIOA->MODER |=  0x00000400;    /* set pin to output mode */

    USART2_init();                  /* initialize USART2 */
    
    
     uint8_t c='c';
     char string_[]= "anna ";
     uint8_t* p_string=(uint8_t*)string_;
     
     while(*p_string !=' ')
     {
       while(!(USART2->SR & USART_SR_TXE)); /* wait until TX is enabled*/
       
       USART2->DR= *p_string;
       
       p_string ++;       
     }
  
  
  
  uint32_t button_msk = (1U << Buttons_GetCount()) - 1;
  //kernel init
  osKernelInitialize();
  //SystemCoreClockConfigure();                              /* configure System Clock */
  
}