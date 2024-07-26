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

    _HANDSDOWN,
};

#define GUI_S LGUI_T(KC_S)
#define ALT_C LALT_T(KC_C)
#define SFT_N LSFT_T(KC_N)
#define CTL_T LCTL_T(KC_T)

#define CTL_A LCTL_T(KC_A)
#define SFT_E LSFT_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define GUI_H LGUI_T(KC_H)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CANARY] = LAYOUT(
        KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                                                KC_Z,    KC_F,    KC_O,    KC_U,    KC_QUOT,
        KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                                                KC_M,    KC_N,    KC_E,    KC_I,    KC_A,
        KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,                                                KC_X,    KC_H,    KC_SCLN, KC_COMM, KC_DOT,
                  LT(_NUM, KC_ESC), LCTL_T(KC_SPC), LALT_T(KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LT(_NAV, KC_DEL)
    ),
    [_HANDSDOWN] = LAYOUT(
        KC_X,    KC_W,    KC_M,    KC_G,    KC_DQUO,                                             KC_HASH, KC_DOT,  KC_QUOT, KC_J,    KC_B,
        GUI_S,   ALT_C,   SFT_N,   CTL_T,   KC_K,                                                KC_COMM, CTL_A,   SFT_E,   ALT_I,   GUI_H,
        KC_V,    KC_P,    KC_L,    KC_D,    KC_SLSH,                                             KC_MINS, KC_U,    KC_O,    KC_Y,    KC_F,
                                        KC_ESC,   KC_R,   KC_TAB,       KC_ENT,   KC_SPC,   KC_BSPC
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
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                XXXXXXX, MAGIC_KEY_LAYER0, MAGIC_KEY_LAYER1, XXXXXXX, XXXXXXX,
                                         XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

enum combos {
    COMBO_CAPS_WORD,
    COMBO_LAYER_NAV,
    COMBO_LAYER_SYM,
    COMBO_LAYER_NUM,
    COMBO_LAYER_CFG,
};

const uint16_t PROGMEM combo_caps_word[] = {SFT_N, SFT_E, COMBO_END};
const uint16_t PROGMEM combo_layer_nav[] = {KC_SPC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM combo_layer_sym[] = {KC_ENT, KC_SPC, COMBO_END};
const uint16_t PROGMEM combo_layer_num[] = {KC_R, KC_TAB, COMBO_END};
const uint16_t PROGMEM combo_layer_cfg[] = {KC_ESC, KC_R, COMBO_END};

combo_t key_combos[] = {
    [COMBO_CAPS_WORD] = COMBO(combo_caps_word, QK_CAPS_WORD_TOGGLE),
    [COMBO_LAYER_NAV] = COMBO(combo_layer_nav, MO(_NAV)),
    [COMBO_LAYER_SYM] = COMBO(combo_layer_sym, MO(_SYM)),
    [COMBO_LAYER_NUM] = COMBO(combo_layer_num, MO(_NUM)),
    [COMBO_LAYER_CFG] = COMBO(combo_layer_cfg, MO(_CFG)),
};
