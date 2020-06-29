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

constexpr uint8_t S7_SPACE = 0b00000000;
constexpr uint8_t S7_DOT = 0b10000000;
constexpr uint8_t S7_MINUS = 0b01000000;

constexpr uint8_t S7_TOP_UNDERLINE = 0b00000001;
constexpr uint8_t S7_UNDERSCORE = 0b0001000;
constexpr uint8_t S7_DEGREE = 0b01100011;
constexpr uint8_t S7_UNDER_DEGREE = 0b01011100;

constexpr uint8_t S7_0 = 0b00111111;
constexpr uint8_t S7_1 = 0b00000110;
constexpr uint8_t S7_2 = 0b01011011;
constexpr uint8_t S7_3 = 0b01001111;
constexpr uint8_t S7_4 = 0b01100110;
constexpr uint8_t S7_5 = 0b01101101;
constexpr uint8_t S7_6 = 0b01111101;
constexpr uint8_t S7_7 = 0b00000111;
constexpr uint8_t S7_8 = 0b01111111;
constexpr uint8_t S7_9 = 0b01101111;

constexpr uint8_t S7_A = 0b01110111;
constexpr uint8_t S7_B = 0b01111100;
constexpr uint8_t S7_C = 0b00111001;
constexpr uint8_t S7_D = 0b01011110;
constexpr uint8_t S7_E = 0b01111001;
constexpr uint8_t S7_F = 0b01110001;
constexpr uint8_t S7_G = 0b00111101;
constexpr uint8_t S7_H = 0b01110110;
constexpr uint8_t S7_I = S7_1;
constexpr uint8_t S7_J = 0b00001110;
constexpr uint8_t S7_K = S7_TOP_UNDERLINE;
constexpr uint8_t S7_L = 0b00111000;
constexpr uint8_t S7_M = S7_TOP_UNDERLINE;
constexpr uint8_t S7_N = 0b01010100;
constexpr uint8_t S7_O = S7_0;
constexpr uint8_t S7_P = 0b01110011;
constexpr uint8_t S7_Q = 0b01100111;
constexpr uint8_t S7_R = 0b01010000;
constexpr uint8_t S7_S = S7_5;
constexpr uint8_t S7_T = 0b01111000;
constexpr uint8_t S7_U = 0b00111110;
constexpr uint8_t S7_V = S7_TOP_UNDERLINE;
constexpr uint8_t S7_W = S7_TOP_UNDERLINE;
constexpr uint8_t S7_X = S7_TOP_UNDERLINE;
constexpr uint8_t S7_Y = 0b01101110;
constexpr uint8_t S7_Z = S7_TOP_UNDERLINE;

#endif // __FONT_7_SEG_H__
