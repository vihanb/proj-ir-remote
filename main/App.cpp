#include "App.hpp"

#include <nvs_flash.h>
#include <esp_log.h>
#include <hap_apple_servs.h>
#include <hap_apple_chars.h>

#include <qrcode.hpp>

using namespace qrcode;

static const char *TAG = APP_NAME ".app";

int App::identifyRoutine(hap_acc_t *acc) {
    ESP_LOGI(TAG, "Identify routine called.");
    return HAP_SUCCESS;
}

void App::init() {
    ESP_ERROR_CHECK(nvs_flash_init());
    
    ESP_ERROR_CHECK(nvs_flash_erase());

    // Setup the NVS (non-volatile storage).
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_module.init();

    hap_init(HAP_TRANSPORT_WIFI);

    // Create accessory object.
    hap_acc_cfg_t cfg = {
        .name = ACCESSORY_NAME,
        .model = APP_NAME,
        .manufacturer = "Vihan",
        .serial_num = "abcdefg",
        .fw_rev = "1.0",
        .hw_rev = "1.0",
        .pv = "1.1",
        .cid = HAP_CID_FAN,
        .identify_routine = App::identifyRoutine,
    };

    accessory = hap_acc_create(&cfg);
    
    // Create service object.
    service = hap_serv_fan_create(false);

    // Warning: omitting creation of Wi-Fi Transit Service
    // as this is not MFi compliant.

    // Add optional characteristics to service.
    int ret = hap_serv_add_char(service, hap_char_name_create(ACCESSORY_NAME));
    ret |= hap_serv_add_char(service, hap_char_rotation_direction_create(HAP_FAN_ROTATION_DIRECTION_CLOCKWISE));
    ret |= hap_serv_add_char(service, hap_char_rotation_speed_create(0));

    hap_set_setup_code(ACCESSORY_SETUP_CODE);
    hap_set_setup_id(ACCESSORY_SETUP_ID);

    // TODO: Initialize factory reset button.

    hap_acc_add_serv(accessory, service);
    hap_add_accessory(accessory);
}

void App::start() {
    wifi_module.start();
    hap_start();

    char *setup_payload = esp_hap_get_setup_payload(ACCESSORY_SETUP_CODE, ACCESSORY_SETUP_ID, false, HAP_CID_FAN);
    QrCode setup_qrcode = QrCode::encodeText(setup_payload, QrCode::Ecc::LOW);
    setup_qrcode.print();
}