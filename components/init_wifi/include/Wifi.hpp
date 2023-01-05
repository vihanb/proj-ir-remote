#pragma once
#include <string>
#include <esp_event.h>
#include <freertos/event_groups.h>

class Wifi {
    std::string serviceName;
    uint32_t popSeed;
    EventGroupHandle_t wifi_event_group;

    static void eventHandler(
        void *data,
        esp_event_base_t event_base,
        int32_t event_id, void* event_data);

    void printQRCode();

public:
    explicit Wifi(const std::string &serviceName);
    ~Wifi();

    // Unique device name.
    std::string deviceName();

    // Secure random POP string.
    std::string pop();

    void init();
    void start();
};