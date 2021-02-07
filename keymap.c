#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"

# endif

#ifdef SSD1306OLED
#include "ssd1306.h"

# endif

#include "arrows.h"
#include "bongocat.h"

extern uint8_t is_master;

enum layer_number
{
	_QWERTY = 0,
		_LOWER,
		_RAISE,
		_ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { /*QWERTY
	 * ,-----------------------------------------.                    ,-----------------------------------------.
	 *| `    |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *| Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *| Esc  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
	 * |------+------+------+------+------+------|  [   |    |    ]  |------+------+------+------+------+------|
	 *|LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |  ,  |   .  |   /  |RShift|
	 * `-----------------------------------------/       /     \      \-----------------------------------------'
	 *                   | LCtrl| LGUI |LOWER | /Space  /      \ BKSPC\   |RAISE |Return| RGUI |
	 *                   |      |      |      |/       /         \      \ |      |      |      |
	 *                  `----------------------------'           '------''--------------------'
	 */

[_QWERTY] = LAYOUT(\
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                       KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, \
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                       KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, \
		KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G,                       KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC,    KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL, \
		               KC_LCTL, KC_LGUI, MO(1), KC_SPC,    KC_BSPC, MO(2), KC_ENT, KC_LALT),
	/*LOWER
	 * ,-----------------------------------------.                    ,-----------------------------------------.
	 *|  F1   |  F2  |  F3  |  F4  |  F5  | F6  |                    |  F7  |  F8  |  F9  |  F10  | F11 |  F12 |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 * |  `   |  !   |  @   |  #   |  $   |  %   |                    |  ^   |   &    |  *   |   ( |  )  |  |   |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *|      |      |      |      |      |      |-------.    ,-------| mute | play | vol+ | vol- |  FF  |      |
	 *|------+------+------+------+------+------| CALC  |    | ptrsc |------+------+------+------+------+------|
	 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
	 * `-----------------------------------------/       /     \      \-----------------------------------------'
	 *                  | LAlt | LGUI |LOWER | /Space  /       \  Del \  |RAISE  |return| RGUI |
	 *                   |      |      |      |/       /         \      \ |      |      |      |
	 *                  `----------------------------'           '------''--------------------'
	 */
[_LOWER] = LAYOUT(\
		        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
		KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MUTE, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT, KC_TRNS, \
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC,   KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
		                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_DEL, KC_TRNS, KC_TRNS, KC_TRNS),
	/*RAISE
	 * ,-----------------------------------------.                    ,-----------------------------------------.
	 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *|      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *|  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
	 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
	 *|  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|     | Home | PGDN | PGUP |  End  |      |
	 * `-----------------------------------------/       /     \      \-----------------------------------------'
	 *                  | LAlt | LGUI |LOWER | /OS(SPC)/       \ BKSP \  |RAISE  |return| RGUI |
	 *                   |      |      |      |/       /         \      \ |      |      |      |
	 *                  `----------------------------'           '------''--------------------'
	 */

[_RAISE] = LAYOUT(\
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
		KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5,                              KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, \
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                           KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, \
		KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,       KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, \
		                KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_SPC),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	/*ADJUST
	 * ,-----------------------------------------.                    ,-----------------------------------------.
	 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
	 *| F13  |  F14 |  F15 |  F16 |  F17 | F18  |-------.    ,-------|      |      |      |      |      |      |
	 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
	 *| F19  | F20  | F21 |  F22 |  F23 |  F24  |-------|    |-------|      |      |      |     |      |      |
	 * `-----------------------------------------/       /     \      \-----------------------------------------'
	 *                  | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
	 *                   |      |      |      |/       /         \      \ |      |      |      |
	 *                  `----------------------------'           '------''--------------------'
	 */
[_ADJUST] = LAYOUT(\
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                       KC_NO, LGUI(LALT(KC_LEFT)), LGUI(LALT(KC_DOWN)), LGUI(LALT(KC_UP)), LGUI(LALT(KC_RGHT)), KC_NO, \
		KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18,                 KC_NO, LCAG(KC_LEFT), LCAG(KC_DOWN), LCAG(KC_UP), LCAG(KC_RGHT), KC_NO, \
		KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_NO,    KC_NO, KC_NO, LGUI(LCTL(KC_LEFT)), LGUI(LCTL(S(KC_LEFT))), LGUI(LCTL(S(KC_RIGHT))), LGUI(LCTL(KC_RGHT)), KC_NO, \
		                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

layer_state_t layer_state_set_user(layer_state_t state)
{
	return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
// #ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
	if (!is_keyboard_master())
		return OLED_ROTATION_180;	// flips the display 180 degrees if offhand
	return rotation;
}


void oled_task_user(void)
{
    // Only have one oled on currently
	if (is_keyboard_left())
	{
		switch (get_highest_layer(layer_state))
		{
			case _QWERTY:
				render_bongo_cat();
				break;
			case _RAISE:
				oled_write_raw_P(arrow[0], ANIM_SIZE);
				break;
			case _LOWER:
				oled_write_raw_P(arrow[1], ANIM_SIZE);
				break;
			case _ADJUST:
				oled_write_raw_P(arrow[2], ANIM_SIZE);
				break;
			default:
				oled_clear();
				oled_write_ln_P(PSTR("error"), false);
		}
	}
}