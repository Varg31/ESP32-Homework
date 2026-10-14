#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"


#include "driver/ledc.h"
#include "esp_err.h"

#include "PWMController.h"

void PWMController::initPWM() {
    ledc_timer_config_t timer_conf = {
        .speed_mode      = mode_,
        .duty_resolution = resolution_,
        .timer_num       = timer_,
        .freq_hz         = freq_,
        .clk_cfg         = LEDC_AUTO_CLK,
        .deconfigure     = false,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));
}

void PWMController::setDuty(uint32_t duty) {
    duty_ = duty;
    ESP_ERROR_CHECK(ledc_set_duty(mode_, channel_, duty_));
    ESP_ERROR_CHECK(ledc_update_duty(mode_, channel_));
}



void PWMController::configureChannel(gpio_num_t gpio_num) {
    // gpio_reset_pin(gpio_num);
    // gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT);
    ledc_channel_config_t chan_conf = {
        .gpio_num    = gpio_num,
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
    ESP_ERROR_CHECK(ledc_channel_config(&chan_conf));
}