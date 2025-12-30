#include "Led.h"


static Led* led_5  = NULL;   // istanza globale della classe
static Led* led_6  = NULL;   // istanza globale della classe
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


}



