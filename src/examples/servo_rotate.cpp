#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "PWMController.h"
#include "Examples.h"

#define SERVO_PIN GPIO_NUM_5

#define PWM_TIMER LEDC_TIMER_0
#define PWM_CHANNEL LEDC_CHANNEL_0
#define PWM_FREQUENCY 500 // 500 Hz
#define PWM_RESOLUTION LEDC_TIMER_10_BIT

void servoRotateTask(void* arg) {
    ESP_LOGI("PWM", "Initializing PWM for servo control...");
    PWMController pwm(PWM_CHANNEL, PWM_TIMER, LEDC_LOW_SPEED_MODE, PWM_FREQUENCY, 0, PWM_RESOLUTION);
    pwm.configureChannel(SERVO_PIN);

    ESP_LOGI("PWM", "Starting servo rotation task...");
    while (1) {
        for (int32_t duty = 0; duty <= 8192; duty += 10) { // Gradually increase duty cycle
            pwm.setDuty(duty);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
        for (int32_t duty = 8192; duty > 0; duty -= 10) { // Gradually decrease duty cycle
            pwm.setDuty(duty);
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
        ESP_LOGI("PWM", "Servo rotation cycle complete, repeating...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
