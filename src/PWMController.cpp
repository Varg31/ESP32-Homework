#include "PWMController.h"

void PWMController::initPWM() {
    ledc_timer_config_t timerConfig = {
        .speed_mode      = mode_,
        .duty_resolution = resolution_,
        .timer_num       = timer_,
        .freq_hz         = freq_,
        .clk_cfg         = LEDC_AUTO_CLK,
        .deconfigure     = false,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timerConfig));
}

void PWMController::setDuty(uint32_t duty) {
    duty_ = duty;
    ESP_ERROR_CHECK(ledc_set_duty(mode_, channel_, duty_));
    ESP_ERROR_CHECK(ledc_update_duty(mode_, channel_));
}

void PWMController::configureChannel(gpio_num_t gpioNum) {
    ledc_channel_config_t channelConfig = {
        .gpio_num    = gpioNum,
        .speed_mode  = mode_,
        .channel     = channel_,
        .intr_type   = LEDC_INTR_DISABLE,
        .timer_sel   = timer_,
        .duty        = duty_,
        .hpoint      = 0,
        .sleep_mode  = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD, // замість ALLOW_PD
        .flags       = {0},
        .deconfigure = false,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channelConfig));
}
