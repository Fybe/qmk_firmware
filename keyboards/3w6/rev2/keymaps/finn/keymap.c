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
    _HANDSDOWN = 0,
    _NAV,
    _NUM,
    _FN,
};

enum custom_keycodes {
    KC_RARR = SAFE_RANGE,

    KC_DIGRAPH_TH,
    KC_DIGRAPH_CH,
    KC_DIGRAPH_SH,
    KC_DIGRAPH_WH,
    KC_DIGRAPH_GH,
    KC_DIGRAPH_PH,

    KC_PRNS,
    KC_BRCS,
    KC_CBRS,

    KC_SMART_NUM,
};

enum tap_dance {
    TD_SMART_SFT = 0,
    TD_NUM_NAV,
};


#define KC_GUI_S LGUI_T(KC_S)
#define KC_ALT_C LALT_T(KC_C)
#define KC_SFT_N LSFT_T(KC_N)
#define KC_CTL_T LCTL_T(KC_T)

#define KC_CTL_A LCTL_T(KC_A)
#define KC_SFT_E LSFT_T(KC_E)
#define KC_ALT_I LALT_T(KC_I)
#define KC_GUI_H LGUI_T(KC_H)

#define KC_UL_A RALT(KC_QUOT)
#define KC_UL_O RALT(KC_SCLN)
#define KC_UL_U RALT(KC_LBRC)
#define KC_SZ RALT(KC_MINS)

/*

  +---+---+---+---+---+                 +---+---+---+---+---+
  | X | W | M | G | J |                 |# @|. !|/ \|_ ^|' "|
  +---+---+---+---+---+                 +---+---+---+---+---+
  | S | C | N | T | K |                 |, ?| A | E | I | H |
  +---+---+---+---+---+                 +---+---+---+---+---+
  | B | P | L | D | V |                 |- +| U | O | Y | F |
  +---+---+---+---+---+                 +---+---+---+---+---+
             +---+---+---+           +---+---+---+
             |NUM| R |ENT|           |SFT|SPC| ⋆ |
             +---+---+   |           |   +---+---+
                     +---+           +---+

  +---+---+---+---+---+                 +---+---+---+---+---+
  |   |  ESC  gh  |   |                 |   |  BSP DEL  |   |
  + Z + Q + $ + ~ + ` +                 +---+ ä + * + & +---+
  |   |  TAB  th  :   |                 |   ;   (   )   |   |
  + ß + > + = + < + % +                 +---+ ü + ö + | +---+
  |   |   }   {   |   |                 |   |   [   ]   |   |
  +---+---+---+---+---+                 +---+---+---+---+---+
             +---+---+---+           +---+---+---+
             |NAV|   |   |           |   |   |   |
             +---+---+   |           |   +---+---+
                     +---+           +---+

 */


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_HANDSDOWN] = LAYOUT(
        KC_X,     KC_W,     KC_M,     KC_G,     KC_J,        KC_HASH, KC_DOT,   KC_SLSH,  KC_UNDS,  KC_QUOT,
        KC_GUI_S, KC_ALT_C, KC_SFT_N, KC_CTL_T, KC_K,        KC_COMM, KC_CTL_A, KC_SFT_E, KC_ALT_I, KC_GUI_H,
        KC_B,     KC_P,     KC_L,     KC_D,     KC_V,        KC_MINS, KC_U,     KC_O,     KC_Y,     KC_F,
                      TD(TD_NUM_NAV), KC_R, KC_ENT, TD(TD_SMART_SFT), KC_SPC, QK_LEAD
    ),
    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______,
           KC_7,    KC_5,    KC_3,    KC_1, _______,         _______,    KC_0,    KC_2,    KC_4,    KC_6,
        _______, _______, _______,    KC_9, _______,         _______,    KC_8, _______, _______, _______,
                             TG(_NUM), _______, _______, _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,         KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_DEL,
        KC_LGUI, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,         KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_END,
        XXXXXXX, XXXXXXX, KC_MSTP, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),
    [_FN] = LAYOUT(
         KC_F11,   KC_F9,   KC_F7,   KC_F5,   KC_F3,           KC_F4,   KC_F6,   KC_F8,  KC_F10,  KC_F12,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   KC_F1,           KC_F2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
    ),
};

typedef enum {
    tap,
    tap_tap,
    hold,
} hold_tap_action_t;

typedef void (*hold_tap_user_fn_t)(hold_tap_action_t, bool pressed);

#define ACTION_TAP_HOLD_TAP(hold_tap_user_fn) \
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

void hold_tap_num_nav(hold_tap_action_t hold_tap_action, bool pressed) {
    if (pressed) {
        switch(hold_tap_action) {
        case tap: layer_on(_NUM); break;
        case tap_tap: layer_on(_FN); break;
        case hold: layer_on(_NAV); break;
        }
    } else {
        switch(hold_tap_action) {
        case tap: break;
        case tap_tap: layer_off(_FN); break;
        case hold: layer_off(_NAV); break;
        }
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SMART_SFT] = ACTION_TAP_HOLD_TAP(hold_tap_smart_shift),
    [TD_NUM_NAV]   = ACTION_TAP_HOLD_TAP(hold_tap_num_nav),
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

    COMBO_DIGRAPH_CH,
    COMBO_DIGRAPH_GH,
    COMBO_DIGRAPH_PH,
    COMBO_DIGRAPH_SH,
    COMBO_DIGRAPH_TH,
    COMBO_DIGRAPH_WH,
};

  /* +---+---+---+---+---+                 +---+---+---+---+---+ */
  /* |   |  ESC  gh  |   |                 |   |  BSP DEL  |   | */
  /* + Z + Q + $ + ~ + ` +                 +---+ ä + * + & +---+ */
  /* |   |  TAB  th  :   |                 |   ;   (   )   |   | */
  /* + ß + > + = + < + % +                 +---+ ü + ö + | +---+ */
  /* |   |   }   {   |   |                 |   |   [   ]   |   | */
  /* +---+---+---+---+---+                 +---+---+---+---+---+ */


const uint16_t PROGMEM combo_ampr[] = {KC_UNDS, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_astr[] = {KC_SLSH, KC_SFT_E, COMBO_END};
const uint16_t PROGMEM combo_brcs[] = {KC_U, KC_O, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_cbrs[] = {KC_D, KC_L, KC_P, COMBO_END};
const uint16_t PROGMEM combo_coln[] = {KC_CTL_T, KC_K, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_SLSH, KC_UNDS, COMBO_END};
const uint16_t PROGMEM combo_dlr[] = {KC_M, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_eql[] = {KC_SFT_N, KC_L, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_M, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {KC_ALT_C, KC_P, COMBO_END};
const uint16_t PROGMEM combo_lbrc[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM combo_lcbr[] = {KC_D, KC_L, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {KC_CTL_A, KC_SFT_E, COMBO_END};
const uint16_t PROGMEM combo_lt[] = {KC_CTL_T, KC_D, COMBO_END};
const uint16_t PROGMEM combo_perc[] = {KC_K, KC_V, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_ALT_I, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_prns[] = {KC_CTL_A, KC_SFT_E, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_q[] = {KC_W, KC_ALT_C, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_O, KC_Y, COMBO_END};
const uint16_t PROGMEM combo_rcbr[] = {KC_L, KC_P, COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {KC_SFT_E, KC_ALT_I, COMBO_END};
const uint16_t PROGMEM combo_scln[] = {KC_COMM, KC_CTL_A, COMBO_END};
const uint16_t PROGMEM combo_sz[] = {KC_GUI_S, KC_B, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_ALT_C, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_tild[] = {KC_G, KC_CTL_T, COMBO_END};
const uint16_t PROGMEM combo_ul_a[] = {KC_DOT, KC_CTL_A, COMBO_END};
const uint16_t PROGMEM combo_ul_o[] = {KC_SFT_E, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ul_u[] = {KC_CTL_A, KC_U, COMBO_END};
const uint16_t PROGMEM combo_z[] = {KC_X, KC_GUI_S, COMBO_END};

const uint16_t PROGMEM combo_digraph_ch[] = {KC_ALT_C, KC_CTL_T, COMBO_END};
const uint16_t PROGMEM combo_digraph_gh[] = {KC_M, KC_G, COMBO_END};
const uint16_t PROGMEM combo_digraph_ph[] = {KC_P, KC_D, COMBO_END};
const uint16_t PROGMEM combo_digraph_sh[] = {KC_GUI_S, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_digraph_th[] = {KC_CTL_T, KC_SFT_N, COMBO_END};
const uint16_t PROGMEM combo_digraph_wh[] = {KC_W, KC_G, COMBO_END};

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

    [COMBO_DIGRAPH_CH] = COMBO(combo_digraph_ch, KC_DIGRAPH_CH),
    [COMBO_DIGRAPH_GH] = COMBO(combo_digraph_gh, KC_DIGRAPH_GH),
    [COMBO_DIGRAPH_PH] = COMBO(combo_digraph_ph, KC_DIGRAPH_PH),
    [COMBO_DIGRAPH_SH] = COMBO(combo_digraph_sh, KC_DIGRAPH_SH),
    [COMBO_DIGRAPH_TH] = COMBO(combo_digraph_th, KC_DIGRAPH_TH),
    [COMBO_DIGRAPH_WH] = COMBO(combo_digraph_wh, KC_DIGRAPH_WH),
};

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    switch (combo_index) {
    case COMBO_DIGRAPH_TH:
    case COMBO_DIGRAPH_CH:
    case COMBO_DIGRAPH_SH:
    case COMBO_DIGRAPH_WH:
    case COMBO_DIGRAPH_GH:
    case COMBO_DIGRAPH_PH:
    case COMBO_TAB:
    case COMBO_LPRN:
    case COMBO_RPRN:
    case COMBO_PRNS:
        return true;
    default:
        return false;
    }
}

const key_override_t at_override = ko_make_basic(MOD_MASK_SHIFT, KC_HASH, KC_AT);
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_EXLM);
const key_override_t backslash_override = ko_make_basic(MOD_MASK_SHIFT, KC_SLSH, KC_BSLS);
const key_override_t circ_override = ko_make_basic(MOD_MASK_SHIFT, KC_UNDS, KC_CIRC);
const key_override_t question_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_QUES);
const key_override_t plus_override = ko_make_basic(MOD_MASK_SHIFT, KC_MINS, KC_PLUS);

const key_override_t *key_overrides[] = {
    &at_override,
    &exclamation_mark_override,
    &backslash_override,
    &circ_override,
    &question_mark_override,
    &plus_override,
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
    case KC_A ... KC_Z:
    case KC_UL_A:
    case KC_UL_O:
    case KC_UL_U:
    case KC_SZ:
    case KC_DIGRAPH_TH ... KC_DIGRAPH_PH:
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

bool num_layer_press_user(uint16_t keycode) {
    switch (keycode) {
    case KC_1 ... KC_0:
    case KC_MINS:
    case KC_ASTR:
    case KC_PLUS:
    case KC_SLSH:
    case KC_DOT:
    case KC_COMM:
    case KC_BSPC:
    case KC_DEL:
    case TG(_NUM):
        return true;
    default:
        return false;
    }
}

void leader_start_user(void) {}
void leader_end_user(void) {
    if (leader_sequence_four_keys(KC_B, KC_O, KC_O, KC_T)) {
        reset_keyboard();
    } else if (leader_sequence_five_keys(KC_R, KC_E, KC_S, KC_E, KC_T)) {
        soft_reset_keyboard();
    }
}

/* TODO: Activity state per adaptive key */
typedef struct {
    uint16_t leader;
    uint16_t adaptive;
    uint16_t replacement;
} adaptive_t;

bool adaptive_key_enabled = true;
uint32_t adaptive_key_deadline;
uint16_t adaptive_key_leader;
uint16_t adaptive_key_input;
uint16_t adaptive_key_output;

adaptive_t adaptive_keys[] = {
    {KC_CTL_A, KC_GUI_H, LGUI_T(KC_U)},
    {KC_SFT_E, KC_GUI_H, LGUI_T(KC_O)},
    {KC_G, KC_M, KC_L},
    {KC_CTL_T, KC_X, KC_Z},
    {KC_UL_A, KC_GUI_H, LGUI_T(KC_U)},
};
#define ADAPTIVE_KEYS_COUNT sizeof(adaptive_keys) / sizeof(*adaptive_keys)

bool adaptive_fire(uint16_t keycode, keyrecord_t *record) {
    if (!adaptive_key_enabled) return true;

    if (record->event.pressed) {
        for (uint8_t i = 0; i < ADAPTIVE_KEYS_COUNT; i++) {
            adaptive_t *adaptive = &adaptive_keys[i];

            if (adaptive->leader == adaptive_key_leader && adaptive->adaptive == keycode) {
                record->keycode = adaptive->replacement;

                adaptive_key_enabled = false;
                process_record(record);
                adaptive_key_enabled = true;

                adaptive_key_leader = KC_NO;
                adaptive_key_input = keycode;
                adaptive_key_output = adaptive->replacement;
                return false;
            }
        }
    } else {
        if (keycode == adaptive_key_input) {
            record->keycode = adaptive_key_output;

            adaptive_key_enabled = false;
            process_record(record);
            adaptive_key_enabled = true;

            adaptive_key_input = KC_NO;
            adaptive_key_output = KC_NO;

            return false;
        }
    }

    return true;
}

void adaptive_prime(uint16_t keycode, keyrecord_t *record) {
    if (!adaptive_key_enabled) return;

    if (record->event.pressed) {
        adaptive_key_leader = keycode;
        adaptive_key_deadline = record->event.time + ADAPTIVE_TERM;
    }
}

void adaptive_scan(uint16_t time) {
    if (timer_expired(time, adaptive_key_deadline))
        adaptive_key_leader = KC_NO;
}

#define TAP_DIGRAPH(kc0, kc1)                                           \
    if (is_caps_word_on()) add_weak_mods(MOD_MASK_SHIFT);              \
    tap_code(kc0);                                                      \
    del_mods(MOD_MASK_SHIFT);                                           \
    tap_code(kc1)


uint16_t last_keypress = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (layer_state_is(_NUM) && !num_layer_press_user(keycode)) {
        layer_off(_NUM);
    }

    if (!adaptive_fire(keycode, record)) return false;
    adaptive_prime(keycode, record);

    if (!record->event.pressed) {
        return true;
    }

    uint16_t mods = get_mods();
    uint16_t weak_mods = get_weak_mods();
    uint16_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
    case KC_RARR:
        clear_mods();
        clear_weak_mods();

        tap_code(KC_SPC);
        tap_code(KC_MINS);
        tap_code16(KC_RABK);
        tap_code(KC_SPC);
        break;

    case KC_DIGRAPH_TH:
        TAP_DIGRAPH(KC_T, KC_H);
        break;

    case KC_DIGRAPH_CH:
        TAP_DIGRAPH(KC_C, KC_H);
        break;

    case KC_DIGRAPH_SH:
        TAP_DIGRAPH(KC_S, KC_H);
        break;

    case KC_DIGRAPH_WH:
        TAP_DIGRAPH(KC_W, KC_H);
        break;

    case KC_DIGRAPH_GH:
        TAP_DIGRAPH(KC_G, KC_H);
        break;

    case KC_DIGRAPH_PH:
        TAP_DIGRAPH(KC_P, KC_H);
        break;

    case KC_PRNS:
        tap_code16(KC_LPRN);
        tap_code16(KC_RPRN);
        break;

    case KC_BRCS:
        tap_code16(KC_LBRC);
        set_oneshot_mods(oneshot_mods);
        tap_code16(KC_RBRC);
        break;

    case KC_CBRS:
        tap_code16(KC_LCBR);
        set_oneshot_mods(oneshot_mods);
        tap_code16(KC_RCBR);
        break;
    }
    set_weak_mods(weak_mods);
    set_mods(mods);
    return true;
}

void matrix_scan_user() {
    uint16_t time = timer_read();
    adaptive_scan(time);
}
