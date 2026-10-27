/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Hand configuration (MASTER_LEFT/RIGHT) is set by the userspace from POINTING_DEVICE */

// Home-row mods, ported from the ZMK "balanced" hold-taps. Vial's QMK Settings tab can
// retune these at runtime; the values here are the defaults after a flash.
#define TAPPING_TERM 280
#define QS_TAPPING_DEFAULT (1 | 2) // permissive hold on, hold-on-other-key-press off
#define CHORDAL_HOLD               // same-hand chords resolve as taps (ZMK hold-trigger-key-positions)
#define HRM_PRIOR_IDLE_MS 150      // ZMK require-prior-idle-ms: fast typing forces taps

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Vial configuration
#define VIAL_KEYBOARD_UID {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x01, 0x23}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

// Underglow: 6 LEDs per half, synced over TRRS
#define RGBLED_SPLIT { 6, 6 }
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 150   // cap brightness to keep current draw sane
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

// Layer colours and feedback flashes (see rgb_layers in keymap.c)
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYERS_RETAIN_VAL       // layer colours follow the brightness setting
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // and still show when the underglow is switched off
#define RGBLIGHT_MAX_LAYERS 12
