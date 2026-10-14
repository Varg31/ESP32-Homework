#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include <esp_log.h>

#include "PWMController.h"
#include "Examples.h"

#define PWM_TIMER LEDC_TIMER_0
#define PWM_CHANNEL LEDC_CHANNEL_0
#define PWM_FREQUENCY 500 // 5 kHz
#define PWM_RESOLUTION LEDC_TIMER_10_BIT

// resolution = 13 біт → max_duty = 8191
// freq = 50 Hz → period = 20000 мкс

uint32_t pulse_width_to_duty(float pulse_ms, uint32_t max_duty, float period_ms = 20.0f) {
    return (uint32_t)((pulse_ms / period_ms) * max_duty);
}

void servoRotateTask(void* arg) {

    ESP_LOGI("PWM", "Initializing PWM for servo control...");
    PWMController pwm(PWM_CHANNEL, PWM_TIMER, LEDC_LOW_SPEED_MODE, PWM_FREQUENCY, 0, PWM_RESOLUTION);
    pwm.configureChannel(GPIO_NUM_5); // Assuming GPIO 5 is connected to the servo

    ESP_LOGI("PWM", "Starting servo rotation task...");
    while (1) {
        ESP_LOGI("PWM", "Rotating servo...");
        for (int32_t duty = 0; duty <= 8192; duty += 10) { // Gradually increase duty cycle
            pwm.setDuty(duty); // нейтраль 90°
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
        ESP_LOGI("PWM", "Servo reached max position, rotating back...");
        for (int32_t duty = 8192; duty > 0; duty -= 10) { // Gradually decrease duty cycle
            pwm.setDuty(duty); // нейтраль 90°
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
        ESP_LOGI("PWM", "Servo rotation cycle complete, repeating...");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Wait for 1
    }
}
