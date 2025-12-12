#include "Led.h"

/*Another way to initialize the constructor's parameters
  Led::Led(GPIO_TypeDef* port, uint16_t pin):
      port_(port), pin_(pin) //initialization
      {
      
      
      
      }
*/





/*------------------ RTOS wrapper------------------------------------------------------------------------------------------------*/
void Led::BlinkLed_Task_Wrap(void* arg){ 
   Led* self = static_cast<Led*>(arg); /* all'interno del metodo static devo per forza passare il puntatore alla classe e castarmelo */
   self->BlinkLed_Task(2000);
  }
/*------------------ RTOS wrapper------------------------------------------------------------------------------------------------*/

/*------------------ RTOS task to be executed-------------------------------------------------------------------------------------*/

void Led::BlinkLed_Task(uint32_t periodMs /*,this*/){
  for (;;) {
        /* this->*/BlinkLed_Toggle();
        osDelay(periodMs);
    }
  
  }
/*------------------ RTOS task to be executed-------------------------------------------------------------------------------------*/



void Led::BlinkLed_Toggle(void/*, this*/) {
   static bool Toggle_b = false;
   if (!Toggle_b){
      port_->ODR|= pin_;
      Toggle_b=true;
  }
  else{
     port_->ODR &= ~pin_;
     Toggle_b=false;
  }
}


void Led::BlinkLed_CreateTask(void/*, this*/) {
    osThreadAttr_t attr = {0};
    attr.name = "LedBlink";
    attr.stack_size = 512;
    attr.priority = osPriorityNormal;
    osThreadNew(BlinkLed_Task_Wrap, this, &attr);
}

