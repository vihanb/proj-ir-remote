#include "homekit_value.hpp"
#include <esp_log.h>

static const char *TAG = "HomeKit.Value";

namespace HomeKit {

Value::Value(const hap_val_t value, hap_char_format_t format)
    : value(value), knownFormat(format)
    {}

Value::Value(bool val)
    : Value(hap_val_t { .i = val }, HAP_CHAR_FORMAT_BOOL) {}

Value::Value(uint8_t val)
    : Value(hap_val_t { .i = val }, HAP_CHAR_FORMAT_UINT8) {}

Value::Value(uint32_t val)
    : Value(hap_val_t { .u = val }, HAP_CHAR_FORMAT_UINT32) {}

Value::Value(uint64_t val)
    : Value(hap_val_t { .i64 = val }, HAP_CHAR_FORMAT_UINT64) {}

Value::Value(float val)
    : Value(hap_val_t { .f = val }, HAP_CHAR_FORMAT_FLOAT) {}

Value::Value(const std::string &val)
    : Value(hap_val_t { .s = const_cast<char *>(val.c_str()) }, HAP_CHAR_FORMAT_STRING) {}


constexpr const char *Value::formatToString(hap_char_format_t format) {
    switch (format) {
        case HAP_CHAR_FORMAT_NONE: return "None";
        case HAP_CHAR_FORMAT_BOOL: return "bool";
        case HAP_CHAR_FORMAT_UINT8: return "uint8_t";
        case HAP_CHAR_FORMAT_UINT16: return "uint16_t";
        case HAP_CHAR_FORMAT_UINT32: return "uint32_t";
        case HAP_CHAR_FORMAT_UINT64: return "uint64_t";
        case HAP_CHAR_FORMAT_INT: return "int";
        case HAP_CHAR_FORMAT_FLOAT: return "float";
        case HAP_CHAR_FORMAT_STRING: return "string";
        case HAP_CHAR_FORMAT_TLV8: return "tlv8";
        case HAP_CHAR_FORMAT_DATA: return "[[data]]";
        default: return "[[unknown]]";
    }
}

void Value::validateAs(hap_char_format_t format) const {
    if (knownFormat != HAP_CHAR_FORMAT_NONE && knownFormat != format) {
        ESP_LOGW(TAG, "Using char of type %s with type %s.", formatToString(knownFormat), formatToString(format));
    }
}

Value::operator bool() const {
    validateAs(HAP_CHAR_FORMAT_BOOL);
    return value.b;
}

Value::operator float() const {
    validateAs(HAP_CHAR_FORMAT_FLOAT);
    return value.f;
}

Value::operator int() const {
    validateAs(HAP_CHAR_FORMAT_INT);
    return value.i;
}

Value::operator uint8_t() const {
    validateAs(HAP_CHAR_FORMAT_UINT8);
    return value.u;
}

Value::operator uint32_t() const {
    validateAs(HAP_CHAR_FORMAT_UINT32);
    return value.u;
}

Value::operator uint64_t() const {
    validateAs(HAP_CHAR_FORMAT_UINT64);
    return value.i64;
}

Value::operator std::string() const {
    validateAs(HAP_CHAR_FORMAT_STRING);
    return std::string(value.s);
}

}