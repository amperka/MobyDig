/*
 * This file is a part of SegM8 library.
 *
 * Product page: https://amperka.ru/product/SegM8
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 * 
 * Author: Yury Botov <by@amperka.com>
 * License: GPLv3, all text here must be included in any redistribution.
 */

#ifndef __FONT_7_SEG_H__
#define __FONT_7_SEG_H__

#include <inttypes.h>

/*
    ___0___
   /       \
  |         |
 5|         |1
   \___6___/
   /       \
  |         |
 4|         |2
   \___3___/
               *7
 */

constexpr uint8_t S7_SPACE = 0b00000000; // " "
constexpr uint8_t S7_DOT = 0b10000000; // "."

constexpr uint8_t S7_MINUS = 0b01000000; // "-"
constexpr uint8_t S7_DOUBLE_QUOTE = 0b00100010; // '"'
constexpr uint8_t S7_QUOTE = 0b00100000; // "'"
constexpr uint8_t S7_COMMA = 0b00010000; // ","
constexpr uint8_t S7_EQUAL = 0b01001000; // "="
constexpr uint8_t S7_LEFT = 0b00111001; // "["
constexpr uint8_t S7_RIGHT = 0b00001111; // "]"

constexpr uint8_t S7_TOP_UNDERLINE = 0b00000001;
constexpr uint8_t S7_UNDERSCORE = 0b0001000; // "_"
constexpr uint8_t S7_DEGREE = 0b01100011;
constexpr uint8_t S7_UNDER_DEGREE = 0b01011100;

constexpr uint8_t S7_0 = 0b00111111; // "0"
constexpr uint8_t S7_1 = 0b00000110; // "1"
constexpr uint8_t S7_2 = 0b01011011; // "2"
constexpr uint8_t S7_3 = 0b01001111; // "3"
constexpr uint8_t S7_4 = 0b01100110; // "4"
constexpr uint8_t S7_5 = 0b01101101; // "5"
constexpr uint8_t S7_6 = 0b01111101; // "6"
constexpr uint8_t S7_7 = 0b00000111; // "7"
constexpr uint8_t S7_8 = 0b01111111; // "8"
constexpr uint8_t S7_9 = 0b01101111; // "9"

constexpr uint8_t S7_A = 0b01110111; // "A"
constexpr uint8_t S7_B = 0b01111100; // "b"
constexpr uint8_t S7_C = 0b01011000; // "c"
constexpr uint8_t S7_D = 0b01011110; // "d"
constexpr uint8_t S7_E = 0b01111001; // "E"
constexpr uint8_t S7_F = 0b01110001; // "F"
constexpr uint8_t S7_G = 0b00111101; // "G"
constexpr uint8_t S7_H = 0b01110110; // "H"
constexpr uint8_t S7_I = S7_1; // "I"
constexpr uint8_t S7_J = 0b00001110; // "J"
constexpr uint8_t S7_K = S7_TOP_UNDERLINE;
constexpr uint8_t S7_L = 0b00111000; // "L"
constexpr uint8_t S7_M = S7_TOP_UNDERLINE;
constexpr uint8_t S7_N = 0b01010100; // "n"
constexpr uint8_t S7_O = 0b01011100; // "o"
constexpr uint8_t S7_P = 0b01110011; // "P"
constexpr uint8_t S7_Q = 0b01100111; // "q"
constexpr uint8_t S7_R = 0b01010000; // "r"
constexpr uint8_t S7_S = S7_5; // "S"
constexpr uint8_t S7_T = 0b01111000; // "t"
constexpr uint8_t S7_U = 0b00111110; // "U"
constexpr uint8_t S7_V = S7_TOP_UNDERLINE;
constexpr uint8_t S7_W = S7_TOP_UNDERLINE;
constexpr uint8_t S7_X = S7_TOP_UNDERLINE;
constexpr uint8_t S7_Y = 0b01101110; // "Y"
constexpr uint8_t S7_Z = S7_TOP_UNDERLINE;

#endif // __FONT_7_SEG_H__
