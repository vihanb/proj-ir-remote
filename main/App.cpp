#include "App.hpp"

#include <nvs_flash.h>
#include <esp_log.h>
#include <hap_apple_servs.h>
#include <qrcode.hpp>
#include <iostream>

#include "FanService.hpp"
#include "TemperatureService.hpp"
#include "HumidityService.hpp"

using namespace qrcode;

static const char *TAG = APP_NAME ".app";

void App::init() {
    // Set up the NVS (non-volatile storage).
    ESP_ERROR_CHECK(nvs_flash_init());

    wifiModule.init();
    homekit.init();
//
//    // Create accessory object.
    auto *accessory = homekit.addAccessory("My Fan", APP_NAME, "SERIALNO", "1.0", "1.0", HAP_CID_SENSOR);
    accessory->addService<FanService>(GPIO_NUM_2);
    accessory->addService<TemperatureService>();
    accessory->addService<HumidityService>();
}

void App::start() {
    wifiModule.start();
    homekit.start();

    if (!homekit.isProbablyPaired()) {
        homekit.printQRCode();
    }
}