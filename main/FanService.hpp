#pragma once

#include <homekit.hpp>
#include <hap_apple_servs.h>
#include <hap_apple_chars.h>

#include "FanController.hpp"

class FanService: public HomeKit::Service {
private:
    FanController fanController;
public:
    explicit FanService(gpio_num_t gpio);

    // hap_status_t readCharacteristic(hap_char_t *characteristic) override;
    void writeCharacteristic(std::vector<HomeKit::WriteData> &writeData) override;
};