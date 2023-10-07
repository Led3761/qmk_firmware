#include QMK_KEYBOARD_H
#include <stdbool.h>
//Debug
#include "print.h"

// Define colors for Layers
#define NO_USB_CONNECTION_HSV_COLOR HSV_WHITE
#define ENG_HSV_COLOR HSV_SPRINGGREEN
#define RUS_HSV_COLOR HSV_GOLD
#define FN_HSV_COLOR HSV_MAGENTA

// Define language switch key combination
#define LANG_SWITCH LWIN(KC_SPACE)

// Defines names for use in layer keycodes and the keymap
enum jiran_layers {
  _ENG,
  _RUS,
  _FN
};

// Define my custom keycodes
enum my_keycodes {
  ENG_KC_SCLN = SAFE_RANGE, // Custom keycode KC_SCLN (;/:) for RUS language
  POINTER_ARROW // Keycode for arrow (->)
};

bool keyboard_usb_connected = false;
// Remember backlight state before turn off on suspend
bool backlight_suspend_state = true;
// Set to true when suspend_power_down_user called first time
// reset to false after wake up. Use for set backlight_suspend_state once
bool power_down_flag = false;
// Disable lang switch on layer change
bool disable_lang_switch = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_ENG] = LAYOUT(
      KC_ESC,
      KC_7,
      KC_5,
      KC_3,
      KC_1,
      KC_9,
      KC_0,
      KC_2,
      KC_4,
      KC_6,
      KC_8,
      KC_EQL,
      KC_DEL,
      KC_TAB,
      KC_Q,
      KC_G,
      KC_M,
      KC_L,
      KC_W,
      KC_B,
      KC_Y,
      KC_U,
      KC_V,
      KC_NO,
      KC_NO,
      KC_SCLN,
      KC_LALT,
      KC_D,
      KC_S,
      KC_T,
      KC_N,
      KC_R,
      KC_I,
      KC_A,
      KC_E,
      KC_O,
      KC_H,
      KC_NO,
      KC_LCTL,
      KC_Z,
      KC_X,
      KC_C,
      KC_F,
      KC_J,
      KC_K,
      KC_P,
      KC_NO,
      KC_NO,
      KC_COMM,
      KC_DOT,
      LT(0,KC_LGUI),
      LT(0,KC_LSFT),
      KC_SPC,
      KC_BSPC,
      MO(2),
      KC_ENT
    ), 

    [_RUS] = LAYOUT(
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_Q,
      KC_W,
      KC_E,
      KC_T,
      KC_A,
      KC_O,
      KC_U,
      KC_N,
      KC_Y,
      KC_P,
      KC_LBRC,
      (ENG_KC_SCLN),
      KC_TRNS,
      KC_R,
      KC_V,
      KC_D,
      KC_F,
      KC_G,
      KC_H,
      KC_J,
      KC_K,
      KC_L,
      KC_SCLN,
      KC_QUOT,
      KC_LCTL,
      KC_Z,
      KC_X,
      KC_C,
      KC_B,
      KC_S,
      KC_I,
      KC_M,
      KC_COMM,
      KC_DOT,
      LSFT(KC_SLSH),
      KC_SLSH,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      KC_TRNS
  ),

  [_FN] = LAYOUT(
      KC_GRV,
      KC_F7,
      KC_F5,
      KC_F3,
      KC_F1,
      KC_F9,
      KC_F10,
      KC_F2,
      KC_F4,
      KC_F6,
      KC_F8,
      KC_MINS,
      KC_F11,
      KC_TRNS,
      RGB_TOG,
      KC_MPLY,
      KC_QUOT,
      KC_LT,
      KC_GT,
      KC_LBRC,
      KC_HOME,
      KC_PGUP,
      KC_END,
      KC_PGDN,
      KC_SLSH,
      KC_F12,
      KC_TRNS,
      BL_TOGG,
      KC_MNXT,
      KC_UNDS,
      KC_LPRN,
      KC_RPRN,
      KC_RBRC,
      KC_LEFT,
      KC_UP,
      KC_RGHT,
      KC_DOWN,
      LCTL(KC_SLSH),
      KC_TRNS,
      BL_STEP,
      KC_MPRV,
      KC_PSCR,
      LSFT(KC_PSCR),
      KC_BSLS,
      LCTL(KC_ENT),
      LCTL(KC_LEFT),
      LCTL(KC_UP),
      LCTL(KC_RGHT),
      LCTL(KC_DOWN),
      (POINTER_ARROW),
      KC_LGUI,
      KC_TRNS,
      KC_TRNS,
      LCTL(KC_BSPC),
      KC_TRNS,
      LCTL(KC_ENT)
  ),
};

// Create combos
const uint16_t PROGMEM hard_sign_combo [] = {KC_J, KC_M, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(hard_sign_combo, KC_RIGHT_BRACKET),
};
// Create key overrides
const key_override_t ctrl_shift_c_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_C, RCTL(KC_V), ~0);
// Override ctrl+c and ctrl+v key combination for FN layout
const key_override_t ctrl_c_fn_key_override = 
  ko_make_with_layers_and_negmods(MOD_MASK_CTRL	, KC_PSCR, RCTL(KC_INSERT), ~0, MOD_MASK_SHIFT);
const key_override_t ctrl_shift_c_fn_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_PSCR, RSFT(KC_INSERT), ~0);
// Overrides default ctrl key combination for RUS layout
const key_override_t ctrl_f_rus_key_override = 
  ko_make_with_layers(MOD_MASK_CTRL	, KC_B, LCTL(KC_F), (1 << _RUS));
const key_override_t ctrl_n_rus_key_override = 
  ko_make_with_layers(MOD_MASK_CTRL	, KC_F, LCTL(KC_N), (1 << _RUS));
const key_override_t ctrl_a_rus_key_override = 
  ko_make_with_layers(MOD_MASK_CTRL	, KC_J, LCTL(KC_A), (1 << _RUS));
const key_override_t ctrl_r_rus_key_override = 
  ko_make_with_layers(MOD_MASK_CTRL	, KC_G, LCTL(KC_R), (1 << _RUS));
const key_override_t ctrl_s_rus_key_override = 
  ko_make_with_layers_and_negmods(MOD_MASK_CTRL	, KC_V, LCTL(KC_S), (1 << _RUS), MOD_MASK_SHIFT);
const key_override_t ctrl_shift_s_rus_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_V, LSFT(LCTL(KC_S)), (1 << _RUS));
const key_override_t ctrl_shift_b_rus_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_O, LSFT(LCTL(KC_B)), (1 << _RUS));

const key_override_t **key_overrides = (const key_override_t *[]){
    &ctrl_shift_c_key_override,
    &ctrl_c_fn_key_override,
    &ctrl_shift_c_fn_key_override,
    &ctrl_f_rus_key_override,
    &ctrl_n_rus_key_override,
    &ctrl_a_rus_key_override,
    &ctrl_r_rus_key_override,
    &ctrl_s_rus_key_override,
    &ctrl_shift_s_rus_key_override,
    &ctrl_shift_b_rus_key_override,
    NULL // Null terminate the array of overrides!
};

void keyboard_post_init_user(void) {
  backlight_enable();
  rgblight_sethsv_noeeprom(NO_USB_CONNECTION_HSV_COLOR);
}

void matrix_scan_user(void) {
  if (!keyboard_usb_connected) {
    keyboard_usb_connected = true;
    rgblight_sethsv_noeeprom(ENG_HSV_COLOR);
  }
}

void suspend_power_down_user(void) {
  // Code will run multiple times while keyboard is suspended
  if (!power_down_flag) {
    power_down_flag = true;
    backlight_suspend_state = is_backlight_enabled();

    backlight_disable();
    rgblight_suspend();
  }
}

void suspend_wakeup_init_user(void) {
  // Code will run on keyboard wakeup
  if (backlight_suspend_state) {
    backlight_enable();
  }
  rgblight_wakeup();
  power_down_flag = false;
  layer_clear();
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
  // Not change default layer
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch ( get_highest_layer(state)) {
  case _ENG:
    rgblight_sethsv_noeeprom(ENG_HSV_COLOR);

    if (disable_lang_switch) {
      disable_lang_switch = false;
    }
    else if (IS_LAYER_ON(_RUS)) {
      tap_code16(LANG_SWITCH);
    }
    break; 
  case _FN:
    rgblight_sethsv_noeeprom(FN_HSV_COLOR);

    if (disable_lang_switch) {
      disable_lang_switch = false;
    }
    else if (IS_LAYER_ON(_RUS)) { // For FN layer use only english
      tap_code16(LANG_SWITCH);
    }
    break;
   case _RUS:
    rgblight_sethsv_noeeprom(RUS_HSV_COLOR);
    
    if (disable_lang_switch) {
      disable_lang_switch = false;
    }
    else if (IS_LAYER_ON(_ENG) || IS_LAYER_ON(_FN)) {
      tap_code16(LANG_SWITCH);
    }
    break;
  
  default:
    rgblight_sethsv_noeeprom(ENG_HSV_COLOR);
    break;
  }
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Process my custom key codes
  switch (keycode) { 
    case (ENG_KC_SCLN):
      if (record->event.pressed) {
        if (get_mods() == MOD_BIT(KC_LSFT)) {
          tap_code(KC_6);
        }
        else {
          tap_code16(LSFT(KC_4));
        }
        return false;
      }
      break;
    case (POINTER_ARROW):
      if (record->event.pressed) {
        tap_code(KC_KP_MINUS);
        tap_code16(LSFT(KC_DOT));
        return false;
      }
    case (LT(0, KC_LGUI)): // Implement LGUI_T(TG(1))
      if (record->tap.count && record->event.pressed) {
        layer_invert(1); // When tap toggle 1 level
      }
      else if (!record->tap.count && record->event.pressed) {
        register_code(KC_LGUI);
      }
      else if (!record->tap.count && !record->event.pressed) {
        unregister_code(KC_LGUI);
      }
      return false;
    case (LT(0, KC_LSFT)): // Implement LSFT_T(OSM(MOD_LSFT))
    print("string Shift");
      if (record->tap.count && record->event.pressed) {
        add_oneshot_mods(MOD_MASK_SHIFT); // When tap register osm left shift event
      }
      else if (!record->tap.count && record->event.pressed) {
        register_code(KC_LSFT);
      }
      else if (!record->tap.count && !record->event.pressed) {
        unregister_code(KC_LSFT);
      }
      return false;
    case (KC_LCTL): { // Switch to eng layout without language changing
      static bool rus_layer_enabled = false;

      if (!record->tap.count && record->event.pressed && IS_LAYER_ON(_RUS)) 
      {
        println("Reg");
        rus_layer_enabled = true;
        disable_lang_switch = true;
        layer_off(_RUS);
      }
      else if (!record->tap.count && !record->event.pressed && rus_layer_enabled) {
        println("UNReg");
        rus_layer_enabled = false;
        disable_lang_switch = true;
        layer_on(_RUS);
      }
    }
      // return false;
  }
  return true;
}
