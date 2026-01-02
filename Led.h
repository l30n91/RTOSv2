#ifndef LED_HPP 
#define LED_HPP

#include "stm32f4xx.h"  
#include "cmsis_os2.h"   // RTOS API



class Led {
  public: Led(GPIO_TypeDef* port, uint16_t pin, osSemaphoreId_t semWait,osSemaphoreId_t semGive, bool led):port_(port), pin_(pin),semWait_(semWait),semGive_(semGive),led_(led){} //parameters initialization :port_(port), pin_(pin){};
    void BlinkLed_Task(uint32_t period);
    void BlinkLed_Toggle(void);
    void BlinkLed_CreateTask(void);
    void BlinkLed_UsartWrite(uint8_t*);
    static void  BlinkLed_Task_Wrap(void*); /* questo metodo ha bisogno di essere dichiarato static void per via di RTOS, infatti 
    la task create di RTOS accetta solamente static void functions*/
    
  private:
     GPIO_TypeDef* port_; 
     uint16_t pin_;
     osSemaphoreId_t semWait_; 
     osSemaphoreId_t semGive_; 
     bool led_ = false;
     bool Toggle_b_ = false;
  
};







#endif // LED_HPP
