#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <cstdint>
#include <esp_log.h>
#include <driver/rmt.h>
#include <mutex>

#include <Lasko.hpp>

class FanController {
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
    bool _isActive;

    bool _currentSwing;
    Speed _currentSpeed;

    struct _QueueData {
        Speed speed;
        bool swing;
    };
    
    uint8_t _queueStorage[sizeof(_QueueData)];
    StaticQueue_t _queue;
    QueueHandle_t _queueHandle;

    TaskHandle_t _taskHandle;
    Remote::Lasko::LaskoChannel remote;

    mutable std::mutex _txActive;

    static void task(void *params);
    void handle(const _QueueData &target);
protected:
    void _speed(Speed targetSpeed);
    void _power(bool isOn);
    void _isSwinging(bool targetSwing);

public:
    explicit FanController();
    FanController(const FanController&) = delete;
    FanController(FanController&&) = delete;
    ~FanController();

    bool isSwinging() const;
    Speed speed() const;

    /**
     * Interfaces with transciever and applies specified
     * changes.
     */
    void commit(Speed targetSpeed, bool targetSwing);
};