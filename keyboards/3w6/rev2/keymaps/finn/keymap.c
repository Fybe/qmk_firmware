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

#include "action_util.h"
#include "caps_word.h"
#include QMK_KEYBOARD_H

enum layers {
    _HANDSDOWN_GOLD = 0,
    _NUM_FN,
    _NAV,
};

enum custom_keycodes {
    KC_PRNS = SAFE_RANGE,
    KC_BRCS,
    KC_CBRS,

    KC_SMART_NUM,
};

enum tap_dance {
    TD_SMART_SFT = 0,
    TD_NUM_NAV,
};


#define KC_CTL_A LCTL_T(KC_A)
#define KC_SFT_E LSFT_T(KC_E)
#define KC_ALT_I LALT_T(KC_I)
#define KC_GUI_H LGUI_T(KC_H)

#define KC_GUI_R LGUI_T(KC_R)
#define KC_ALT_S LALT_T(KC_S)
#define KC_SFT_N LSFT_T(KC_N)
#define KC_CTL_D LCTL_T(KC_D)

#define KC_UL_A RALT(KC_Q)
#define KC_UL_O RALT(KC_P)
#define KC_UL_U RALT(KC_Y)
#define KC_SZ RALT(KC_S)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HANDSDOWN_GOLD] = LAYOUT(
                          KC_J,     KC_G,     KC_M,     KC_P,     KC_V,        KC_HASH, KC_DOT,   KC_SLSH,  KC_UNDS,  KC_QUOT,
                          KC_GUI_R, KC_ALT_S, KC_SFT_N, KC_CTL_D, KC_B,        KC_COMM, KC_CTL_A, KC_SFT_E, KC_ALT_I, KC_GUI_H,
                          KC_X,     KC_F,     KC_L,     KC_C,     KC_W,        KC_MINS, KC_U,     KC_O,     KC_Y,     KC_K,
                          TT(_NUM_FN), KC_T, KC_ENT, TD(TD_SMART_SFT), KC_SPC, TT(_NAV)
                          ),
    [_NUM_FN] = LAYOUT(
                       QK_BOOT,   KC_F9,   KC_F8,   KC_F7,  KC_F12,         _______,    KC_7,    KC_8,    KC_9, _______,
                       _______,   KC_F6,   KC_F5,   KC_F4,  KC_F11,         _______,    KC_4,    KC_5,    KC_6, KC_DOT,
                       _______,   KC_F3,   KC_F2,   KC_F1,  KC_F10,         _______,    KC_1,    KC_2,    KC_3, _______,
                       _______, _______, _______, _______, KC_0, _______
                       ),
    [_NAV] = LAYOUT(
                    XXXXXXX,         KC_VOLD,         KC_MUTE,         KC_VOLU, XXXXXXX,       KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
                    KC_LGUI, LALT_T(KC_MPRV), LSFT_T(KC_MPLY), LCTL_T(KC_MNXT), XXXXXXX,       KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
                    XXXXXXX,         XXXXXXX,         KC_MSTP,         XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
                    ),
};

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R',
                  '*', '*', '*',  '*', '*', '*'
    );

typedef struct {
    uint16_t leader;
    uint16_t follow_in;
    uint16_t follow_out;
    bool active;
} adaptive_t;

#define ADAPTIVE(lead, in, out) {.leader = lead, .follow_in = in, .follow_out = out}

adaptive_t adaptives[] = {
    ADAPTIVE(KC_CTL_A, KC_GUI_H, KC_U),
    ADAPTIVE(KC_SFT_E, KC_GUI_H, KC_O),
    ADAPTIVE(KC_U, KC_GUI_H, KC_A),
    ADAPTIVE(KC_O, KC_GUI_H, KC_E),
};

uint16_t adaptive_deadline = 0;
uint16_t adaptive_last_keycode = KC_NO;
uint16_t adaptive_active_in = KC_NO;
uint16_t adaptive_active_out = KC_NO;

#define ADAPTIVES_COUNT sizeof(adaptives) / sizeof(*adaptives)

void process_record_adaptive(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        for (size_t i = 0; i < ADAPTIVES_COUNT; i++) {
            adaptive_t *adaptive = &adaptives[i];
            if (adaptive->leader == adaptive_last_keycode && adaptive->follow_in == keycode) {
                record->keycode = adaptive->follow_out;
                adaptive->active = true;
                adaptive_last_keycode = KC_NO;
                return;
            }
        }

        adaptive_last_keycode = keycode;
        adaptive_deadline = record->event.time + ADAPTIVE_TERM;
    } else {
        for (size_t i = 0; i < ADAPTIVES_COUNT; i++) {
            adaptive_t *adaptive = &adaptives[i];
            if (adaptive->active && adaptive->follow_in == keycode) {
                record->keycode = adaptive->follow_out;
                adaptive->active = false;
                return;
            }
        }
    }
}


void matrix_scan_adaptive(void) {
    if (timer_expired(timer_read(), adaptive_deadline)) {
        adaptive_last_keycode = KC_NO;
    }
}


typedef enum {
    tap,
    tap_tap,
    hold,
} hold_tap_action_t;

typedef void (*hold_tap_user_fn_t)(hold_tap_action_t, bool pressed);

#define ACTION_TAP_HOLD_TAP(hold_tap_user_fn)                           \
    {.fn = { tap_dance_hold_tap_on_each_tap, tap_dance_hold_tap_finished, NULL, tap_dance_hold_tap_release}, .user_data = (void *)((hold_tap_user_fn_t) hold_tap_user_fn) }

void tap_dance_hold_tap_on_each_tap(tap_dance_state_t *state, void *user_data) {
    hold_tap_user_fn_t hold_tap_user_fn = (hold_tap_user_fn_t) user_data;

    if (state->count == 2) {
        hold_tap_user_fn(tap_tap, true);
    }
}

void tap_dance_hold_tap_finished(tap_dance_state_t *state, void *user_data) {
    hold_tap_user_fn_t hold_tap_user_fn = (hold_tap_user_fn_t) user_data;

    if (state->count == 1) {
        if (state->pressed) {
            hold_tap_user_fn(hold, true);
        } else {
            hold_tap_user_fn(tap, true);
            hold_tap_user_fn(tap, false);
        }
    }
}

void tap_dance_hold_tap_release(tap_dance_state_t *state, void *user_data) {
    hold_tap_user_fn_t hold_tap_user_fn = (hold_tap_user_fn_t) user_data;

    if (state->count == 2) {
        hold_tap_user_fn(tap_tap, false);
        state->finished = true;
    } else if (state->finished) {
        hold_tap_user_fn(hold, false);
    }
}

void hold_tap_smart_shift(hold_tap_action_t hold_tap_action, bool pressed) {
    if (pressed) {
        switch(hold_tap_action) {
        case tap: set_oneshot_mods(get_oneshot_mods() ^ MOD_LSFT); break;
        case tap_tap: caps_word_toggle(); break;
        case hold: add_mods(MOD_LSFT); break;
        }
    } else {
        switch(hold_tap_action) {
        case tap: break;
        case tap_tap: break;
        case hold: del_mods(MOD_LSFT); break;
        default: break;
        }
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SMART_SFT] = ACTION_TAP_HOLD_TAP(hold_tap_smart_shift),
};

enum combos {
    COMBO_AMPR = 0,
    COMBO_ASTR,
    COMBO_BRCS,
    COMBO_BSPC,
    COMBO_CBRS,
    COMBO_COLN,
    COMBO_DEL,
    COMBO_DLR,
    COMBO_EQL,
    COMBO_ESC,
    COMBO_GRV,
    COMBO_GT,
    COMBO_LBRC,
    COMBO_LCBR,
    COMBO_LPRN,
    COMBO_LT,
    COMBO_PERC,
    COMBO_PIPE,
    COMBO_PRNS,
    COMBO_Q,
    COMBO_RBRC,
    COMBO_RCBR,
    COMBO_RPRN,
    COMBO_SCLN,
    COMBO_SZ,
    COMBO_TAB,
    COMBO_TILD,
    COMBO_UL_A,
    COMBO_UL_O,
    COMBO_UL_U,
    COMBO_Z,
};


const uint16_t PROGMEM combo_ampr[] = {KC_UNDS, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_astr[] = {KC_SLSH, KC_SFT_E, COMBO_END};
const uint16_t PROGMEM combo_brcs[] = {KC_U, KC_O, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_cbrs[] = {KC_C, KC_L, KC_F, COMBO_END};
const uint16_t PROGMEM combo_coln[] = {KC_CTL_D, KC_B, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_SLSH, KC_UNDS, COMBO_END};
const uint16_t PROGMEM combo_dlr[] = {KC_M, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_eql[] = {KC_SFT_N, KC_L, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {KC_CTL_D, KC_C, COMBO_END};
const uint16_t PROGMEM combo_lbrc[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM combo_lcbr[] = {KC_C, KC_L, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {KC_CTL_A, KC_SFT_E, COMBO_END};
const uint16_t PROGMEM combo_lt[] = {KC_ALT_S, KC_F, COMBO_END};
const uint16_t PROGMEM combo_perc[] = {KC_B, KC_W, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_ALT_I, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_prns[] = {KC_CTL_A, KC_SFT_E, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_q[] = {KC_G, KC_ALT_S, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_O, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_rcbr[] = {KC_L, KC_F, COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {KC_SFT_E, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_scln[] = {KC_COMM, KC_CTL_A, COMBO_END};
const uint16_t PROGMEM combo_sz[] = {KC_GUI_R, KC_J, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_ALT_S, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_tild[] = {KC_P, KC_CTL_D, COMBO_END};
const uint16_t PROGMEM combo_ul_a[] = {KC_DOT, KC_CTL_A, COMBO_END};
const uint16_t PROGMEM combo_ul_o[] = {KC_SFT_E, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ul_u[] = {KC_CTL_A, KC_U, COMBO_END};
const uint16_t PROGMEM combo_z[] = {KC_J, KC_GUI_R, COMBO_END};

combo_t key_combos[] = {
    [COMBO_AMPR] = COMBO(combo_ampr, KC_AMPR),
    [COMBO_ASTR] = COMBO(combo_astr, KC_ASTR),
    [COMBO_BRCS] = COMBO(combo_brcs, KC_BRCS),
    [COMBO_BSPC] = COMBO(combo_bspc, KC_BSPC),
    [COMBO_CBRS] = COMBO(combo_cbrs, KC_CBRS),
    [COMBO_COLN] = COMBO(combo_coln, KC_COLN),
    [COMBO_DEL] = COMBO(combo_del, KC_DEL),
    [COMBO_DLR] = COMBO(combo_dlr, KC_DLR),
    [COMBO_EQL] = COMBO(combo_eql, KC_EQL),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_GRV] = COMBO(combo_grv, KC_GRV),
    [COMBO_GT] = COMBO(combo_gt, KC_GT),
    [COMBO_LBRC] = COMBO(combo_lbrc, KC_LBRC),
    [COMBO_LCBR] = COMBO(combo_lcbr, KC_LCBR),
    [COMBO_LPRN] = COMBO(combo_lprn, KC_LPRN),
    [COMBO_LT] = COMBO(combo_lt, KC_LT),
    [COMBO_PERC] = COMBO(combo_perc, KC_PERC),
    [COMBO_PIPE] = COMBO(combo_pipe, KC_PIPE),
    [COMBO_PRNS] = COMBO(combo_prns, KC_PRNS),
    [COMBO_Q] = COMBO(combo_q, KC_Q),
    [COMBO_RBRC] = COMBO(combo_rbrc, KC_RBRC),
    [COMBO_RPRN] = COMBO(combo_rprn, KC_RPRN),
    [COMBO_RCBR] = COMBO(combo_rcbr, KC_RCBR),
    [COMBO_SCLN] = COMBO(combo_scln, KC_SCLN),
    [COMBO_SZ] = COMBO(combo_sz, KC_SZ),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_TILD] = COMBO(combo_tild, KC_TILD),
    [COMBO_UL_A] = COMBO(combo_ul_a, KC_UL_A),
    [COMBO_UL_O] = COMBO(combo_ul_o, KC_UL_O),
    [COMBO_UL_U] = COMBO(combo_ul_u, KC_UL_U),
    [COMBO_Z] = COMBO(combo_z, KC_Z),
};

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
    case COMBO_TAB:
    case COMBO_LPRN:
    case COMBO_RPRN:
    case COMBO_PRNS:
    case COMBO_LCBR:
    case COMBO_RCBR:
    case COMBO_CBRS:
        return true;
    default:
        return false;
    }
}

uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    switch(combo_index) {
    case COMBO_Z:
    case COMBO_Q:
    case COMBO_SCLN:
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

const key_override_t at_override = ko_make_basic(MOD_MASK_SHIFT, KC_HASH, KC_AT);
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_EXLM);
const key_override_t backslash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_CIRC);
const key_override_t question_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUES);
const key_override_t plus_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_PLUS);
const key_override_t euro_override = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, RALT(KC_5));

const key_override_t *key_overrides[] = {
    &at_override,
    &exclamation_mark_override,
    &backslash_override,
    &circ_override,
    &question_mark_override,
    &plus_override,
    &euro_override,
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
    case KC_A ... KC_Z:
    case KC_UL_A:
    case KC_UL_O:
    case KC_UL_U:
    case KC_SZ:
    case TD(TD_SMART_SFT):
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
    process_record_adaptive(keycode, record);

    if (!record->event.pressed) switch (keycode) {
    case KC_PRNS:
        tap_code16(KC_LPRN);
        tap_code16(KC_RPRN);
        break;

    case KC_BRCS:
        tap_code16(KC_LBRC);
        tap_code16(KC_RBRC);
        break;

    case KC_CBRS:
        tap_code16(KC_LCBR);
        tap_code16(KC_RCBR);
        break;
    }
    return true;
}

void matrix_scan_user(void) {
    matrix_scan_adaptive();
}
