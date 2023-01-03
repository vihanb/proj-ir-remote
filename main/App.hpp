#pragma once
#include <Wifi.hpp>

#include <hap.h>

#define APP_NAME                "IR Remote"
#define ACCESSORY_NAME          "My Fan"
#define ACCESSORY_SETUP_CODE    "123-45-678"
#define ACCESSORY_SETUP_ID      "APPL"

#define HAP_FAN_ROTATION_DIRECTION_CLOCKWISE        0
#define HAP_FAN_ROTATION_DIRECTION_COUNTERCLOCKWISE 1

class App final {
private:
    Wifi wifi_module;

    hap_serv_t *service;
    hap_acc_t *accessory;

    static int identifyRoutine(hap_acc_t *acc);

public:
    App(): wifi_module(APP_NAME) {};

    void init();
    void start();
};