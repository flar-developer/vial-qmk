// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_logo(void) {
    // QMK Logo
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_logo();
    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE
/* Map physical under glow LEDs for RGB matrix support
 *  09, 02, xx, xx, 01, xx,                   xx, 11, xx, xx, 12, 19,
 *  xx, xx, xx, xx, xx, 00,                   10, xx, xx, xx, xx, xx,
 *  08, 03, 04, xx, xx, xx, 07, xx,   xx, 17, xx, xx, xx, 14, 13, 18,
 *                  xx, 05, 06, xx,   xx, xx, xx, 16, 15, xx
 *
 *   02,     01,     00,              35,     36,     37,
 * 11, 10, 09, 08, 07, 06,          41, 42, 43, 44, 45, 46,
 * 17, 16, 15, 14, 13, 12,          47, 48, 49, 50, 51, 52,
 * 23, 22, 21, 20, 09, 18, 05,  40, 53, 54, 55, 56, 57, 58,
 * 29, 28, 27, 26, 25, 24, 30,  65, 59, 60, 61, 62, 63, 64,
 *            34, 33, 32, 31     66, 67, 68, 69
 *   03,        04,                        39,        38
 */
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    /* kyria rev2
    { NO_LED, NO_LED, NO_LED, 1,      NO_LED, NO_LED, 2,      9     },
    { NO_LED, NO_LED, 0,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 7,      NO_LED, NO_LED, NO_LED, 4,      3,      8      },
    { NO_LED, NO_LED, 6,      5,      NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, 11,     NO_LED, NO_LED, 12,     19     },
    { NO_LED, NO_LED, 10,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, 17,     NO_LED, NO_LED, NO_LED, 14,     13,     18     },
    { NO_LED, NO_LED, 16,     15,     NO_LED, NO_LED, NO_LED, NO_LED },
    */
   // Left part
   {      5,  4,  3,  2,  1,  0 },
   {      6,  7,  8,  9, 10, 11 },
   {     17, 16, 15, 14, 13, 12 },
   {     18, 19, 20, 21, 22, 23 },
   { NO_LED, 28, 27, 26, 25, 24 },
   // Right part
   {     34, 33, 32, 31, 30, 29 },
   {     35, 36, 37, 38, 39, 40 },
   {     46, 45, 44, 43, 42, 41 },
   {     47, 48, 49, 50, 51, 52 },
   { NO_LED, 57, 56, 55, 54, 53 }
}, {
    // LED Index to Physical Position
    { 88, 8}, { 72, 8}, { 56, 8}, { 40, 8}, { 24, 8}, {  8, 8},
    {  8,20}, { 24,20}, { 40,20}, { 56,20}, { 72,20}, { 88,20},
    { 88,32}, { 72,32}, { 56,32}, { 40,32}, { 24,32}, {  8,32},
    {  8,44}, { 24,44}, { 40,44}, { 56,44}, { 72,44}, { 88,44},
    {108,38}, {100,56}, { 80,56}, { 64,56}, { 48,56},
    {144, 8}, {160, 8}, {176, 8}, {192, 8}, {208, 8}, {224, 8},
    {224,20}, {208,20}, {192,20}, {176,20}, {160,20}, {144,20},
    {144,32}, {160,32}, {176,32}, {192,32}, {208,32}, {224,32},
    {224,44}, {208,44}, {192,44}, {176,44}, {160,44}, {144,44},
    {124,38}, {132,56}, {152,56}, {168,56}, {184,56}
}, {
    // LED Index to Flag
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL,
    LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL, LED_FLAG_ALL

} };
#endif
