#pragma once
#include <esp_err.h>
#include <string>

esp_err_t get_device_service_name(char *service_name, size_t max);
esp_err_t get_device_pop(char *pop, size_t max);