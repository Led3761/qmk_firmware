#include QMK_KEYBOARD_H
#include <stdbool.h>
#include "transactions.h"

// Define colors for Layers
#define NO_USB_CONNECTION_HSV_COLOR HSV_WHITE
#define ENG_HSV_COLOR HSV_SPRINGGREEN
#define RUS_HSV_COLOR HSV_GOLD
#define FN_HSV_COLOR HSV_MAGENTA
#define QWERTY_HSV_COLOR HSV_RED

// Define language switch key combination
#define LANG_SWITCH LWIN(KC_SPACE)

// Defines using language
enum use_languages {
  LANG_ENG,
  LANG_RUS
};

// Defines names for use in layer keycodes and the keymap
enum jiran_layers {
  _ENG,
  _RUS,
  _QWERTY,
  _FN
};

// Define my custom keycodes
enum my_keycodes {
  ENG_KC_SCLN = SAFE_RANGE, // Custom keycode KC_SCLN (;/:) for RUS language
  POINTER_ARROW // Keycode for arrow (->)
};

bool keyboard_usb_connected = false;
// Remember backlight state before turn off on suspend
bool backlight_suspend_state = false;
// Set to true when suspend_power_down_user called first time
// reset to false after wake up. Use for set backlight_suspend_state once
bool power_down_flag = false;
// Current language
uint8_t current_lag = LANG_ENG;
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
      MO(_FN),
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

  [_QWERTY] = LAYOUT(
      KC_ESC,
      KC_1,
      KC_2,
      KC_3,
      KC_4,
      KC_5,
      KC_6,
      KC_7,
      KC_8,
      KC_9,
      KC_0,
      KC_MINS,
      TG(_QWERTY),
      KC_TAB,
      KC_Q,
      KC_W,
      KC_E,
      KC_R,
      KC_T,
      KC_Y,
      KC_U,
      KC_I,
      KC_O,
      KC_P,
      KC_LBRC,
      KC_EQL,
      KC_LSFT,
      KC_A,
      KC_S,
      KC_D,
      KC_F,
      KC_G,
      KC_H,
      KC_J,
      KC_K,
      KC_L,
      KC_SCLN,
      KC_RBRC,
      KC_LCTL,
      KC_Z,
      KC_X,
      KC_C,
      KC_V,
      KC_B,
      KC_N,
      KC_M,
      KC_COMM,
      KC_DOT,
      KC_SLSH,
      KC_QUOT,
      KC_LALT,
      KC_SPC,
      KC_LGUI,
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
      KC_TRNS,
      KC_TRNS,
      KC_TRNS,
      LCTL(KC_BSPC),
      KC_TRNS,
      LCTL(KC_ENT)
  )
};

// Custom data sync between sides
typedef struct _master_to_slave_t {
  bool m2s_power_state;
} master_to_slave_t;

typedef struct _slave_to_master_t {
  bool s2m_data_accepted;
} slave_to_master_t;

void power_state_sync_slave_handler(
  uint8_t in_buflen, const void* in_data, 
  uint8_t out_buflen, void* out_data) 
{
  const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
  slave_to_master_t *s2m = (slave_to_master_t*)out_data;

  if (m2s->m2s_power_state) {
    rgblight_wakeup();
  }
  else {
    rgblight_suspend();
  }

  s2m->s2m_data_accepted = true;
}

// Create combos
const uint16_t PROGMEM hard_sign_combo [] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM rus_yo_combo [] = {KC_T, KC_F, COMBO_END};
const uint16_t PROGMEM qwerty_layer_combo [] = {KC_DEL, KC_G, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(hard_sign_combo, KC_RIGHT_BRACKET),
  COMBO(rus_yo_combo, KC_GRV),
  COMBO(qwerty_layer_combo, TG(_QWERTY))
};

// Create key overrides
const key_override_t ctrl_shift_c_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_C, RCTL(KC_V), ~0);
// Override ctrl+c and ctrl+v key combination for FN layout
const key_override_t ctrl_c_fn_key_override = 
  ko_make_with_layers_and_negmods(MOD_MASK_CTRL	, KC_PSCR, RCTL(KC_INSERT), ~0, MOD_MASK_SHIFT);
const key_override_t ctrl_shift_c_fn_key_override = 
  ko_make_with_layers(MOD_MASK_SHIFT | MOD_MASK_CTRL , KC_PSCR, RSFT(KC_INSERT), ~0);

const key_override_t **key_overrides = (const key_override_t *[]){
  &ctrl_shift_c_key_override,
  &ctrl_c_fn_key_override,
  &ctrl_shift_c_fn_key_override,
  NULL // Null terminate the array of overrides!
};

void lang_check_and_set(uint8_t p_set_layer) {
  if (disable_lang_switch) {
    disable_lang_switch = false;
    return;
  }

  uint8_t mods = get_mods();

  if ((p_set_layer == _RUS) && current_lag != LANG_RUS)
  {
    current_lag = LANG_RUS;
    unregister_mods(mods);
    tap_code16(LANG_SWITCH);
    register_mods(mods);
  }
  else if (((p_set_layer == _FN) && current_lag != LANG_ENG)
        || ((p_set_layer == _ENG) && current_lag != LANG_ENG))
  {
    current_lag = LANG_ENG;
    unregister_mods(mods);
    tap_code16(LANG_SWITCH);
    register_mods(mods);
  }
}

void keyboard_post_init_user(void) {
  transaction_register_rpc(POWER_STATE_SYNC, power_state_sync_slave_handler);
  rgblight_wakeup();
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
    if (is_keyboard_master()) {
      master_to_slave_t m2s = {false};
      slave_to_master_t s2m = {false};

      transaction_rpc_exec(POWER_STATE_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m);
    }

    rgblight_suspend();
    power_down_flag = true;
    backlight_suspend_state = is_backlight_enabled();

    backlight_disable();
  }
}

void suspend_wakeup_init_user(void) {
  // Code will run on keyboard wakeup
  if (is_keyboard_master()) {
    master_to_slave_t m2s = {true};
    slave_to_master_t s2m = {false};
    
    transaction_rpc_exec(POWER_STATE_SYNC, sizeof(m2s), &m2s, sizeof(s2m), &s2m);
  }

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
  switch (get_highest_layer(state)) {
  case _ENG:
    rgblight_sethsv_noeeprom(ENG_HSV_COLOR);
    lang_check_and_set(_ENG);
    break; 

  case _FN:
    rgblight_sethsv_noeeprom(FN_HSV_COLOR);
    lang_check_and_set(_FN);
    break;

   case _RUS:
    rgblight_sethsv_noeeprom(RUS_HSV_COLOR);
    lang_check_and_set(_RUS);
    break;

  case _QWERTY:
    rgblight_sethsv_noeeprom(QWERTY_HSV_COLOR);
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
      if (record->tap.count && record->event.pressed && !IS_LAYER_ON(_FN)) {
        layer_invert(_RUS); // When tap toggle 1 level
      }
      else if (record->event.pressed) {
        register_code(KC_LGUI);
      }
      else if (!record->event.pressed) {
        unregister_code(KC_LGUI);
      }
      return false;
    case (LT(0, KC_LSFT)): // Implement LSFT_T(OSM(MOD_LSFT))
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

      if (!record->tap.count && record->event.pressed && IS_LAYER_ON(_RUS)) {
        rus_layer_enabled = true;
        disable_lang_switch = true;
        layer_off(_RUS);
      }
      else if (!record->tap.count && !record->event.pressed && rus_layer_enabled) {
        rus_layer_enabled = false;
        layer_on(_RUS);
      }
    }
      // return false;
  }
  return true;
}
