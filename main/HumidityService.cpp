#include "HumidityService.hpp"

#include <hap_apple_servs.h>
#include <hap_apple_chars.h>

HumidityService::HumidityService()
: HomeKit::Service(
        hap_serv_humidity_sensor_create(50.0),
        {
                hap_char_name_create("Humidity Sensor")
        }) {}

hap_status_t HumidityService::readCharacteristic(HomeKit::Characteristic &characteristic) {
    if (characteristic.isTypeUUID(HAP_CHAR_UUID_CURRENT_RELATIVE_HUMIDITY)) {
        float humidity = 50.0;
        characteristic.value(humidity);
        return HAP_STATUS_SUCCESS;
    } else {
        return HAP_STATUS_VAL_INVALID;
    }
}
