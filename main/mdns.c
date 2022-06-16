#include "cloudsensor.h"

static const char *TAG = "mdns handler";

void start_mdns() {
    ESP_LOGI(TAG, "mdns hostname: %s", CONFIG_CLOUDSENSOR_MDNS_HOSTNAME);

    // init mdns
    ESP_ERROR_CHECK(mdns_init());
    ESP_ERROR_CHECK(mdns_hostname_set(CONFIG_CLOUDSENSOR_MDNS_HOSTNAME));
    ESP_ERROR_CHECK(mdns_instance_name_set("esp32 based temperatur/humidity sensor"));

    // txt record
    mdns_txt_item_t serviceDeviceInfoData[3] = {
        {"board", "esp32"},
        {"version", "1.0.0"}};

    // start service
    ESP_ERROR_CHECK(mdns_service_add("cloudsensor-webserver",
                                     "_http", "_tcp", 80, serviceDeviceInfoData, 2));
}