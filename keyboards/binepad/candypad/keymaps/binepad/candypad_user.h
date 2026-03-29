// Copyright 2025 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#ifdef VIA_ENABLE // Only works if VIA is enabled

enum via_per_key_value {
    id_rtc_date = 8,
    id_rtc_time = 9,
    id_rtc_posix_time = 10,
    id_firmware_button = 99
};

enum via_id_firmware_button {
    id_buton_ignore = 0,
    id_button_bootloader,   // 1
    id_button_reboot,       // 2
    id_button_debug_toggle, // 3
    id_button_clear_eeprom  // 4
};

#endif // VIA_ENABLE
