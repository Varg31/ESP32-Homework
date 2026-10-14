#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <esp_log.h>

#include "GPIOHelpers.h"
#include "Examples.h"

#define BLUE_PIN GPIO_NUM_41
#define RED_PIN GPIO_NUM_42
#define BUTTON_PIN GPIO_NUM_2

enum class BlinkMode {
    Sync,
    Async
};

static volatile BlinkMode led_mode = BlinkMode::Sync;

static void IRAM_ATTR external_isr_handler(void* arg) {
    led_mode = BlinkMode::Sync;
}

static void IRAM_ATTR internal_isr_handler(void* arg) {
    led_mode = BlinkMode::Async;
}

void button_switch_task(void* arg) {
    set_pin_mode(BLUE_PIN);
    set_pin_mode(RED_PIN);

    set_pin_mode(BUTTON_PIN, GPIO_MODE_INPUT);
    set_pin_mode(GPIO_NUM_0, GPIO_MODE_INPUT);

    gpio_pulldown_en(BUTTON_PIN);
    gpio_pullup_dis(BUTTON_PIN);

    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);
    gpio_set_intr_type(GPIO_NUM_0, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, external_isr_handler, nullptr);
    gpio_isr_handler_add(GPIO_NUM_0, internal_isr_handler, nullptr);

    gpio_intr_enable(BUTTON_PIN);
    gpio_intr_enable(GPIO_NUM_0);

    while (1) {
        if (led_mode == BlinkMode::Sync) {
            ESP_LOGI("ISR", "External button pressed, switching to Sync mode");
            led_set_state(BLUE_PIN, 1);
            led_set_state(RED_PIN, 1);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            led_set_state(BLUE_PIN, 0);
            led_set_state(RED_PIN, 0);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        } else {
            ESP_LOGI("ISR", "Internal button pressed, switching to Async mode");
            led_set_state(BLUE_PIN, 1);
            led_set_state(RED_PIN, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            led_set_state(BLUE_PIN, 0);
            led_set_state(RED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}
