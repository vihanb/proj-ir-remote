#include <stdio.h>

#include <esp_log.h>
#include <esp_wifi.h>
#include <esp_event.h>

#include <Wifi.hpp>
#include "App.hpp"

App app;

extern "C" void app_main(void)
{
    // Setup the event group.
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    app.init();
    app.start();
}
