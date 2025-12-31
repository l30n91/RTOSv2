#include "Led.h"
#include "Usart.h"

/*Another way to initialize the constructor's parameters
  Led::Led(GPIO_TypeDef* port, uint16_t pin):
      port_(port), pin_(pin) //initialization
      {
      
      
      
      }
*/



extern Usart* usart2;

/*------------------ RTOS wrapper------------------------------------------------------------------------------------------------*/
void Led::BlinkLed_Task_Wrap(void* arg){ 
   Led* self = static_cast<Led*>(arg); /* all'interno del metodo static devo per forza passare il puntatore alla classe e castarmelo */
   self->BlinkLed_Task(2000);
  }
/*------------------ RTOS wrapper------------------------------------------------------------------------------------------------*/

/*------------------ RTOS task to be executed-------------------------------------------------------------------------------------*/


void Led::BlinkLed_Task(uint32_t periodMs/*,this*/){
  
  for (;;) {
            osSemaphoreAcquire(semWait_, osWaitForever); // aspetta il turno
            /* this->*/BlinkLed_Toggle();
            char string[] ="ciao";
            usart2->Usart_Write((uint8_t*)string);
            osDelay(periodMs);
            osSemaphoreRelease(semGive_);  //passa il turno a Task2 (intervento)
    }
  
  }
/*------------------ RTOS task to be executed-------------------------------------------------------------------------------------*/



void Led::BlinkLed_Toggle(void/*, this*/) {
   
   if (!Toggle_b_){
      port_->ODR|= pin_;
      Toggle_b_=true;
  }
  else{
     port_->ODR &= ~pin_;
     Toggle_b_=false;
  }
}


void Led::BlinkLed_CreateTask(void/*, this*/) {
    osThreadAttr_t attr = {0};
    attr.name = "LedBlink";
    attr.stack_size = 512;
    attr.priority = osPriorityNormal;
    osThreadNew(BlinkLed_Task_Wrap, this, &attr);
}

