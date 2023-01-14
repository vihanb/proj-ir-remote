#pragma once

#include <Wifi.hpp>
#include <homekit.hpp>
#include <optional>

#define APP_NAME                "IR Remote"
#define ACCESSORY_SETUP_CODE    "123-45-678"
#define ACCESSORY_SETUP_ID      "ABCD"

class App final {
private:
    Wifi wifi_module;

    std::optional<HomeKit::Accessory> accessory;

public:
    App(): wifi_module(APP_NAME) {};
    ~App();

    void init();
    void start();
};