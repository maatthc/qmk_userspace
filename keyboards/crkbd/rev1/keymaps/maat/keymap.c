// clang-format off
#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "keymap.h"

// Notifies the host of the layer change using raw HID
// https://docs.qmk.fm/features/rawhid#usage
//
#ifdef RAW_ENABLE
    layer_state_t layer_state_set_user(layer_state_t state) {
        uint8_t hi_layer = get_highest_layer(state);
    #ifdef CONSOLE_ENABLE
        #include "print.h"
        uprintf("LAYER: Selected Layer: %d\n", hi_layer);
    #endif
        uint8_t response[RAW_EPSIZE];
        memset(response, 0x00, RAW_EPSIZE);
        response[PAYLOAD_BEGIN]     = PAYLOAD_MARK;
        response[PAYLOAD_BEGIN + 1] = hi_layer;
        raw_hid_send(response, RAW_EPSIZE);
        return state;
    }
#endif /* ifdef RAW_ENABLE */

// Predictive tap hold: https://github.com/jgandert/qmk_modules/tree/main/predictive_tap_hold
const uint8_t pth_side_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_split_3x6_3(
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,PTH_L,    PTH_R, PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,PTH_L,    PTH_R, PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,PTH_L,    PTH_R, PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
                        PTH_L, PTH_L, PTH_L,    PTH_R, PTH_R, PTH_R
);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[L_BASE]=LAYER(LAYER_BASE),
[L_MEDIA]=LAYER(LAYER_MEDIA),
[L_NAV]=LAYER(LAYER_NAV),
[L_NUM]=LAYER(LAYER_NUM),
[L_SYM]=LAYER(LAYER_SYM),
[L_FUN]=LAYER(LAYER_FUN),
};

#ifdef OLED_ENABLE
    #include "oled.c"
#endif
