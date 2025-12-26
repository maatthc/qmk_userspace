#pragma once

// PTH
// https://github.com/jgandert/qmk_modules/blob/main/predictive_tap_hold/README.md
// #define PTH_DISABLED
#define TAPPING_TERM 0
#define PTH_FAST_STREAK_TAP_ENABLE
// #define PTH_DEBUG
#define PTH_DONT_HOLD_INSTANTLY
// PTH end

// App Companion
// https://docs.qmk.fm/features/rawhid#usage
// https://github.com/maatthc/qmk_layers_app_companion
#define RAW_EPSIZE 32
#define PAYLOAD_MARK 0x90
#define PAYLOAD_BEGIN 24

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE 0x61
// App Companion end

// Do not Auto Shift special keys -_, =+, [{, ]}, ;:, '", ,<, .>, and /?
// #define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
// #define NO_AUTO_SHIFT_NUMERIC
