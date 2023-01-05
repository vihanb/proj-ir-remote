#include "homekit_characteristic.hpp"
#include <cstring>
#include <esp_log.h>

#include "homekit_value.hpp"

namespace HomeKit {

Characteristic::Characteristic(hap_char_t *hapChar)
    : hapChar(hapChar) {}

const char *Characteristic::typeUUID() const {
    return hap_char_get_type_uuid(hapChar);
}

bool Characteristic::isTypeUUID(const char *typeUUID) const {
    return std::strcmp(hap_char_get_type_uuid(hapChar), typeUUID) == 0;
}

hap_char_format_t Characteristic::format() const {
    return hap_char_get_format(hapChar);
}

void Characteristic::value(const Value &newValue) const {
    newValue.validateAs(hap_char_get_format(hapChar));
    hap_char_update_val(hapChar, const_cast<hap_val_t *>(&newValue.value));
}

Value Characteristic::value() const {
    return Value(*hap_char_get_val(hapChar), hap_char_get_format(hapChar));
}


}