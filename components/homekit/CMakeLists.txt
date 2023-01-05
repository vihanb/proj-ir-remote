idf_component_register(SRCS "homekit_write_data.cpp" "homekit_characteristic.cpp" "homekit_service.cpp" "homekit_accessory.cpp" "homekit_value.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_hap_core)
