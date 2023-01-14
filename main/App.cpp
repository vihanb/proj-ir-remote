#include "App.hpp"

#include <nvs_flash.h>
#include <esp_log.h>
#include <hap_apple_servs.h>
#include <hap_apple_chars.h>
#include <qrcode.hpp>

#include "FanService.hpp"

using namespace qrcode;

static const char *TAG = APP_NAME ".app";

void App::init() {
    ESP_LOGI(TAG, "Starting " APP_NAME ".");

    // Setup the NVS (non-volatile storage).
    ESP_ERROR_CHECK(nvs_flash_init());

    wifi_module.init();

    hap_init(HAP_TRANSPORT_WIFI);

    // Create accessory object.
    accessory.emplace("My Fan", APP_NAME, "SERIALNO", "1.0", "1.0", HAP_CID_FAN);
    accessory->addService(new FanService {});

    hap_set_setup_code(ACCESSORY_SETUP_CODE);
    hap_set_setup_id(ACCESSORY_SETUP_ID);

    accessory->start();
}

App::~App() {
    hap_stop();
    hap_deinit();
}

void App::start() {
    wifi_module.start();
    hap_start();

    char *setup_payload = esp_hap_get_setup_payload(ACCESSORY_SETUP_CODE, ACCESSORY_SETUP_ID, false, HAP_CID_FAN);
    QrCode setup_qrcode = QrCode::encodeText(setup_payload, QrCode::Ecc::LOW);
    setup_qrcode.print();
}