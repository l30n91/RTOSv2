#ifndef LED_HPP
#define LED_HPP

#include "stm32f4xx.h"   // o quello della tua MCU
#include "cmsis_os2.h"   // RTOS API

class Led {
public:
    Led(GPIO_TypeDef* port, uint16_t pin);

    void on();
    void off();
    void toggle();

    // Avvia un thread che fa blinking (periodo in ms)
    void startBlinkTask(uint32_t periodMs);

private:
    static void blinkThread(void* arg);  // trampolino statico
    void runBlink(uint32_t periodMs);    // corpo del task

    GPIO_TypeDef* port_;
    uint16_t pin_;
};

#endif // LED_HPP
