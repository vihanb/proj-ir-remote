#include <esp_wifi.h>
#include <esp_check.h>

static const char *TAG = "Wifi.utils";

esp_err_t get_device_service_name(char *service_name, size_t max)
{
    uint8_t eth_mac[8];   
    esp_efuse_mac_get_default(eth_mac);
    snprintf(service_name, max, "%s%02X%02X%02X",
             "po", eth_mac[3], eth_mac[4], eth_mac[5]);
    return ESP_OK;
}

esp_err_t get_device_pop(char *pop, size_t max)
{
    if (!pop || !max) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t eth_mac[8];
    esp_efuse_mac_get_default(eth_mac);
    snprintf(pop, max, "%02x%02x%02x%02x", eth_mac[2], eth_mac[3], eth_mac[4], eth_mac[5]);
    return ESP_OK;
}