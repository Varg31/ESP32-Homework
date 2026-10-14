#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Examples.h"

// Uncomment the example you want to run (implementations live in src/examples/)
extern "C" void app_main() {
    // xTaskCreate(button_switch_task, "button_switch_task", 4096, nullptr, 5, nullptr);
    xTaskCreate(photo_resistor_task, "photo_resistor_task", 4096, nullptr, 5, nullptr);
    // xTaskCreate(servoRotateTask, "servoRotateTask", 4096, nullptr, 5, nullptr);
    // xTaskCreate(pwm_blinkTask, "pwm_blinkTask", 4096, nullptr, 5, nullptr);
}
