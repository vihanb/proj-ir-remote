#include "FanService.hpp"

#include <esp_log.h>

static const char *TAG = "FanService";

FanService::FanService()
    : HomeKit::Service(
        hap_serv_fan_v2_create(false),
        {
            hap_char_name_create("My Fan"),
            hap_char_swing_mode_create(HAP_SWING_MODE_DISABLED),
            hap_char_rotation_speed_create(0),
        }
    ), fanController() {}

void FanService::writeCharacteristic(std::vector<HomeKit::WriteData> &writeData) {
    auto speed = fanController.speed();
    uint8_t isSwinging = fanController.isSwinging();

    for (HomeKit::WriteData &writeData : writeData) {
        if (writeData.characteristic().isTypeUUID(HAP_CHAR_UUID_ACTIVE)) {
            uint8_t isActive = writeData.value();
            if (isActive) {
                speed = FanController::Speed::High;
            } else {
                speed = FanController::Speed::Off;
            }
        } else if (writeData.characteristic().isTypeUUID(HAP_CHAR_UUID_SWING_MODE)) {
            isSwinging = static_cast<uint8_t>(writeData.value());
        } else if (writeData.characteristic().isTypeUUID(HAP_CHAR_UUID_ROTATION_SPEED)) {
            speed = FanController::scalarToSpeed(writeData.value());
        } else {
            writeData.status(HAP_STATUS_VAL_INVALID);
            continue;
        }

        writeData.status(HAP_STATUS_SUCCESS);
    }

    fanController.commit(speed, isSwinging);
    (*this)[HAP_CHAR_UUID_ACTIVE] = static_cast<uint8_t>(speed == FanController::Speed::Off);
    (*this)[HAP_CHAR_UUID_ROTATION_SPEED] = FanController::speedToScalar(speed);
    (*this)[HAP_CHAR_UUID_SWING_MODE] = static_cast<uint8_t>(isSwinging);
}