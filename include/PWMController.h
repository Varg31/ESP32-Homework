#pragma once

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"

class PWMController {
public:
    PWMController(ledc_channel_t channel, ledc_timer_t timer, ledc_mode_t mode, uint32_t freq, uint32_t duty, ledc_timer_bit_t resolution = LEDC_TIMER_10_BIT)
        : channel_(channel), timer_(timer), mode_(mode), freq_(freq), duty_(duty), resolution_(resolution) {
        initPWM();
    }

    void setDuty(uint32_t duty);

    void setFrequency(uint32_t freq) {
        freq_ = freq;
        ESP_ERROR_CHECK(ledc_set_freq(mode_, timer_, freq_));
    }

    void configureChannel(gpio_num_t gpioNum);

private:
    ledc_channel_t channel_;
    ledc_timer_t timer_;
    ledc_mode_t mode_;
    uint32_t freq_;
    uint32_t duty_;
    ledc_timer_bit_t resolution_;

    void initPWM();
};
