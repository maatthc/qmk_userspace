// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
#include QMK_KEYBOARD_H
#include "print.h"

const uint16_t PROGMEM restore_window_size[] = {RWIN(KC_LEFT), RWIN(KC_RIGHT), COMBO_END};
combo_t key_combos[] = {
    COMBO(restore_window_size, RWIN(KC_UP)),
};

// Notifies the host of the layer change
// Layers reference: users/manna-harbour_miryoku/miryoku_babel/miryoku_layer_list.h
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            // send f13
            SEND_STRING(SS_TAP(X_F13));
            break;
        case 4:
            SEND_STRING(SS_TAP(X_F14));
            break;
        case 5:
            SEND_STRING(SS_TAP(X_F15));
            break;
        case 6:
            SEND_STRING(SS_TAP(X_F16));
            break;
        case 7:
            SEND_STRING(SS_TAP(X_F17));
            break;
        case 8:
            SEND_STRING(SS_TAP(X_F18));
            break;
        case 9:
            SEND_STRING(SS_TAP(X_F19));
            break;
        default:
            uprintf("Layer not mapped: %d\n", get_highest_layer(state));
            break;
    }
    return state;
}

// Predictive tap hold: https://github.com/jgandert/qmk_modules/tree/main/predictive_tap_hold
const uint8_t pth_side_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT_miryoku(
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R,
    PTH_L, PTH_L, PTH_L, PTH_L, PTH_L,     PTH_R, PTH_R, PTH_R, PTH_R, PTH_R
);
