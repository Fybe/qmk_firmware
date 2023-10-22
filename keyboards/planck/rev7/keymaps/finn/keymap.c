/* Copyright 2015-2023 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum planck_layers { _CANARY, _QWERTY, _RAISE, _LOWER, _FN };

enum planck_keycodes { CANARY = SAFE_RANGE, QWERTY };

#define FN MO(_FN)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define CANARY DF(_CANARY)
#define QWERTY DF(_QWERTY)

// Home row mods

#define MOD_C LGUI_T(KC_C)
#define MOD_R LALT_T(KC_R)
#define MOD_S LSFT_T(KC_S)
#define MOD_T LCTL_T(KC_T)

#define MOD_N LCTL_T(KC_N)
#define MOD_E LSFT_T(KC_E)
#define MOD_I LALT_T(KC_I)
#define MOD_A LGUI_T(KC_A)

// US international

#define KC_ADIA RALT(KC_QUOT)
#define KC_ODIA RALT(KC_SCLN)
#define KC_UDIA RALT(KC_LBRC)
#define KC_SS RALT(KC_MINS)
#define KC_EUR RALT(KC_E)

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_CANARY] = LAYOUT_planck_1x2uC(
    QK_GESC, KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,    KC_Z,    KC_F,    KC_O,    KC_U,    KC_EQL,  KC_BSPC,
    KC_TAB,  MOD_C,   MOD_R,   MOD_S,   MOD_T,   KC_G,    KC_M,    MOD_N,   MOD_E,   MOD_I,   MOD_A,   KC_QUOT,
    CW_TOGG, KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,    KC_X,    KC_H,    KC_SCLN, KC_COMM, KC_DOT,  KC_ENT,
    XXXXXXX, XXXXXXX, XXXXXXX, FN,      RAISE,      KC_SPACE,      LOWER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_QWERTY] = LAYOUT_planck_1x2uC(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
    QK_GESC, FN,      KC_LGUI, KC_LALT, RAISE,      KC_SPACE,      LOWER,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

[_RAISE] = LAYOUT_planck_1x2uC(
    XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_MINS, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_SLSH, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_SPACE,     KC_0,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_LOWER] = LAYOUT_planck_1x2uC(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_EUR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ODIA, KC_UDIA, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_ADIA, KC_SS,   XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_SPACE,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_FN] = LAYOUT_planck_1x2uC(
    QK_BOOTLOADER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F7,  KC_F8,   KC_F9,   XXXXXXX, XXXXXXX,
    XXXXXXX,       CANARY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F4,  KC_F5,   KC_F6,   KC_F11,  XXXXXXX,
    XXXXXXX,       QWERTY,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F1,  KC_F2,   KC_F3,   KC_F12,  XXXXXXX,
    XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,     KC_F10, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};
/* clang-format on */

layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MOD_A:
        case MOD_I:
        case MOD_C:
        case MOD_R:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}
