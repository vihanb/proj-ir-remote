#pragma once

typedef enum {
    HAP_FAN_ROTATION_DIRECTION_CLOCKWISE = 0,
    HAP_FAN_ROTATION_DIRECTION_COUNTERCLOCKWISE = 1,
} hap_fan_rotation_direction_t;

typedef enum {
    HAP_INACTIVE = 0,
    HAP_ACTIVE = 1,
} hap_active_t;

typedef enum {
    HAP_SWING_MODE_DISABLED = 0,
    HAP_SWING_MODE_ENABLED = 1,
} hap_swing_mode_t;