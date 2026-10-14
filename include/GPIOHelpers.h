#pragma once

#include "driver/gpio.h"

inline void setPinMode(gpio_num_t pin, gpio_mode_t mode = GPIO_MODE_OUTPUT) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, mode);
}

inline void setLedState(gpio_num_t pin, bool state) {
    gpio_set_level(pin, state);
}
