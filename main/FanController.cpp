#include "FanController.hpp"
#include <esp_log.h>

static const char *TAG = "Fan Controller";

FanController::FanController(gpio_num_t gpio)
    : FreeRTOS::Task("Fan Controller Handler"),
      remote(gpio),
      _currentSwing(false),
      _currentSpeed(Speed::Off) {}

void FanController::handle(const QueueData &target) {
    const std::lock_guard<std::mutex> _lock(_txActive);

    _speed(target.speed);
    _isSwinging(target.swing);

    ESP_LOGI(TAG, "Updated fan state. (speed: %d, swing: %d)", static_cast<int>(target.speed), target.swing);

    // TODO: write back to HomeKit
}

[[noreturn]] void FanController::task() {
    while (true) {
        if (auto value = _queue.receive()) {
            handle(*value);
        }
    }
}

void FanController::_speed(Speed targetSpeed) {
    bool isOn = targetSpeed != Speed::Off;
    if (isOn) {
        _power(true);
        int speedTicks = distanceBetween(_currentSpeed, targetSpeed);
        for (int i = 0; i < speedTicks; i++) {
            remote.execute(remote.speed);
        }
    } else {
        _power(false);
    }
}

void FanController::_power(bool isOn) {
    bool currentlyOn = _currentSpeed != Speed::Off;
    if (isOn != currentlyOn) {
        remote.execute(remote.togglePower);

        if (isOn) {
            _currentSpeed = Speed::High;
            _currentSwing = false;
        } else {
            _currentSpeed = Speed::Off;
        }

    }
}

void FanController::_isSwinging(bool targetSwing) {
    if (targetSwing != _currentSwing) {
        if (_currentSpeed == Speed::Off) {
            ESP_LOGW(TAG, "Toggling swing even though device is off.");
        }

        remote.execute(remote.toggleSwing);
        _currentSwing = targetSwing;
    }
}

bool FanController::isSwinging() const {
    const std::lock_guard<std::mutex> _lock(_txActive);
    return _currentSwing;
}

FanController::Speed FanController::speed() const {
    const std::lock_guard<std::mutex> _lock(_txActive);
    return _currentSpeed;
}

void FanController::commit(Speed targetSpeed, bool targetSwing) {
    _queue.overwrite({
        .speed = targetSpeed,
        .swing = targetSwing
    });
}