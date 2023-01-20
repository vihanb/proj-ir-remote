#pragma once

#include <cstdint>
#include <esp_log.h>
#include <driver/rmt.h>
#include <mutex>
#include <CXXFreeRTOS.hpp>

#include <Lasko.hpp>

class FanController : private FreeRTOS::Task {
public:
    enum class Speed {
        Off = 0,
        Low = 1,
        Medium = 2,
        High = 3
    };

    static constexpr Speed scalarToSpeed(float scalarSpeed) {
        if (scalarSpeed < 1.0f) {
            return Speed::Off;
        } else if (scalarSpeed < 34.0f) {
            return Speed::Low;
        } else if (scalarSpeed < 67.0f) {
            return Speed::Medium;
        } else {
            return Speed::High;
        }
    }

    static constexpr float speedToScalar(Speed speed) {
        switch (speed) {
            case Speed::Off: return 0.0;
            case Speed::Low: return 33.3;
            case Speed::Medium: return 66.6;
            case Speed::High: return 100;
            default: return 1.23f;
        }
    }

    static constexpr int distanceBetween(
        Speed currentSpeed,
        Speed targetSpeed
    ) {
        int currentSpeedN = static_cast<int>(currentSpeed);
        int targetSpeedN = static_cast<int>(targetSpeed);

        return (currentSpeedN - targetSpeedN + 3) % 3;
    }

private:
    struct QueueData {
        Speed speed;
        bool swing;
    };
    FreeRTOS::Queue<QueueData, 1> _queue;
    mutable std::mutex _txActive;

    Remote::Lasko::LaskoChannel remote;

    [[noreturn]] void task() override;
    void handle(const QueueData &target);

protected:
    bool _currentSwing;
    Speed _currentSpeed;

    void _speed(Speed targetSpeed);
    void _power(bool isOn);
    void _isSwinging(bool targetSwing);

public:
    explicit FanController(gpio_num_t gpio);
    FanController(const FanController&) = delete;
    FanController(FanController&&) = delete;

    bool isSwinging() const;
    Speed speed() const;

    /**
     * Interfaces with transceiver and applies specified
     * changes.
     */
    void commit(Speed targetSpeed, bool targetSwing);
};