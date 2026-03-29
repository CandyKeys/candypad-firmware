// Copyright 2024 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "candypad_user.h"

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

// Only works if VIA is enabled
#ifdef VIA_ENABLE

void candypad_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rtc_date:
        case id_rtc_time:
        case id_rtc_posix_time:
            break;

        case id_firmware_button: {
            switch (value_data[0]) {
                case id_button_bootloader:
                    reset_keyboard();
                    break;
                case id_button_reboot:
                    soft_reset_keyboard();
                    break;
                case id_button_debug_toggle:
                    debug_enable ^= 1;
                    break;
                case id_button_clear_eeprom:
                    eeconfig_disable();
                    wait_ms(500);
                    soft_reset_keyboard();
                    break;
            }
            break;
        }
    }
}

void candypad_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rtc_date:
        case id_rtc_time:
        case id_rtc_posix_time:
            break;
        case id_firmware_button:
            value_data[0] = 0;
            break;
    }
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                candypad_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                candypad_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                break;
            default:
                break;
        }
    }
}

#endif // VIA_ENABLE
