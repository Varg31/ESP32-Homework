#include <esp_adc/adc_cali.h>
#include <esp_adc/adc_cali_scheme.h>
#include <esp_adc/adc_oneshot.h>
#include "esp_log.h"

#include "ADCController.h"

int ADCController::readADC() {
    int adc_raw = 0;
    int adc_voltage = 0;

    ESP_ERROR_CHECK(adc_oneshot_read(adc_handle_, channel_, &adc_raw));
    ESP_LOGI("ADCController", "Raw ADC Value: %d", adc_raw);
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(cali_handle_, adc_raw, &adc_voltage));

    return adc_voltage; // Return voltage in millivolts
}

void ADCController::init() {
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit_,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle_));

    adc_oneshot_chan_cfg_t config = {
        .atten = atten_,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle_, channel_, &config));

    adc_cali_curve_fitting_config_t cali_curve = {
        .unit_id = unit_,
        .chan = channel_,
        .atten = atten_,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&cali_curve, &cali_handle_));
}