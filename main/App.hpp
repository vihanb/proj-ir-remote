#pragma once

#include <Wifi.hpp>
#include <homekit.hpp>
#include <optional>

#define APP_NAME                "IR Remote"
#define ACCESSORY_SETUP_CODE    "123-45-678"
#define ACCESSORY_SETUP_ID      "ABCD"

class App final {
private:
    WiFi wifiModule {APP_NAME };
    HomeKit::HomeKit homekit { ACCESSORY_SETUP_CODE, ACCESSORY_SETUP_ID };

public:
    void init();
    void start();
};