/* Copyright 2021 weteor
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

enum layers
{
    _CANARY = 0,
    _SYM,
    _NAV,
    _NUM,
    _CFG,
};

#define CS(x) C(S(x))

const uint16_t PROGMEM combo_ae[] = {KC_QUOT, KC_A, COMBO_END};
const uint16_t PROGMEM combo_oe[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM combo_ue[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_ss[] = {KC_Y, KC_S, COMBO_END};

const uint16_t PROGMEM combo_lshift[] = {KC_S, KC_V, COMBO_END};
const uint16_t PROGMEM combo_lctrl[] = {KC_T, KC_D, COMBO_END};
const uint16_t PROGMEM combo_lalt[] = {KC_R, KC_J, COMBO_END};
const uint16_t PROGMEM combo_lgui[] = {KC_C, KC_Q, COMBO_END};

const uint16_t PROGMEM combo_rshift[] = {KC_N, KC_H, COMBO_END};
const uint16_t PROGMEM combo_rctrl[] = {KC_E, KC_SCLN, COMBO_END};
const uint16_t PROGMEM combo_ralt[] = {KC_I, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_rgui[] = {KC_A, KC_DOT, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_ae, RALT(KC_QUOT)),
    COMBO(combo_oe, RALT(KC_SCLN)),
    COMBO(combo_ue, RALT(KC_LBRC)),
    COMBO(combo_ss, RALT(KC_MINS)),

    COMBO(combo_lshift, KC_LSFT),
    COMBO(combo_lctrl, KC_LCTL),
    COMBO(combo_lalt, KC_LALT),
    COMBO(combo_lgui, KC_LGUI),

    COMBO(combo_rshift, KC_LSFT),
    COMBO(combo_rctrl, KC_LCTL),
    COMBO(combo_ralt, KC_LALT),
    COMBO(combo_rgui, KC_LGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CANARY] = LAYOUT(
        KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                                                KC_Z,    KC_F,    KC_O,    KC_U,    KC_QUOT,
        KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                                                KC_M,    KC_N,    KC_E,    KC_I,    KC_A,
        KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,                                                KC_X,    KC_H,    KC_SCLN, KC_COMM, KC_DOT,
                  LT(_NUM, KC_ESC), LCTL_T(KC_SPC), LALT_T(KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LT(_NAV, KC_DEL)
    ),
    [_SYM] = LAYOUT(
        KC_GRV , KC_CIRC,   KC_AT,  KC_DLR, KC_TILD,                                KC_AMPR, KC_EXLM, KC_PIPE, KC_UNDS, KC_HASH,
        KC_SLSH, KC_LBRC, KC_LCBR, KC_LPRN,  KC_EQL,                                KC_ASTR, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS,
        XXXXXXX, KC_QUES, KC_MINS, KC_PERC, KC_PLUS,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, MO(_CFG),     XXXXXXX, LSFT_T(KC_ENT), XXXXXXX
    ),
    [_NAV] = LAYOUT(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,                                XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,  KC_DEL,
        KC_LGUI, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_END,
        XXXXXXX, XXXXXXX, KC_MSTP, XXXXXXX, XXXXXXX,                           XXXXXXX, C(KC_TAB), CS(KC_TAB), XXXXXXX, XXXXXXX,
                                        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, KC_LGUI, XXXXXXX
    ),
    [_NUM] = LAYOUT(
        XXXXXXX,  KC_F9, KC_F10, KC_F11, KC_F12,                                    KC_PPLS,  KC_P7,  KC_P8,  KC_P9, KC_PSLS,
        XXXXXXX,  KC_F5,  KC_F6,  KC_F7,  KC_F8,                                    KC_PEQL,  KC_P4,  KC_P5,  KC_P6, KC_PENT,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F4,                                    KC_PMNS,  KC_P1,  KC_P2,  KC_P3, KC_PAST,
                                        XXXXXXX, XXXXXXX, XXXXXXX,      KC_COMM, LSFT_T(KC_P0), KC_PDOT
    ),
    [_CFG] = LAYOUT(
        QK_BOOTLOADER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
    ),
};


uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    default:
        return 75;
    }
}
