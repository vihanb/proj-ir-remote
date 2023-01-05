#pragma once

#include <hap.h>
#include <vector>
#include <initializer_list>

#include "homekit_write_data.hpp"
#include "homekit_characteristic.hpp"

namespace HomeKit {

class Service {
private:
    static int readCallback(
        hap_char_t *hc,
        hap_status_t *status_code,
        void *serv_priv,
        void *read_priv
    );

    static int writeCallback(
        hap_write_data_t write_data[],
        int count,
        void *serv_priv,
        void *write_priv
    );
public:
    hap_serv_t *service;

    Service(hap_serv_t *service, std::initializer_list<hap_char_t *> chars);
    Service(Service&& service);
    virtual ~Service();

    Service() = delete;
    Service(const Service&) = delete;

    void addCharacteristic(hap_char_t *characteristic);
    Characteristic getCharacteristic(const char *UUID);

    virtual hap_status_t readCharacteristic(hap_char_t *characteristic);
    virtual void writeCharacteristic(std::vector<WriteData> &writeData);

    const char *UUID() const;
};

}