#include <esp_adc/adc_cali_scheme.h>
#include "esp_log.h"

#include "ADCController.h"

int ADCController::readADC() {
    int raw = 0;
    int voltage = 0;

    ESP_ERROR_CHECK(adc_oneshot_read(adcHandle_, channel_, &raw));
    ESP_LOGI("ADCController", "Raw ADC Value: %d", raw);
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(caliHandle_, raw, &voltage));

    return voltage; // Return voltage in millivolts
}

void ADCController::init() {
    adc_oneshot_unit_init_cfg_t unitConfig = {
        .unit_id = unit_,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unitConfig, &adcHandle_));

    adc_oneshot_chan_cfg_t channelConfig = {
        .atten = atten_,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adcHandle_, channel_, &channelConfig));

    adc_cali_curve_fitting_config_t caliConfig = {
        .unit_id = unit_,
        .chan = channel_,
        .atten = atten_,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&caliConfig, &caliHandle_));
}
