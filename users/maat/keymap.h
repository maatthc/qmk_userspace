// clang-format off
#pragma once

#define LAYER(...) MAPPING(__VA_ARGS__)
#define U_NA KC_NO
#define U_NP KC_NO
#define U_NU KC_NO

enum layers_num { L_BASE, L_NAV, L_MOUSE, L_MEDIA, L_NUM, L_SYM, L_FUN };

#define MAPPING( \
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

#define LAYER_BASE \
KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
KC_A,              LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      KC_QUOT,   \
KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMMA,          KC_DOT,            KC_SLSH,\
U_NP,              U_NP,              LT(L_MOUSE,KC_ESC),LT(L_NAV,KC_BSPC),  LT(L_NUM,KC_TAB),LT(L_SYM,KC_ENT),  LT(L_FUN,KC_SPC), LT(L_MEDIA,KC_INS),  U_NP,              U_NP


#define LAYER_MEDIA \
UG_TOGG,   KC_BRID,   KC_BRIU,   QK_BACKLIGHT_STEP,  UG_VALU,        QK_BOOT,    U_NA,   U_NA,   U_NA,   KC_SLEP,        \
KC_MPRV,   KC_VOLD,   KC_VOLU,   KC_MNXT,   UG_VALD,              U_NA,    KC_LSFT,    KC_LCTL,   KC_LALT,   KC_LGUI, \
UG_NEXT,   UG_HUEU,   UG_HUED,   UG_SATU,   UG_SATD,              U_NA,    U_NA,   U_NA,   U_NA,    U_NA,     \
U_NP,      U_NP,      KC_MUTE,   KC_MPLY,   KC_MSTP,           U_NA,    U_NA,   U_NA,   U_NP,   U_NP


#define LAYER_NUM \
U_NA,     U_NA,    U_NA,  U_NA,   U_NA,                 KC_LBRC,        KC_7,        KC_8,       KC_9,     KC_RBRC,         \
KC_LGUI,     KC_LALT,    KC_LCTL,    KC_LSFT,    U_NA,           KC_SCLN,     KC_4,     KC_5,      KC_6,     KC_EQL,          \
U_NA,     U_NA,    U_NA,    U_NA,  U_NA,             KC_GRV,     KC_1,       KC_2,        KC_3,           KC_BSLS,           \
U_NP,     U_NP,    U_NA,    U_NA,  U_NA,             KC_MINS,     KC_0,       KC_DOT,     U_NP,         U_NP


#define LAYER_FUN \
KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              U_NA,         U_NA,       U_NA,       U_NA,       \
KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL,           U_NA,              KC_LSFT,      KC_LCTL,    KC_LALT,    KC_LGUI,    \
KC_F10,            KC_F1,             KC_F2,             KC_F3,             KC_PAUS,           U_NA,              U_NA,         U_NA,       U_NA,       U_NA,       \
U_NP,              U_NP,              KC_APP,            KC_SPC,            KC_LGUI,           U_NA,              U_NA,         U_NA,       U_NP,       U_NP


#define LAYER_SYM \
KC_LCBR,           KC_AMPR,           KC_ASTR,           KC_LPRN,           KC_RCBR,           U_NA,              U_NA,   U_NA,  U_NA,    U_NA,     \
KC_COLN,           KC_DLR,            KC_PERC,           KC_CIRC,           KC_PLUS,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_TILD,           KC_EXLM,           KC_AT,             KC_HASH,           KC_PIPE,           U_NA,              U_NA,    U_NA,  U_NA,           U_NA,              \
U_NP,              U_NP,              KC_LPRN,           KC_RPRN,           KC_UNDS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP


#define LAYER_NAV \
U_NA,     U_NA,    U_NA,  U_NA,   U_NA,              KC_AGIN,             KC_PSTE,             KC_COPY,             KC_CUT,             KC_UNDO,             \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              KC_LEFT,           KC_DOWN,           KC_UP,             KC_RGHT,           CW_TOGG,           \
U_NA,              U_NA,              U_NA,    U_NA,    U_NA,              KC_HOME,           KC_PGDN,           KC_PGUP,           KC_END,            KC_INS,            \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_ENT,            KC_BSPC,           KC_DEL,            U_NP,              U_NP


