#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

// Defines for bootmagic
layer_state_t layer_state_set_user(layer_state_t state) {
    // Prüfen, ob sowohl LOWER als auch RAISE aktiv sind
    if (layer_state_cmp(state, _RAISE) && layer_state_cmp(state, _LOWER)) {
        state |= (1UL << _ADJUST);  // ADJUST Layer aktivieren
    } else {
        state &= ~(1UL << _ADJUST);  // ADJUST Layer deaktivieren
    }
    return state;
}





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  


/* Qwerty
 * ,----------------------------------.           ,----------------------------------.
 * |  Q   |  W   |  E   |  R   |  T   |           |  Y   |  U   |  I   |  O   |  P   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  A   |  S   |  D   |  F   |  G   |           |  H   |  J   |  K   |  L   |  ;   |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Z   |  X   |  C   |  V   |  B   |           |  N   |  M   |  ,   |  .   |  /   |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.       ,--------------------.
 *                  | ESCAPE | LOWER| Space|    | Enter| RAISE| Shift |
 *                  `--------------------'      `--------------------.
 */
[_QWERTY] = LAYOUT_split_3x5_3(
  KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,           KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,
  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,           KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,
  KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,           KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                    KC_ESCAPE, LOWER,   KC_SPC,         KC_ENTER, RAISE,   KC_LEFT_SHIFT
),


/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab | Left | Down |  Up  | Right|           |    (  |  )  |   &  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  :  |  SPACE |  X |  C |   V   |           |    {  |  }  |   |  |   "  |   '  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |COMMAND| LOWER|BACKSPACE|    |      | RAISE|      |
 *                  `--------------------'    `--------------------.
 */
[_RAISE] = LAYOUT_split_3x5_3(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      KC_LPRN, KC_RPRN, KC_AMPR,  KC_LBRC, KC_RBRC,
  KC_COLON, KC_SPC,  KC_X, KC_C, KC_V,      KC_LCBR, KC_RCBR, KC_PIPE, KC_DQT,  KC_QUOT,
                    KC_LCMD, LOWER, KC_BACKSPACE,      _______, RAISE, _______
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Reset |      |      |      |      |           |      |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Caps|   ~  |      |  <   |   >  |           |      |      |      |   |  |   "  |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      | LOWER|      |    |      | RAISE|  Del |
 *                  `--------------------'    `--------------------.
 */
[_LOWER] = LAYOUT_split_3x5_3(
  QK_BOOT, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_L,
  KC_CAPS, KC_TILD, _______, KC_LT, KC_GT,      _______, _______, _______, KC_PIPE,  KC_DQT,
                    _______, LOWER, _______,      KC_ENT,  RAISE, KC_DEL
),

/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |           |   F6 |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  F11 |  F12 |      |      |      |           |      |      |      |Taskmg|caltde|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * | Reset|      |      |      |      |           |      |      |      |      |      |
 * `----------------------------------'           `----------------------------------'
 *                  ,--------------------.    ,--------------------.
 *                  |      | LOWER|      |    |      | RAISE|      |
 *                  `--------------------'    `--------------------.
 */
[_ADJUST] =  LAYOUT_split_3x5_3(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, TSKMGR, CALTDEL,
  QK_BOOT, _______, _______, _______, _______,      _______, _______, _______, _______,  _______,
                    _______, _______, _______,      _______,  _______, _______
)
};

