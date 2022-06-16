#ifndef __CLOUD_SENSOR_H__
#define __CLOUD_SENSOR_H__

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "rom/ets_sys.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "DHT22.h"

void printSysInfo();
void DHT_task(void *pvParameter);

#endif