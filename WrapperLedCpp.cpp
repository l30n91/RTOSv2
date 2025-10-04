#include "Led.h"


static Led* led = NULL;   // istanza globale della classe


extern "C"{
void Led_Init(void) {
    if (!led) {
        led = new Led(GPIOA, GPIO_PIN_5);   // crea l’oggetto inizializando anche il costruttore della classe
    }
}


void Led_createBlinkTask(void) {
    if (led) {
        led->createBlinkTask();
    }
}

}