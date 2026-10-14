    

class ADCController {
public:
    ADCController(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten) 
        : unit_(unit), channel_(channel), atten_(atten), adc_handle_(nullptr), cali_handle_(nullptr) {
        init();
    }

    int readADC();

private:
    adc_unit_t unit_;
    adc_channel_t channel_;
    adc_atten_t atten_;
    adc_oneshot_unit_handle_t adc_handle_;
    adc_cali_handle_t cali_handle_;

    void init();
};