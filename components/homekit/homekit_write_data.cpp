#include "homekit_write_data.hpp"

namespace HomeKit {

WriteData::WriteData(hap_write_data_t *writeData)
    : writeData(writeData) {}

Characteristic WriteData::characteristic() const {
    return Characteristic(writeData->hc);
}

void WriteData::status(hap_status_t hapStatus) {
    *(writeData->status) = hapStatus;
}

hap_status_t WriteData::status() const {
    return *(writeData->status);
}

Value WriteData::value() const {
    return Value(writeData->val, characteristic().format());
}

}