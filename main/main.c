#include "cloudsensor.h"

void app_main()
{
	nvs_flash_init();

    start_wifi();
    start_mdns();
    start_webserver();

	vTaskDelay( 1000 / portTICK_RATE_MS );
	xTaskCreate( &DHT_task, "DHT_task", 2048, NULL, 5, NULL );
}

// DHT22 sensor reading test
// Jun 2007: Ricardo Timmermann, implemetation
void DHT_task(void *pvParameter)
{
	setDHTgpio( 4 );
	while(1) {
		int ret = readDHT();
		errorHandler(ret);
		
		// -- wait at least 2 sec before reading again ------------
		// The interval of whole process must be beyond 2 seconds !! 
		vTaskDelay( 3000 / portTICK_RATE_MS );
	}
}