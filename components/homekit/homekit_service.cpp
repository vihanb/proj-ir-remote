#include "homekit_service.hpp"

#include <stdexcept>
#include <string>
#include <utility>
#include <esp_log.h>

static const char *TAG = "HomeKit.Service";

namespace HomeKit {

Service::Service(
    hap_serv_t *service,
    std::initializer_list<hap_char_t *> chars
) : service(service) {
    for (hap_char_t *characteristic : chars) {
        try {
            addCharacteristic(characteristic);
        } catch(const std::exception&) {
            hap_serv_delete(service);
            throw;
        }
    }

    hap_serv_set_priv(service, this);
    hap_serv_set_read_cb(service, &Service::readCallback);
    hap_serv_set_write_cb(service, &Service::writeCallback);

    ESP_LOGI(TAG, "Service created (uuid: %s).", hap_serv_get_type_uuid(service));
}

Service::Service(Service&& otherService)
    : service(std::exchange(otherService.service, nullptr)) {
    hap_serv_set_priv(service, this);
}

Service::~Service() {
    if (!service) return;
    
    hap_serv_set_read_cb(service, NULL);
    hap_serv_set_write_cb(service, NULL);

    ESP_LOGI(TAG, "Service deleted (uuid: %s).", hap_serv_get_type_uuid(service));
}

hap_status_t Service::readCharacteristic(hap_char_t *characteristic) {
    ESP_LOGD(TAG, "No service read callback provided.");
    return HAP_STATUS_SUCCESS; 
}

void Service::writeCharacteristic(std::vector<WriteData> &writeData) {
    ESP_LOGD(TAG, "No service write callback provided.");
}

Characteristic Service::getCharacteristic(const char *UUID) {
    return Characteristic(hap_serv_get_char_by_uuid(service, UUID));
}

void Service::addCharacteristic(hap_char_t *characteristic) {
    int err = hap_serv_add_char(service, characteristic);
    const char *uuid = hap_char_get_type_uuid(characteristic);

    if (err) {
        hap_char_delete(characteristic);
        throw std::runtime_error("Failed to add characteristic (uuid: " + std::string(uuid) + ").");
    }
}


// Static Delegators
int Service::readCallback(
    hap_char_t *hc,
    hap_status_t *status_code,
    void *serv_priv,
    void *read_priv
) {
    Service *base = static_cast<Service *>(serv_priv);
    *status_code = base->readCharacteristic(hc);
    return HAP_SUCCESS;
}

int Service::writeCallback(
    hap_write_data_t write_data[],
    int count,
    void *serv_priv,
    void *write_priv
) {
    Service *base = static_cast<Service *>(serv_priv);
    std::vector<WriteData> writeData;

    for (int i = 0; i < count; i++) {
        writeData.push_back(WriteData(&write_data[i]));
    }

    base->writeCharacteristic(writeData);

    int ret = 0;
    for (const WriteData &wd : writeData) {
        if (wd.status() != HAP_STATUS_SUCCESS) {
            ret |= HAP_FAIL;
        }
    }

    return ret;
}

const char *Service::UUID() const {
    return hap_serv_get_type_uuid(service);
}

}