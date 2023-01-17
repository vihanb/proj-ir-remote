#ifndef IR_REMOTE_HUMIDITYSERVICE_HPP
#define IR_REMOTE_HUMIDITYSERVICE_HPP

#include <homekit.hpp>

class HumidityService : public HomeKit::Service {
public:
    explicit HumidityService();

    hap_status_t readCharacteristic(HomeKit::Characteristic &characteristic) override;
};


#endif //IR_REMOTE_HUMIDITYSERVICE_HPP
