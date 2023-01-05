#include "homekit_accessory.hpp"

#include <stdexcept>
#include <functional>
#include <esp_log.h>

using namespace std::placeholders;

static const char *TAG = "HomeKit.Accessory";

namespace HomeKit {

Accessory::Accessory(
    const std::string &name,
    const std::string &model,
    const std::string &serial,
    const std::string &fwRev,
    const std::string &hwRev,
    hap_cid_t cid
) {
    hap_acc_cfg_t config = {
        .name = const_cast<char *>(name.c_str()),
        .model = const_cast<char *>(model.c_str()),
        .manufacturer = const_cast<char *>("Vihan"),
        .serial_num = const_cast<char *>(serial.c_str()),
        .fw_rev = const_cast<char *>(fwRev.c_str()),
        .hw_rev = const_cast<char *>(hwRev.c_str()),
        .pv = const_cast<char *>("1.1"),
        .cid = cid,
        .identify_routine = &Accessory::identifyRoutine,
    };

    accessory = hap_acc_create(&config);
    if (accessory == nullptr) {
        throw std::runtime_error("Failed to create HomeKit accessory.");
    }
    
    debugIdentifier = name + " (serial: " + serial + ", cid: " + std::to_string(cid) + ")";
}

Accessory::~Accessory() {
    hap_acc_delete(accessory);
}

int Accessory::identifyRoutine(hap_acc_t *acc) {
    ESP_LOGI(TAG, "Identifying accessory.");
    return HAP_SUCCESS;
}

void Accessory::addService(Service *service) {
    hap_acc_add_serv(accessory, service->service);
    services.push_back(std::unique_ptr<Service>(service));
}

void Accessory::start() {
    hap_add_accessory(accessory);
}

}