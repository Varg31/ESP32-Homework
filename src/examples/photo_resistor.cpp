#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_cali.h>
#include <esp_log.h>

#include "ADCController.h"
#include "GPIOHelpers.h"
#include "Examples.h"

#define TRANSISTOR_PIN GPIO_NUM_38
#define DARK_THRESHOLD 1500
#define LIGHT_THRESHOLD 1000

// #define ADC_PIN ADC_CHANNEL_5 // GPIO 33 on ESP320

void photo_resistor_task(void* arg) {
    ADCController adc(ADC_UNIT_1, ADC_CHANNEL_6, ADC_ATTEN_DB_12);
    set_pin_mode(TRANSISTOR_PIN);

    while (1) {
        int voltage = adc.readADC();
        if (voltage < DARK_THRESHOLD)
            led_set_state(TRANSISTOR_PIN, 1);
        else if (voltage > LIGHT_THRESHOLD)
            led_set_state(TRANSISTOR_PIN, 0);

        ESP_LOGI("ADC", "Photoresistor voltage: %d mV", voltage);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
