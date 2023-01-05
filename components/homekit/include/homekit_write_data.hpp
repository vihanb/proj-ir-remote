#pragma once
#include "homekit_characteristic.hpp"
#include "homekit_value.hpp"

namespace HomeKit {

class WriteData {
public:
    hap_write_data_t *writeData;
    
    WriteData() = delete;
    WriteData(hap_write_data_t *writeData);

    Characteristic characteristic() const;

    void status(hap_status_t hapStatus);
    hap_status_t status() const;

    Value value() const;
};

}