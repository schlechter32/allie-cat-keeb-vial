 /* Copyright 2020 Naoki Katahira
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

// Port of the ZMK corne keymap (zmk-config/config/corne.keymap) to the Lily58.
// The Lily58-only keys (number row, inner keys, outer thumbs) carry the extras.

#include QMK_KEYBOARD_H
#include "holykeebs.h"

enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST, // LOWER + RAISE
  _PLAIN,  // no home-row mods, toggled from RAISE
  _SPARE,  // free for Vial
};

// Home-row mods (ZMK hmmod / hmmodr / hmlayer / hmlayerr)
#define HM_A    LCTL_T(KC_A)
#define HM_S    LGUI_T(KC_S)
#define HM_D    LALT_T(KC_D)
#define HM_F    LT(_LOWER, KC_F)
#define HM_G    LT(_RAISE, KC_G)
#define HM_H    LT(_RAISE, KC_H)
#define HM_J    LT(_LOWER, KC_J)
#define HM_K    LALT_T(KC_K)
#define HM_L    RGUI_T(KC_L)
#define HM_SCLN RCTL_T(KC_SCLN)

// Pinky shifts (ZMK pinkyshiftL / pinkyshiftR)
#define PS_TAB  LSFT_T(KC_TAB)
#define PS_ENT  RSFT_T(KC_ENT)

// Ctrl+Alt+Shift holds (ZMK SpaceMeh / slash)
#define MEH_SPC MEH_T(KC_SPC)
#define MEH_SLS MEH_T(KC_SLSH)

// Held Ctrl+Shift on the inner keys: fixes Ctrl (A) + Shift (Tab) both being on the left pinky
#define CS_HOLD LCTL(KC_LSFT)

// LOWER mod-taps whose tap is a shifted symbol; the tap is sent in process_record_keymap
#define LM_PLUS LCTL_T(KC_EQL)
#define LM_CIRC LALT_T(KC_6)
#define LM_DLR  LGUI_T(KC_4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_BASE] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  PS_TAB,  HM_A,    HM_S,    HM_D,    HM_F,    HM_G,                       HM_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, PS_ENT,
  KC_DEL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    CS_HOLD, CS_HOLD,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, MEH_SLS,
                    MS_BTN1, KC_RALT, MO(_LOWER), MEH_SPC,      C(KC_BSPC), MO(_RAISE), KC_RALT, MS_BTN2
),

 [_LOWER] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, KC_UNDS, LM_PLUS, LM_CIRC, LM_DLR,  _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_END,  _______,
  _______, KC_TILD, HK_D_MODE, MS_BTN3, HK_S_MODE, KC_F11, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PGUP, _______,
                    _______, _______, _______, _______,                    _______, _______, _______, _______
),

 [_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, KC_AT,   KC_EXLM, KC_LCBR, KC_RCBR, KC_AMPR,                    KC_CIRC, KC_7,    KC_8,    KC_9,    KC_DLR,  _______,
  _______, KC_MINS, KC_BSLS, KC_LPRN, KC_RPRN, KC_ASTR,                    KC_0,    KC_4,    KC_5,    KC_6,    KC_EQL,  _______,
  _______, KC_GRV,  KC_HASH, KC_LBRC, KC_RBRC, KC_PERC, _______, _______,  KC_PIPE, KC_1,    KC_2,    KC_3,    KC_COMM, _______,
                    _______, TO(_PLAIN), _______, _______,                 _______, _______, _______, _______
),

// Pointer speed: hold DPI / DPI snipe / scroll buffer and press Down / Up. HK_SAVE keeps it.
 [_ADJUST] = LAYOUT(
  QK_CLEAR_EEPROM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  QK_BOOT, UG_TOGG, UG_NEXT, UG_HUED, UG_HUEU, HK_C_SCROLL,               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  XXXXXXX, HK_P_SET_D, HK_P_SET_S, HK_P_SET_BUF, HK_SAVE, HK_S_MODE_T,    XXXXXXX, KC_DOWN, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
  KC_LSFT, UG_VALD, UG_VALU, UG_SATD, UG_SATU, HK_D_MODE_T, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, HK_RESET, HK_DUMP, XXXXXXX,
                    _______, _______, _______, _______,                   _______, _______, _______, _______
),

 [_PLAIN] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    _______,
  _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  _______, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT, _______,
                    _______, TO(_BASE), _______, _______,                  _______, _______, _______, _______
),

 [_SPARE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,
                    _______, _______, _______, _______,                    _______, _______, _______, _______
)
};

// Thumbs are '*' so they can trigger holds on either hand (ZMK lists the space thumb on both sides).
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM = LAYOUT(
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L',                'R', 'R', 'R', 'R', 'R', 'R',
  'L', 'L', 'L', 'L', 'L', 'L', 'L',      'R', 'R', 'R', 'R', 'R', 'R', 'R',
                 '*', '*', '*', '*',      '*', '*', '*', '*'
);

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// ZMK require-prior-idle-ms: a home-row key pressed within HRM_PRIOR_IDLE_MS of the previous
// typed key is forced to its tap keycode, so fast rolls never produce a modifier.
static uint16_t last_typed_time;
static bool     typing_streak;
static uint8_t  forced_tap[MATRIX_ROWS][MATRIX_COLS];

static uint8_t hrm_tap_keycode(uint16_t keycode) {
  if (keycode == PS_TAB || keycode == PS_ENT) {
    return KC_NO; // pinky shifts had no prior-idle in ZMK
  }
  if (IS_QK_MOD_TAP(keycode)) {
    keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
  } else if (IS_QK_LAYER_TAP(keycode)) {
    keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
  } else {
    return KC_NO;
  }
  switch (keycode) {
    case KC_A ... KC_Z:
    case KC_SCLN:
    case KC_SLSH:
    case KC_SPC:
      return keycode;
  }
  return KC_NO;
}

static void mark_typed(void) {
  last_typed_time = timer_read();
  typing_streak   = true;
}

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.type != KEY_EVENT) {
    return true;
  }
  uint8_t row = record->event.key.row;
  uint8_t col = record->event.key.col;

  if (!record->event.pressed) {
    if (forced_tap[row][col]) {
      record->keycode       = forced_tap[row][col];
      forced_tap[row][col]  = KC_NO;
    }
    return true;
  }

  uint8_t tap = hrm_tap_keycode(keycode);
  if (tap != KC_NO) {
    if (typing_streak && timer_elapsed(last_typed_time) < HRM_PRIOR_IDLE_MS) {
      record->keycode      = tap;
      forced_tap[row][col] = tap;
      mark_typed();
    }
  } else if (keycode >= KC_A && keycode <= KC_SLASH) {
    mark_typed();
  } else {
    typing_streak = false;
  }
  return true;
}

static bool tap_shifted(uint16_t keycode, keyrecord_t *record) {
  if (record->tap.count && record->event.pressed) {
    tap_code16(keycode);
    return false;
  }
  return true;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  // A home-row key that resolved as a tap continues the typing streak.
  if (record->event.pressed && record->tap.count && hrm_tap_keycode(keycode) != KC_NO) {
    mark_typed();
  }

  switch (keycode) {
    case LM_PLUS: return tap_shifted(KC_PLUS, record);
    case LM_CIRC: return tap_shifted(KC_CIRC, record);
    case LM_DLR:  return tap_shifted(KC_DLR, record);
  }
  return true;
}
