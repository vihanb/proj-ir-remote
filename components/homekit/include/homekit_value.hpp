#pragma once
#include <hap.h>
#include <string>

#include "homekit_value.hpp"

namespace HomeKit {

class Value {
    static constexpr const char *formatToString(hap_char_format_t format);
public:

    const hap_val_t value;
    const hap_char_format_t knownFormat;
    
    void validateAs(hap_char_format_t expectedFormat) const;

    Value() = delete;
    Value(const hap_val_t value, hap_char_format_t format = HAP_CHAR_FORMAT_NONE);
    
    Value(bool);
    Value(uint8_t);
    Value(uint32_t);
    Value(uint64_t);
    Value(float);
    Value(const std::string&);

    operator bool() const;
    operator int() const;
    operator uint8_t() const;
    operator uint32_t() const;
    operator uint64_t() const;
    operator float() const;
    operator std::string() const;
};

}