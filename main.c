
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
static osSemaphoreId_t sem1; // turno Task1
static osSemaphoreId_t sem2; // turno Task2
static osSemaphoreId_t sem3; // turno Task2


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


void LED_blink(void) {
   //GPIOA->ODR ^= (1U << 5);  // PA5 on
   GPIOA->ODR = (1U << 5);  // PA5 on
}

void LED_blink_6(void) {
   //GPIOA->ODR ^= (1U << 6);  // PA6 on
   GPIOA->ODR = (1U << 6);  // PA6 on
}


void LED_blink_7(void) {
   //GPIOA->ODR ^= (1U << 6);  // PA6 on
   GPIOA->ODR = (1U << 7);  // PA6 on
}


static void TaskBlink5(void *arg)
{
  (void)arg;
  for (;;)
  {
    osSemaphoreAcquire(sem1, osWaitForever); // aspetta il turno
    LED_blink();
    osDelay(2000);    // 500 ms (usa il tick di RTOS)
    osSemaphoreRelease(sem2);   // passa il turno a Task2 (intervento)
  }
} 

static void TaskBlink6(void *arg)
{
  (void)arg;
  for (;;)
  {
    osSemaphoreAcquire(sem2, osWaitForever); // aspetta il turno
    LED_blink_6();
    osDelay(2000); 
    osSemaphoreRelease(sem3);   // passa il turno a Task1 (intervento)    
  }
} 


static void TaskBlink7(void *arg)
{
  (void)arg;
  for (;;)
  {
    osSemaphoreAcquire(sem3, osWaitForever); // aspetta il turno
    LED_blink_7();
    osDelay(2000); 
    osSemaphoreRelease(sem1);   // passa il turno a Task1 (intervento)    
  }
} 


int osKernelConfigStatus;
int main (void)
{
  
    RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
    GPIOA->MODER &= ~0x00000C00;    /* clear pin mode */
    GPIOA->MODER |=  0x00000400;    /* set pin to output mode */
    GPIOA->MODER |=  (1U << (6 * 2));  // set PA6 come output
    GPIOA->MODER |=  (1U << (7 * 2));  // set PA6 come output
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
  
  
  //kernel init
  osKernelInitialize();
  sem1 = osSemaphoreNew(1, 1, NULL);
  sem2 = osSemaphoreNew(1, 0, NULL);
  sem3 = osSemaphoreNew(1, 0, NULL);
     
     
  osThreadNew(TaskBlink5, NULL, &blinkAttr);  // 2) crea i thread
  osThreadNew(TaskBlink6, NULL, &blinkAttr);  // 2) crea i thread
  osThreadNew(TaskBlink7, NULL, &blinkAttr);  // 2) crea i thread
  osKernelStart(); 
  for(;;) {}
}