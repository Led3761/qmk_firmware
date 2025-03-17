/*
Copyright 2022 GEIST <@geigeigeist>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


// ┌─────────────────────────────────────────────────┐
// │ k e y   m a t r i x                             │
// └─────────────────────────────────────────────────┘

#define MATRIX_ROW_PINS { C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define DEBOUNCE 5


// ┌─────────────────────────────────────────────────┐
// │ s p l i t   c o m m u n i c a t i o n           │
// └─────────────────────────────────────────────────┘

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT_POLL 10
#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_WATCHDOG_TIMEOUT 3000


// ┌─────────────────────────────────────────────────┐
// │ e n c o d e r s                                 │
// └─────────────────────────────────────────────────┘

#define ENCODER_RESOLUTION 2


// ┌─────────────────────────────────────────────────┐
// │ o l e d s                                       │
// └─────────────────────────────────────────────────┘

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#    define OLED_FONT_H  "./lib/glcdfont.c"
#endif

// ┌─────────────────────────────────────────────────┐
// │ a u d i o                                       │
// └─────────────────────────────────────────────────┘
#define AUDIO_PIN B5
#define AUDIO_DAC_SAMPLE_MAX 4095U
#define AUDIO_POWER_CONTROL_PIN_ON_STATE 1

#define AUDIO_VOICES
#define AUDIO_VOICE_DEFAULT butts_fader

#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4