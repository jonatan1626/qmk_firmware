/* Copyright 2019 MechMerlin
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

rgblight_config_t RGB_current_config;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

void copyrgb(LED_TYPE *src, LED_TYPE *dst);

LED_TYPE led_save[RGBLED_NUM];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( \
        KC_ESC,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DEL, \
        KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,          \
        KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN,                  \
        KC_LSFT, KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_TILD,         \
        KC_LCTL, KC_LALT, KC_LGUI,               KC_SPC, KC_SPC, KC_SPC,         KC_RGUI, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT                   \
    ),
[1] = LAYOUT( \
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_MUTE, \
        KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_TRNS,          \
        KC_TRNS, RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU,                   \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_VOLD,          \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END                     \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void LED_default_set(void) {
    sethsv(HSV_TEAL, (LED_TYPE *)&led[0]);
    sethsv(HSV_TEAL, (LED_TYPE *)&led[1]);
    sethsv(HSV_TEAL, (LED_TYPE *)&led[2]);
    sethsv(HSV_TEAL, (LED_TYPE *)&led[3]);
    sethsv(HSV_TEAL, (LED_TYPE *)&led[4]);
    sethsv(HSV_TEAL, (LED_TYPE *)&led[5]);

    rgblight_set();
}


void matrix_init_user(void) {
    LED_default_set();
}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(E6);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[0]);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[1]);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[2]);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[3]);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[4]);
        // sethsv(HSV_ORANGE, (LED_TYPE *)&led[5]);
        rgblight_mode(13);
        rgblight_set();
    } else {
        writePinHigh(E6);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[0]);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[1]);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[2]);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[3]);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[4]);
        sethsv(HSV_TEAL, (LED_TYPE *)&led[5]);
        rgblight_mode(2);
        rgblight_set();
    }
}
