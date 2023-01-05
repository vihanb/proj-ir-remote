#include "FanController.hpp"
#include <esp_log.h>

static const char *TAG = "Fan Controller";

FanController::FanController()
    : _isActive(false),
      _currentSwing(false),
      _currentSpeed(Speed::Off) {
    _queueHandle =
        xQueueCreateStatic(
            1,
            sizeof(_QueueData),
            _queueStorage,
            &_queue);

    xTaskCreate(&FanController::handlerCallback, "Fan Controller Handler", 4096, this, 5, &_taskHandle);
}

void FanController::handlerCallback(void *params) {
    FanController *controller = static_cast<FanController *>(params);
    _QueueData target;

    while (true) {
        if (xQueueReceive(controller->_queueHandle, &target, 5) == pdTRUE) {
            // Update Speed
            int speedTicks = distanceBetween(controller->_currentSpeed, target.speed);
            // TODO: issue << speed ticks >>

            controller->_currentSpeed = target.speed;

            // Update swing
            if (target.swing != controller->_currentSwing) {
                // TODO: issue swing command
            }

            controller->_currentSwing = target.swing;

            ESP_LOGI(TAG, "Updated fan state. (speed: %d, swing: %d)", static_cast<int>(target.speed), target.swing);
        }

        // TODO: write back to original
    }
}

FanController::~FanController() {
    vTaskDelete(_taskHandle);
    vQueueDelete(_queueHandle);
}

bool FanController::isSwinging() const {
    return _currentSwing;
}

FanController::Speed FanController::speed() const {
    return _isActive ? Speed::Off : _currentSpeed;
}

void FanController::commit(Speed targetSpeed, bool targetSwing) {
    _QueueData newState = {
        .speed = targetSpeed,
        .swing = targetSwing
    };

    xQueueOverwrite(_queueHandle, &newState);
}