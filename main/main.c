#include "cloudsensor.h"

/*
 * Start dht22 sensor reader task which reads sensor values every three seconds
 * Afterwards, start wifi. When wifi connection was successful, continue
 * Finally run mdns for easy network discovery and rest webserver to read the
 * sensor data on demand.
 */
void app_main()
{
	nvs_flash_init();
	vTaskDelay( 500 / portTICK_RATE_MS );
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );
    vTaskDelay( 500 / portTICK_RATE_MS );

    start_wifi();
	xTaskCreate( &influx_task, "influx_task", 4096, NULL, 5, NULL );

    start_mdns();
    start_webserver();
}