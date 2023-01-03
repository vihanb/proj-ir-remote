idf_component_register(SRCS "Wifi.cpp" "utils.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES wifi_provisioning qrcode)
