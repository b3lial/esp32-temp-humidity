#include "cloudsensor.h"

// push sensor data continously into influx db
void influx_task(void* pvParameter) {
    while (1) {
        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}