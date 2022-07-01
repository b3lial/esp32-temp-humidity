#ifndef __CLOUD_SENSOR_H__
#define __CLOUD_SENSOR_H__

#include <stdio.h>
#include <string.h>
#include <sys/param.h>

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
#include "esp_http_client.h"
#include "esp_tls.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "mdns.h"
#include "esp_http_server.h"
#include "cJSON.h"

#include "DHT22.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

void printSysInfo();
void DHT_task(void *pvParameter);

void start_wifi();
void start_mdns();

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);

void influx_task(void* pvParameter);
void http_influx_write(void);
esp_err_t _http_event_handler(esp_http_client_event_t *evt);

#endif