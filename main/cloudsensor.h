#ifndef __CLOUD_SENSOR_H__
#define __CLOUD_SENSOR_H__

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp32/rom/ets_sys.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sys.h"


#include "DHT22.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define DEFAULT_AUTHMODE WIFI_AUTH_WPA2_PSK

void printSysInfo();
void DHT_task(void *pvParameter);

void start_wifi();

#endif