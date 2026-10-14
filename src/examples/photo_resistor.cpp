#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_log.h>

#include "ADCController.h"
#include "GPIOHelpers.h"
#include "Examples.h"

#define TRANSISTOR_PIN GPIO_NUM_38
#define DARK_THRESHOLD 1500
#define LIGHT_THRESHOLD 1000

void photoResistorTask(void* arg) {
    ADCController adc(ADC_UNIT_1, ADC_CHANNEL_6, ADC_ATTEN_DB_12);
    setPinMode(TRANSISTOR_PIN);

    while (1) {
        int voltage = adc.readADC();
        if (voltage < DARK_THRESHOLD)
            setLedState(TRANSISTOR_PIN, 1);
        else if (voltage > LIGHT_THRESHOLD)
            setLedState(TRANSISTOR_PIN, 0);

        ESP_LOGI("ADC", "Photoresistor voltage: %d mV", voltage);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
