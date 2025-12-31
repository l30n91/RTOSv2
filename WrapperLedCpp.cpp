#include "Led.h"
#include "Usart.h"

static Led* led_5  = NULL;   // istanza globale della classe 
static Led* led_6  = NULL;   // istanza globale della classe
Usart* usart2 = NULL;
static osSemaphoreId_t sem1;
static osSemaphoreId_t sem2;


extern "C"{
void Led_Init(void) {
    if (!sem1 && !sem2) {
        sem1 = osSemaphoreNew(1, 0, nullptr);
        sem2 = osSemaphoreNew(1, 1, nullptr);
    }
  
 
    if (!led_5 && !led_6) {
        led_5 = new Led(GPIOA, GPIO_PIN_5,sem1, sem2); // crea l’oggetto inizializzando anche il costruttore della classe
        led_6 = new Led(GPIOA, GPIO_PIN_6,sem2, sem1); // crea l’oggetto inizializzando anche il costruttore della classe
    }
}


void Led_createBlinkTask(void) {
    if (led_5 && led_6) {
        led_5->BlinkLed_CreateTask();
        led_6->BlinkLed_CreateTask();
    }
}

/* usart address è per il costruttore della classe, usart rcc en è per la init dell'usart2 TRAMITE RCC*/
void Usart_Init(USART_TypeDef* usart_address, uint32_t rcc_usart_en) {
     if (!usart2){
        usart2 = new Usart(usart_address);
        usart2->Usart_Init(rcc_usart_en);
    }
  }

  void Usart_Write(uint8_t* p_string) {
        usart2->Usart_Write(p_string);
    }
  }





