idf_component_register(SRCS "FanController.cpp" "FanService.cpp" "App.cpp" "ir-remote.cpp" "TemperatureService.cpp" "HumidityService.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES Remote WiFi qrcode homekit esp_hap_apple_profiles CXXFreeRTOS)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-write-strings)