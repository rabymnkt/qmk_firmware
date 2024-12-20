#include QMK_KEYBOARD_H
#include <stdio.h>

bool is_lower_pressed = false;
bool is_upper_pressed = false;
static bool is_ime_locked = false;

enum custom_keycodes {
    ESC_ENG = SAFE_RANGE,
    LOWER,
    RAISE,
    IME_LOCK,
    IME_UNLOCK
};

enum keymap_layer {
    KL_BASE,
    KL_LOWER,
    KL_RAISE,
    KL_ADJUST,
    KL_NUMPAD,
    KL_MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [KL_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT,   LOWER, KC_BSPC,     KC_SPC,   RAISE, KC_LGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [KL_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_CAPS, SGUI(KC_LEFT), XXXXXXX, ESC_ENG, TT(4),                  KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX,  KC_ESC,   MO(5),                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_RGUI, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_BSPC,     KC_ENT,   RAISE, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [KL_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_CIRC,  KC_DLR, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_MINS,  KC_EQL, KC_PLUS, KC_LCBR, KC_LPRN,                      KC_RPRN, KC_RCBR, KC_BSLS, KC_SLSH, XXXXXXX, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX,  KC_GRV,   KC_LT, KC_LBRC,                      KC_RBRC,   KC_GT, KC_PIPE, XXXXXXX, KC_RGUI, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,   LOWER,  KC_DEL,     KC_SPC, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [KL_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PSCR, XXXXXXX, KC_VOLD,KC_MUTE, KC_VOLU,                       KC_WBAK,KC_WSCH, KC_WHOM, KC_WFWD, KC_WREF,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_INS, XXXXXXX, IME_LOCK, AG_SWAP, KC_MPLY,                      KC_MPRV, AG_NORM, IME_UNLOCK, KC_MNXT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, KC_BSPC,     KC_SPC, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [KL_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_P7, KC_P8,   KC_P9,  KC_NUM,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+-------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   TT(4),                      XXXXXXX,  KC_P4,   KC_P5,   KC_P6, KC_PAST, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+-------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PMNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+-------+--------+--------+--------+--------|
                                          XXXXXXX, _______, KC_BSPC,     KC_SPC,   KC_P0,  KC_ENT
                                      //`--------------------------'  `--------------------------'
  ),
  [KL_MOUSE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_HOME,   KC_UP,  KC_END, KC_PGUP, XXXXXXX,                      KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+                    +--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX,                      KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+                    +--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   MO(5),                      XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, KC_BSPC,     KC_SPC, XXXXXXX,  KC_ENT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8
#define L_NUMPAD 16
#define L_MOUSE 32

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
		case L_NUMPAD:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case L_MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("unknown"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ESC_ENG:
        if (record->event.pressed) {
            // キーコード ESC_ENG が押された時
            tap_code(KC_ESC);
        }else{
            // キーコード ESC_ENG が離された時
            tap_code(KC_LNG2);
        }
        break;
    case LOWER:
        if (record->event.pressed) {
            layer_on(KL_LOWER);
            is_lower_pressed = true;
            update_tri_layer(KL_LOWER, KL_RAISE, KL_ADJUST);
        } else {
            layer_off(KL_LOWER);
            update_tri_layer(KL_LOWER, KL_RAISE, KL_ADJUST);
            if (is_lower_pressed){
                tap_code(KC_LNG2);
            }
            is_lower_pressed = false;
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed) {
            layer_on(KL_RAISE);
            is_upper_pressed = true;
            update_tri_layer(KL_LOWER, KL_RAISE, KL_ADJUST);
        } else {
            layer_off(KL_RAISE);
            update_tri_layer(KL_LOWER, KL_RAISE, KL_ADJUST);
            if(is_upper_pressed && !is_ime_locked){
                tap_code(KC_LNG1);
            }
            is_upper_pressed = false;
        }
        return false;
        break;
    case IME_LOCK:
        if (record->event.pressed) {
            is_ime_locked = true;
        }
        return false;
        break;
    case IME_UNLOCK:
        if (record->event.pressed) {
            is_ime_locked = false;
        }
        return false;
        break;
    default:
        if (record->event.pressed) {
#ifdef OLED_ENABLE
            set_keylog(keycode, record);
#endif
            is_lower_pressed = false;
            is_upper_pressed = false;
        }
    }
    return true;
};
