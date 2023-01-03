idf_component_register(SRCS "App.cpp" "ir-remote.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES init_wifi qrcode esp_hap_core esp_hap_apple_profiles)
