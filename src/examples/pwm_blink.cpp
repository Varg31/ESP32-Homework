#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "PWMController.h"
#include "Examples.h"

#define BLUE_PIN GPIO_NUM_41

#define PWM_TIMER LEDC_TIMER_0
#define PWM_CHANNEL LEDC_CHANNEL_0
#define PWM_FREQUENCY 500 // 500 Hz
#define PWM_RESOLUTION LEDC_TIMER_10_BIT

void pwmBlinkTask(void* arg) {
    PWMController pwm(PWM_CHANNEL, PWM_TIMER, LEDC_LOW_SPEED_MODE, PWM_FREQUENCY, 512, PWM_RESOLUTION);
    pwm.configureChannel(BLUE_PIN);

    while (1) {
        ESP_LOGI("PWM", "Blinking LED with PWM...");
        pwm.setDuty(1023);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        pwm.setDuty(0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
