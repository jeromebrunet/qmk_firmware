/* Copyright 2020 Jerome Brunet
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

#include "mm60.h"

#define ARRAY_SIZE(x) (sizeof ((x)) / sizeof(*(x)))

static const uint8_t led_init[] = { D1, D3, D0, D5, D2 };

void keyboard_pre_init_kb(void)
{
    uint8_t i, pin;

    for (i = 0; i < ARRAY_SIZE(led_init); i++) {
        pin = led_init[i];
        setPinOutput(pin);
        writePin(pin, 1);
        _delay_ms(200);
        writePin(pin, 0);
    }
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state)
{
    uint8_t layer = get_highest_layer(state);

    writePin(D3, !!(layer & 0x1));
    writePin(D2, !!(layer & 0x2));
    writePin(D1, !!(layer & 0x4));

    return state;
}


bool led_update_kb(led_t led_state)
{
    bool res = led_update_user(led_state);

    if (res) {
        writePin(D5, led_state.caps_lock);
        writePin(D0, led_state.scroll_lock);
    }
    return res;
}
