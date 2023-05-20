/*
 * MIT License
 *
 * Copyright (c) 2023 Liron Meler
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include "hex_face.h"
#include "watch_utility.h"

char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'b', 'C', 'd', 'E', 'F'};

void hex_face_setup(movement_settings_t *settings, uint8_t watch_face_index, void ** context_ptr) {
    (void) settings;
    if (*context_ptr == NULL) {
        *context_ptr = malloc(sizeof(hex_state_t));
        memset(*context_ptr, 0, sizeof(hex_state_t));
        // Do any one-time tasks in here; the inside of this conditional happens only at boot.
    }
    // Do any pin or peripheral setup here; this will be called whenever the watch wakes from deep sleep.
}

void hex_face_activate(movement_settings_t *settings, void *context) {
    (void) settings;

    // Handle any tasks related to your watch face coming on screen.
}

bool hex_face_loop(movement_event_t event, movement_settings_t *settings, void *context) {
    char buf[11];
    uint8_t pos;
    uint32_t index;

    watch_date_time date_time;
    switch (event.event_type) {
        case EVENT_ACTIVATE:
        case EVENT_TICK:
        case EVENT_LOW_ENERGY_UPDATE:
            date_time = watch_rtc_get_date_time();
            
            pos = 0;
            sprintf(buf, "%s", watch_utility_get_weekday(date_time));
            
            index = 2;
            buf[index++] = map[date_time.unit.day / 0x10];
            buf[index++] = map[date_time.unit.day % 0x10];
            
            buf[index++] = map[date_time.unit.hour / 0x10];
            buf[index++] = map[date_time.unit.hour % 0x10];
            
            buf[index++] = map[date_time.unit.minute / 0x10];
            buf[index++] = map[date_time.unit.minute % 0x10];
            
            buf[index++] = map[date_time.unit.second / 0x10];
            buf[index++] = map[date_time.unit.second % 0x10];

            watch_display_string(buf, pos);
            break;
        default:
            return movement_default_loop_handler(event, settings);
    }

    return true;
}

void hex_face_resign(movement_settings_t *settings, void *context) {
    (void) settings;
    (void) context;
}

