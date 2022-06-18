#include "cloudsensor.h"

static const char *TAG = "rest handler";

/* Our URI handler function to be called during GET /uri request */
esp_err_t get_handler(httpd_req_t *req)
{
    // convert sensor values to strings
    char temp[256];
    char humidity[256];
    sprintf(temp, "%.1f", getTemperature());
    sprintf(humidity, "%.1f", getHumidity());
    ESP_LOGI(TAG, "reading temp: %s", temp);
    ESP_LOGI(TAG, "reading humidty: %s", humidity);

    // create rest reply
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "temperature", temp);
    cJSON_AddStringToObject(root, "humidity", humidity);
    const char *sensor_data = cJSON_Print(root);

    // send to clieant and clean up
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, sensor_data, HTTPD_RESP_USE_STRLEN);
    free((void *)sensor_data);
    cJSON_Delete(root);
    return ESP_OK;
}

/* URI handler structure for GET /uri */
httpd_uri_t uri_get = {
    .uri      = "/data",
    .method   = HTTP_GET,
    .handler  = get_handler,
    .user_ctx = NULL
};

/* Function for starting the webserver */
httpd_handle_t start_webserver(void)
{
    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK) {
        /* Register URI handlers */
        httpd_register_uri_handler(server, &uri_get);
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

/* Function for stopping the webserver */
void stop_webserver(httpd_handle_t server)
{
    if (server) {
        /* Stop the httpd server */
        httpd_stop(server);
    }
}