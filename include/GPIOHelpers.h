#pragma once

#include "driver/gpio.h"

inline void set_pin_mode(gpio_num_t pin, gpio_mode_t mode = GPIO_MODE_OUTPUT) {
    gpio_reset_pin(pin);
    gpio_set_direction(pin, mode);
}

inline void led_set_state(gpio_num_t pin, bool state) {
    gpio_set_level(pin, state);
}
