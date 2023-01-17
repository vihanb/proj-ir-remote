#include "TemperatureService.hpp"

#include <hap_apple_servs.h>
#include <hap_apple_chars.h>

TemperatureService::TemperatureService()
    : HomeKit::Service(
        hap_serv_temperature_sensor_create(0.0), {
                hap_char_name_create("Temperature Sensor")
        }) {}

hap_status_t TemperatureService::readCharacteristic(HomeKit::Characteristic &characteristic) {
    if (characteristic.isTypeUUID(HAP_CHAR_UUID_CURRENT_TEMPERATURE)) {
        float temperature = 24.0f; // In Celsius
        characteristic.value(temperature);
        return HAP_STATUS_SUCCESS;
    } else {
        return HAP_STATUS_VAL_INVALID;
    }
}
