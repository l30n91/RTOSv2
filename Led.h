#ifndef LED_HPP 
#define LED_HPP

#include "stm32f4xx.h"  
#include "cmsis_os2.h"   // RTOS API



class Led {
  public: Led(GPIO_TypeDef* port, uint16_t pin):port_(port), pin_(pin){} //parameters initialization :port_(port), pin_(pin){};
    void BlinkLed_Task(uint32_t period);
    void BlinkLed_Toggle(void);
    void BlinkLed_CreateTask(void);
    static void  BlinkLed_Task_Wrap(void*); //this method needs to be STATIC because it is needed for RTOS
    
  private:
     GPIO_TypeDef* port_; 
     uint16_t pin_;
};







#endif // LED_HPP
