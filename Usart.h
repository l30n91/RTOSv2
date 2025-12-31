#ifndef USART_HPP 
#define USART_HPP

#include "stm32f4xx.h"  
#include "cmsis_os2.h"   // RTOS API



class Usart {
  public: Usart(USART_TypeDef* port):port_(port){} //parameters initialization :port_(port), pin_(pin){};
    void Usart_Write(uint8_t*);
    void Usart_Init(uint32_t);
    //static void  Usart2_Write_Task_Wrap(void*); //this method needs to be STATIC because it is needed for RTOS
    
  private:
     USART_TypeDef* port_;
};







#endif // USART_HPP