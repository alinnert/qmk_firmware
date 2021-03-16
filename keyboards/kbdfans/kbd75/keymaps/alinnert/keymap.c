#include QMK_KEYBOARD_H

enum layers {
  BASE_WIN,
  BASE_MAC,
  KBD_FN,
  SYS_WIN,
  SYS_MAC,
  CH_WIN,
  CH_MAC,
};

enum custom_keycodes {
  M_GRV = SAFE_RANGE,
  M_DSPC,
};

void update_layer_leds(bool is_mac) {
  if (is_mac) {
    rgblight_sethsv_range(0, 180, 180, 11, 13);
  } else {
    rgblight_sethsv_range(148, 180, 180, 11, 13);
  }
};

layer_state_t layer_state_set_user(layer_state_t state) {
  update_layer_leds(layer_state_cmp(state, BASE_MAC));
  return state;
};

void keyboard_post_init_user(void) {
  update_layer_leds(IS_LAYER_ON(BASE_MAC));
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      // Backtick
      case M_GRV:
        register_code(KC_LSHIFT);
        SEND_STRING("= ");
        unregister_code(KC_LSHIFT);
        break;

      // Doppel-Leertaste
      case M_DSPC:
        tap_code(KC_SPACE);
        tap_code(KC_SPACE);
        tap_code(KC_LEFT);
        break;
    }
  }

  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE_WIN] = LAYOUT(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TG(BASE_MAC),_______,KC_DEL,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   XXXXXXX,  KC_BSPC,  KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
    MO(SYS_WIN),KC_A,   KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                      KC_ENT,   KC_PGDN,
    KC_LSFT,  MO(CH_WIN),KC_Z,    KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    KC_END,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_LCTL,  KC_LGUI,  KC_SPC,                       KC_RALT,  KC_RGUI,  MO(KBD_FN),KC_LEFT, KC_DOWN,   KC_RGHT
  ),

  [BASE_MAC] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    MO(SYS_MAC),_______,_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
    _______,  MO(CH_MAC),_______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    KC_LGUI,  KC_LCTL,  _______,                      KC_LGUI,  KC_LALT,  _______,                      _______,  KC_RCTL,  _______,  _______,  _______,  _______
  ),

  [KBD_FN] = LAYOUT(
    RGB_TOG,  RGB_M_P,  RGB_M_B,  RGB_M_R,  RGB_M_SW, RGB_M_SN, RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  XXXXXXX,  XXXXXXX,  XXXXXXX,  EEP_RST,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET,    XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  BL_OFF,   BL_INC,   BL_ON,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  BL_TOGG,  BL_STEP,  BL_DEC,   BL_BRTG,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  RGB_VAI,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            RGB_SAI,  RGB_VAD,
    XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_HUD,  RGB_SAD,  RGB_HUI
  ),

  [CH_WIN] = LAYOUT(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    S(KC_BSLS), S(KC_2),    S(KC_SLSH), XXXXXXX,       RALT(KC_8), RALT(KC_9), S(KC_RBRC),    S(KC_5),       XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,
    XXXXXXX,    RALT(KC_Q), S(KC_4),    KC_NUBS,    S(KC_NUBS), S(KC_7),    RALT(KC_MINS), RALT(KC_7), RALT(KC_0), RALT(KC_RBRC), RALT(KC_NUBS), XXXXXXX,                            XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    M_GRV,         S(KC_6),    S(KC_0),    S(KC_MINS),    S(KC_1),       XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,       KC_SPC,                                XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
  ),

  [CH_MAC] = LAYOUT(
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    S(KC_BSLS), S(KC_2),    S(KC_SLSH), XXXXXXX,    A(KC_5),    A(KC_6),    S(KC_RBRC), S(KC_5),    XXXXXXX,    XXXXXXX,    XXXXXXX,                XXXXXXX,
    XXXXXXX,    A(KC_L),    S(KC_4),    KC_NUBS,    S(KC_NUBS), S(KC_7),    A(S(KC_7)), A(KC_8),    A(KC_9),    A(KC_N),    A(KC_7),    XXXXXXX,                            XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    M_GRV,      S(KC_6),    S(KC_0),    S(KC_MINS), S(KC_1),    XXXXXXX,    XXXXXXX,                XXXXXXX,    XXXXXXX,
    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    KC_SPC,                             XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
  ),

  [SYS_WIN] = LAYOUT(
    KC_PWR,   KC_SLEP,  KC_WAKE,       XXXXXXX,   XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  KC_WBAK,  KC_WFWD,       KC_WREF,   KC_WHOM,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PSCR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,   XXXXXXX,
    KC_CAPS,  KC_MSTP,  KC_MPRV,       KC_MNXT,   KC_MPLY,       KC_BRIU,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
    XXXXXXX,  XXXXXXX,  C(G(KC_LEFT)), G(KC_TAB), C(G(KC_RGHT)), KC_BRID,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  XXXXXXX,  XXXXXXX,                      KC_APP,   XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,       XXXXXXX,   XXXXXXX,       XXXXXXX,  KC_VOLD,  KC_VOLU,  KC_MUTE,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
    _______,  _______,  _______,                                 _______,  _______,  M_DSPC,                       _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [SYS_MAC] = LAYOUT(
    XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  XXXXXXX,        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  G(KC_LEFT),G(KC_RIGHT),  G(KC_R),  G(S(KC_H)),     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  G(S(KC_5)), XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_DEL,   XXXXXXX,
    XXXXXXX,  XXXXXXX,  KC_MPRV,       KC_MNXT,  KC_MPLY,        KC_BRIU,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
    XXXXXXX,  XXXXXXX,  C(KC_LEFT),    C(KC_UP), C(KC_RIGHT),    KC_BRID,  KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RIGHT, XXXXXXX,    XXXXXXX,                      S(KC_F10),XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,       XXXXXXX,  C(KC_DOWN),     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
    _______,  _______,  _______,                                 _______,  _______,  M_DSPC,                       _______,    _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  // [0] = LAYOUT(
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,            XXXXXXX,  XXXXXXX,
  //   XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  // ),

  // [0] = LAYOUT(
  //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
  //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
  //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,
  //   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
  //   _______,  _______,  _______,                      _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______
  // ),
};
