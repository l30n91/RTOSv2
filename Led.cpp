#include "Led.h"

Led::Led(GPIO_TypeDef* port, uint16_t pin): port_(port), pin_(pin) {}

void Led::on() {
   port_->ODR = pin_;
}

void Led::off() {
    port_->BSRR = (uint32_t)pin_ << 16U;
}

void Led::toggle() {
    port_->ODR ^= pin_;
}



void Led::runBlink(uint32_t periodMs) {
    for (;;) {
        toggle();
        osDelay(periodMs);
    }
}

void Led::blinkThread(void* arg) {
    Led* self = static_cast<Led*>(arg);
    self->runBlink(2000);
}

void Led::createBlinkTask(void) {
    // crea un thread RTOS che chiama blinkThread con this
    osThreadAttr_t attr={0};
    attr.name = "LedBlink";
    attr.stack_size = 512;
    attr.priority = osPriorityNormal;
    osThreadNew(blinkThread, this, &attr);
}



