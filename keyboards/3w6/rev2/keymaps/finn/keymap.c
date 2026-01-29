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

#include "caps_word.h"
#include QMK_KEYBOARD_H

enum layers {
    _HANDSDOWN_GOLD = 0,
    _NUM_FN,
    _NAV,
};

enum custom_keycodes {
    MY_BEGIN = SAFE_RANGE
};

#define MY_A LCTL_T(KC_A)
#define MY_E LSFT_T(KC_E)
#define MY_I LALT_T(KC_I)
#define MY_H LGUI_T(KC_H)

#define MY_R LGUI_T(KC_R)
#define MY_S LALT_T(KC_S)
#define MY_N LSFT_T(KC_N)
#define MY_D LCTL_T(KC_D)

#define KC_UL_A RALT(KC_Q)
#define KC_UL_O RALT(KC_P)
#define KC_UL_U RALT(KC_Y)
#define KC_SZ RALT(KC_S)

#define MY_SFT LT(0, KC_NO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HANDSDOWN_GOLD] = LAYOUT(
                          KC_J,     KC_G,     KC_M,     KC_P,     KC_V,        KC_DOT,  KC_LPRN,  KC_RPRN,  KC_SCLN,  KC_QUOT,
                          MY_R,     MY_S,     MY_N,     MY_D,     KC_B,        KC_COMM, MY_A,     MY_E,     MY_I,     MY_H,
                          KC_X,     KC_F,     KC_L,     KC_C,     KC_W,        KC_MINS, KC_U,     KC_O,     KC_Y,     KC_K,
                                             TT(_NUM_FN), KC_T, KC_ENT,        MY_SFT, KC_SPC, TT(_NAV)
                          ),
    [_NUM_FN] = LAYOUT(
                       QK_BOOT,   KC_F9,   KC_F8,   KC_F7,  KC_F12,         _______,    KC_7,    KC_8,    KC_9, _______,
                       _______,   KC_F6,   KC_F5,   KC_F4,  KC_F11,         _______,    KC_4,    KC_5,    KC_6, KC_DOT,
                       _______,   KC_F3,   KC_F2,   KC_F1,  KC_F10,         _______,    KC_1,    KC_2,    KC_3, _______,
                       _______, _______, _______, _______, KC_0, _______
                       ),
    [_NAV] = LAYOUT(
                    XXXXXXX,     KC_VOLD,         KC_MUTE,         KC_VOLU, XXXXXXX,       KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
                    KC_LGUI, LALT_T(KC_MPRV), LSFT_T(KC_MPLY), LCTL_T(KC_MNXT), XXXXXXX,       KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
                    XXXXXXX,         XXXXXXX,         KC_MSTP,         XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                              _______, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, _______
                    ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                  '*', '*', '*',  '*', '*', '*'
    );

enum combos {
    COMBO_AMPR = 0,
    COMBO_ASTR,
    COMBO_BSPC,
    COMBO_COLN,
    COMBO_DEL,
    COMBO_DLR,
    COMBO_EQL,
    COMBO_ESC,
    COMBO_GRV,
    COMBO_GT,
    COMBO_LT,
    COMBO_PERC,
    COMBO_Q,
    COMBO_SLSH,
    COMBO_SZ,
    COMBO_TAB,
    COMBO_TILD,
    COMBO_UNDS,
    COMBO_UL_A,
    COMBO_UL_O,
    COMBO_UL_U,
    COMBO_Z,
};

const uint16_t PROGMEM combo_ampr[] = {MY_I, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_astr[] = {KC_RPRN, MY_E, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM combo_coln[] = {MY_D, KC_B, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_RPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM combo_dlr[] = {KC_M, MY_N, COMBO_END};
const uint16_t PROGMEM combo_eql[] = {MY_N, KC_L, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {MY_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo_lt[] = {MY_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_perc[] = {KC_B, KC_W, COMBO_END};
const uint16_t PROGMEM combo_q[] = {KC_G, MY_S, COMBO_END};
const uint16_t PROGMEM combo_slsh[] = {KC_SCLN, MY_I, COMBO_END};
const uint16_t PROGMEM combo_sz[] = {MY_R, KC_X, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {MY_S, MY_N, COMBO_END};
const uint16_t PROGMEM combo_tild[] = {KC_P, MY_D, COMBO_END};
const uint16_t PROGMEM combo_unds[] = {KC_COMM, MY_A, COMBO_END};
const uint16_t PROGMEM combo_ul_a[] = {KC_DOT, MY_A, COMBO_END};
const uint16_t PROGMEM combo_ul_o[] = {MY_E, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ul_u[] = {MY_A, KC_U, COMBO_END};
const uint16_t PROGMEM combo_z[] = {KC_J, MY_R, COMBO_END};

combo_t key_combos[] = {
    [COMBO_AMPR] = COMBO(combo_ampr, KC_AMPR),
    [COMBO_ASTR] = COMBO(combo_astr, KC_ASTR),
    [COMBO_BSPC] = COMBO(combo_bspc, KC_BSPC),
    [COMBO_COLN] = COMBO(combo_coln, KC_COLN),
    [COMBO_DEL] = COMBO(combo_del, KC_DEL),
    [COMBO_DLR] = COMBO(combo_dlr, KC_DLR),
    [COMBO_EQL] = COMBO(combo_eql, KC_EQL),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_GRV] = COMBO(combo_grv, KC_GRV),
    [COMBO_GT] = COMBO(combo_gt, KC_GT),
    [COMBO_LT] = COMBO(combo_lt, KC_LT),
    [COMBO_PERC] = COMBO(combo_perc, KC_PERC),
    [COMBO_Q] = COMBO(combo_q, KC_Q),
    [COMBO_SZ] = COMBO(combo_sz, KC_SZ),
    [COMBO_SLSH] = COMBO(combo_slsh, KC_SLSH),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_TILD] = COMBO(combo_tild, KC_TILD),
    [COMBO_UNDS] = COMBO(combo_unds, KC_UNDS),
    [COMBO_UL_A] = COMBO(combo_ul_a, KC_UL_A),
    [COMBO_UL_O] = COMBO(combo_ul_o, KC_UL_O),
    [COMBO_UL_U] = COMBO(combo_ul_u, KC_UL_U),
    [COMBO_Z] = COMBO(combo_z, KC_Z),
};

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
    case COMBO_TAB:
        return true;
    default:
        return false;
    }
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch(combo_index) {
    case COMBO_Z:
    case COMBO_Q:
    case COMBO_COLN:
    case COMBO_UL_A:
    case COMBO_UL_O:
    case COMBO_UL_U:
    case COMBO_SZ:
        return COMBO_TERM + 10;
    default:
        return COMBO_TERM;
    }
}

const key_override_t at_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_AT);
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_EXLM);
const key_override_t backslash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_CIRC);
const key_override_t question_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUES);
const key_override_t plus_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_PLUS);
const key_override_t euro_override = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, RALT(KC_5));
const key_override_t hash_override = ko_make_basic(MOD_MASK_SHIFT, KC_TILD, KC_HASH);
const key_override_t pipe_override = ko_make_basic(MOD_MASK_SHIFT, KC_AMPR, KC_PIPE);
const key_override_t lcbr_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LCBR);
const key_override_t rcbr_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RCBR);
const key_override_t lbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_LT, KC_LBRC);
const key_override_t rbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_GT, KC_RBRC);

const key_override_t *key_overrides[] = {
    &at_override,
    &exclamation_mark_override,
    &backslash_override,
    &circ_override,
    &question_mark_override,
    &plus_override,
    &euro_override,
    &hash_override,
    &pipe_override,
    &lcbr_override,
    &rcbr_override,
    &lbrc_override,
    &rbrc_override
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
    case KC_A ... KC_Z:
    case KC_UL_A:
    case KC_UL_O:
    case KC_UL_U:
    case KC_SZ:
        add_weak_mods(MOD_LSFT);
        return true;

    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
        return true;

    default:
        return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TT(_NUM_FN):
    case TT(_NAV):
        return true;
    default:
        return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MY_SFT:
        if (record->tap.count == 0 && record->event.pressed) {
            add_mods(MOD_LSFT);
        }
        else if (record->tap.count == 0 && !record->event.pressed) {
            del_mods(MOD_LSFT);
        }
        else if (record->tap.count == 1 && record->event.pressed) {
            set_oneshot_mods(get_oneshot_mods() ^ MOD_LSFT);
        }
        else if (record->tap.count == 2 && record->event.pressed) {
            caps_word_toggle();
        }
        return false;
    }

    return true;
}
