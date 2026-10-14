#pragma once

#include <esp_adc/adc_oneshot.h>
#include <esp_adc/adc_cali.h>

class ADCController {
public:
    ADCController(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten)
        : unit_(unit), channel_(channel), atten_(atten), adcHandle_(nullptr), caliHandle_(nullptr) {
        init();
    }

    int readADC();

private:
    adc_unit_t unit_;
    adc_channel_t channel_;
    adc_atten_t atten_;
    adc_oneshot_unit_handle_t adcHandle_;
    adc_cali_handle_t caliHandle_;

    void init();
};
