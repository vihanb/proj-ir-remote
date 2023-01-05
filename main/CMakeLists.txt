idf_component_register(SRCS "FanController.cpp" "FanService.cpp" "App.cpp" "ir-remote.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES init_wifi qrcode homekit esp_hap_apple_profiles)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-write-strings)