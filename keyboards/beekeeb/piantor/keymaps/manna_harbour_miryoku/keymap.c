// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include QMK_KEYBOARD_H
#include "print.h"
#include "raw_hid.h"

const uint16_t PROGMEM restore_window_size[] = {RWIN(KC_LEFT), RWIN(KC_RIGHT), COMBO_END};
combo_t key_combos[] = {
    COMBO(restore_window_size, RWIN(KC_UP)),
};

// Notifies the host of the layer change using raw HID
// https://docs.qmk.fm/features/rawhid#usage
// Layers reference: users/manna_harbour_miryoku/miryoku_babel/miryoku_layer_list.h
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t hi_layer = get_highest_layer(state);
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: Selected Layer: %d\n", hi_layer);
#endif
    raw_hid_send(&hi_layer,32);
    return state;
}

// Predictive tap hold: https://github.com/jgandert/qmk_modules/tree/main/predictive_tap_hold
const uint8_t pth_side_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_miryoku(
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R
);
