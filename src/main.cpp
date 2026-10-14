#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Examples.h"

// Uncomment the example you want to run (implementations live in src/examples/)
extern "C" void app_main() {
    // xTaskCreate(buttonSwitchTask, "buttonSwitchTask", 4096, nullptr, 5, nullptr);
    xTaskCreate(photoResistorTask, "photoResistorTask", 4096, nullptr, 5, nullptr);
    // xTaskCreate(servoRotateTask, "servoRotateTask", 4096, nullptr, 5, nullptr);
    // xTaskCreate(pwmBlinkTask, "pwmBlinkTask", 4096, nullptr, 5, nullptr);
}
