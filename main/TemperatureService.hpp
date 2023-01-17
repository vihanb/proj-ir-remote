#ifndef IR_REMOTE_TEMPERATURESERVICE_HPP
#define IR_REMOTE_TEMPERATURESERVICE_HPP


#include <homekit.hpp>

class TemperatureService : public HomeKit::Service {
public:
    explicit TemperatureService();

    hap_status_t readCharacteristic(HomeKit::Characteristic &characteristic) override;
};


#endif //IR_REMOTE_TEMPERATURESERVICE_HPP
