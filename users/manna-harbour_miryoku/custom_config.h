// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define TAPPING_TERM 200
#define DYNAMIC_TAPPING_TERM_INCREMENT 50

// Do not Auto Shift special keys -_, =+, [{, ]}, ;:, '", ,<, .>, and /?
//#define NO_AUTO_SHIFT_SPECIAL

// Do not Auto Shift numeric keys, zero through nine.
//#define NO_AUTO_SHIFT_NUMERIC

#define MIRYOKU_MAPPING( \
      K00,  K01,  K02,  K03,  K04,         K05,  K06,  K07,  K08,  K09, \
      K10,  K11,  K12,  K13,  K14,         K15,  K16,  K17,  K18,  K19, \
      K20,  K21,  K22,  K23,  K24,         K25,  K26,  K27,  K28,  K29, \
      N30,  N31,  K32,  K33,  K34,         K35,  K36,  K37,  N38,  N39 \
) \
LAYOUT_split_3x6_3( \
RWIN(RCTL(KC_LEFT)),  K00,  K01,  K02,  K03,  K04,         K05,  K06,  K07,  K08,  K09,  RWIN(RCTL(KC_RIGHT)), \
RWIN(KC_LEFT),  K10,  K11,  K12,  K13,  K14,         K15,  K16,  K17,  K18,  K19,  RWIN(KC_RIGHT), \
RSG(KC_LEFT),  K20,  K21,  K22,  K23,  K24,         K25,  K26,  K27,  K28,  K29,  RSG(KC_RIGHT) , \
                  K32,  K33,  K34,         K35,  K36,  K37 \
)

#define MIRYOKU_LAYER_BASE \
KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
KC_A,              LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      KC_QUOT,   \
KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMMA,          KC_DOT,            KC_SLSH,\
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_BSPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_SPC), LT(U_FUN,KC_INS),  U_NP,              U_NP


// Added Dynamic Tapping Term : https://docs.qmk.fm/tap_hold#dynamic-tapping-term
#define MIRYOKU_LAYER_MEDIA \
U_NA,     U_NA,     U_NA,     U_NA,     DT_PRNT,           QK_BACKLIGHT_STEP, KC_BRID,           KC_BRIU,           U_NU,              U_NU,           \
KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  DT_UP,             KC_MPRV,           KC_VOLD,           KC_VOLU,           KC_MNXT,           U_NU,           \
U_NA,     U_NA,     U_NA,     U_NA,     DT_DOWN,           U_NU,              U_NU,              U_NU,              U_NU,              U_NU,           \
U_NP,     U_NP,     U_NA,     U_NA,     U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           U_NP,              U_NP
