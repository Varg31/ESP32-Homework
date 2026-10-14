#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "GPIOHelpers.h"
#include "Examples.h"

#define BLUE_PIN GPIO_NUM_41
#define RED_PIN GPIO_NUM_42
#define BUTTON_PIN GPIO_NUM_2
#define BOOT_BUTTON_PIN GPIO_NUM_0

enum class BlinkMode {
    Sync,
    Async
};

static volatile BlinkMode ledMode = BlinkMode::Sync;

static void IRAM_ATTR externalIsrHandler(void* arg) {
    ledMode = BlinkMode::Sync;
}

static void IRAM_ATTR internalIsrHandler(void* arg) {
    ledMode = BlinkMode::Async;
}

void buttonSwitchTask(void* arg) {
    setPinMode(BLUE_PIN);
    setPinMode(RED_PIN);

    setPinMode(BUTTON_PIN, GPIO_MODE_INPUT);
    setPinMode(BOOT_BUTTON_PIN, GPIO_MODE_INPUT);

    gpio_pulldown_en(BUTTON_PIN);
    gpio_pullup_dis(BUTTON_PIN);

    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);
    gpio_set_intr_type(BOOT_BUTTON_PIN, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, externalIsrHandler, nullptr);
    gpio_isr_handler_add(BOOT_BUTTON_PIN, internalIsrHandler, nullptr);

    gpio_intr_enable(BUTTON_PIN);
    gpio_intr_enable(BOOT_BUTTON_PIN);

    while (1) {
        if (ledMode == BlinkMode::Sync) {
            ESP_LOGI("ISR", "External button pressed, switching to Sync mode");
            setLedState(BLUE_PIN, 1);
            setLedState(RED_PIN, 1);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            setLedState(BLUE_PIN, 0);
            setLedState(RED_PIN, 0);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        } else {
            ESP_LOGI("ISR", "Internal button pressed, switching to Async mode");
            setLedState(BLUE_PIN, 1);
            setLedState(RED_PIN, 0);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            setLedState(BLUE_PIN, 0);
            setLedState(RED_PIN, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}
