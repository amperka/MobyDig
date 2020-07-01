/*
 * This file is a part of SegM8 library.
 *
 * Product page: https://amperka.ru/product/SegM8
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 *
 * Author: Yury Botov <by@amperka.com>
 * License: GPLv3, all text here must be included in any redistribution.
 */

#include "segm8.h"

const static uint8_t font[] = {
    S7_SPACE, // space (all off)
    S7_TOP_UNDERLINE, // !
    S7_DOUBLE_QUOTE, // "
    S7_TOP_UNDERLINE, // #
    S7_TOP_UNDERLINE, // $
    S7_TOP_UNDERLINE, // %
    S7_TOP_UNDERLINE, // &
    S7_QUOTE, // '
    S7_TOP_UNDERLINE, // (
    S7_TOP_UNDERLINE, // )
    S7_TOP_UNDERLINE, // *
    S7_TOP_UNDERLINE, // +
    S7_COMMA, // ,
    S7_MINUS, // -
    S7_DOT, // .
    S7_SLASH, // /
    S7_0, // 0
    S7_1, // 1
    S7_2, // 2
    S7_3, // 3
    S7_4, // 4
    S7_5, // 5
    S7_6, // 6
    S7_7, // 7
    S7_8, // 8
    S7_9, // 9
    S7_TOP_UNDERLINE, // :
    S7_TOP_UNDERLINE, // ;
    S7_TOP_UNDERLINE, // <
    S7_EQUAL, // =
    S7_TOP_UNDERLINE, // >
    S7_TOP_UNDERLINE, // ?
    S7_TOP_UNDERLINE, // @
    S7_A, // A
    S7_B, // B
    S7_C, // C
    S7_D, // D
    S7_E, // E
    S7_F, // F
    S7_G, // G
    S7_H, // H
    S7_I, // I
    S7_J, // J
    S7_TOP_UNDERLINE, // K
    S7_L, // L
    S7_TOP_UNDERLINE, // M
    S7_N, // N
    S7_O, // O
    S7_P, // P
    S7_Q, // Q
    S7_R, // R
    S7_S, // S
    S7_T, // T
    S7_U, // U
    S7_TOP_UNDERLINE, // V
    S7_TOP_UNDERLINE, // W
    S7_TOP_UNDERLINE, // X
    S7_Y, // Y
    S7_TOP_UNDERLINE, // Z
    S7_LEFT, // [
    S7_BACK_SLASH, // '\'
    S7_RIGHT, // ]
    S7_DEGREE, // ^
    S7_UNDERSCORE, // _
};

static uint8_t decode(uint8_t c) {
    if (c > 95 && c < 128)
        c -= 32;
    if (c > 31) {
        c -= 32;
        return font[c];
    }
    return S7_TOP_UNDERLINE;
}

static uint8_t decodeDigit(uint8_t digit) {
    if (digit <= 9)
        return digit + '0';
    if (digit >= 10 && digit <= 15)
        return digit + 'A';
    return 'N';
}

SegM8::SegM8(uint8_t pinCS, uint8_t deviceCount)
    : _spi(pinCS, deviceCount)
    , _deviceCount(deviceCount) {}

SegM8::SegM8(uint8_t pinCS, uint8_t pinDI, uint8_t pinCLK, uint8_t deviceCount)
    : _spi(pinCS, pinDI, pinCLK, deviceCount)
    , _deviceCount(deviceCount) {}

void SegM8::begin() {
    _spi.begin();
    clear();
}

void SegM8::clear() {
    for (uint8_t i = 0; i < _spi.chainLength(); i++)
        _spi.writeByte(decode(' '), i);
    _spi.update();
}

void SegM8::display(int16_t number, uint8_t position, uint8_t width,
    uint8_t flags) {
    if (number < 0) {
        _spi.writeByte(decode('-'), position);
        display((uint32_t)(-number), position + 1, width - 1,
            flags & 0b11111110);
    } else {
        display((uint32_t)(number), position, width, flags);
    }
}

void SegM8::display(unsigned int number, uint8_t position, uint8_t width,
    uint8_t flags) {
    display((uint32_t)number, position, width, flags);
}

void SegM8::display(int32_t number, uint8_t position, uint8_t width,
    uint8_t flags) {
    if (number < 0) {
        _spi.writeByte(decode('-'), position);
        display((uint32_t)(-number), position + 1, width - 1,
            flags & 0b11111110);
    } else {
        display((uint32_t)(number), position, width, flags);
    }
}

void SegM8::display(uint32_t number, uint8_t position, uint8_t width,
    uint8_t flags) {
    uint8_t index = sizeof(_buffer) - 2;
    uint8_t radix = (flags & SEGM8_RADIX_16) ? 16 : 10;
    for (uint8_t i = 0; i < sizeof(_buffer); i++)
        _buffer[i] = 0;

    if (number == 0) {
        _buffer[index] = decodeDigit(0);
    } else {
        for (uint8_t i = index; i > 0; i--) {
            _buffer[i] = decodeDigit(number % radix);
            number /= radix;
            if ((number == 0 && !(flags & SEGM8_PAD_ZEROS)) || i + width < sizeof(_buffer) - 1) {
                index = i;
                break;
            }
        }
    }

    display((const char*)&_buffer[index], position, width, flags);
}

void SegM8::display(float number, uint8_t position, uint8_t width,
    uint8_t precission, uint8_t flags) {
    uint8_t index = sizeof(_buffer) - 2;
    for (uint8_t i = 0; i < sizeof(_buffer); i++)
        _buffer[i] = 0;

    long prec = 1;
    for (uint8_t i = 0; i < precission; i++)
        prec *= 10;

    long bothParts = number * prec;
    long rightPart = bothParts % prec;
    long leftPart = (long)number;

    if (rightPart == 0) {
        for (uint8_t i = 0; i < precission; i++)
            _buffer[index--] = decodeDigit(0);
    } else {
        for (uint8_t i = index; i > 0; i--) {
            _buffer[i] = decodeDigit(rightPart % 10);
            rightPart /= 10;
            if ((rightPart == 0 && !(flags & SEGM8_PAD_ZEROS)) || i + width < sizeof(_buffer) - 1) {
                index = i;
                break;
            }
        }
    }

    _buffer[index--] = '.';

    if (leftPart == 0) {
        _buffer[index] = decodeDigit(0);
    } else {
        for (uint8_t i = index; i > 0; i--) {
            _buffer[i] = decodeDigit(leftPart % 10);
            leftPart /= 10;
            if ((leftPart == 0 && !(flags & SEGM8_PAD_ZEROS)) || i + width < sizeof(_buffer) - 1) {
                index = i;
                break;
            }
        }
    }

    display((const char*)&_buffer[index], position, width, flags);
}

void SegM8::display(const char* string, uint8_t position, uint8_t width,
    uint8_t flags) {
    uint8_t beginPosition;
    uint8_t endPosition;
    uint8_t j = 0;

    if (flags && SEGM8_ALIGN_LEFT) {
        beginPosition = min(position, _spi.chainLength());
        endPosition = min(_spi.chainLength(), (position + min(width, strlen(string))));
    } else { // SEGM8_ALIGN_RIGHT
        beginPosition = min((position + (width - strlen(string))), _spi.chainLength());
        endPosition = min(_spi.chainLength(), (position + width));
    }

    for (uint8_t i = position; i < beginPosition; i++)
        _spi.writeByte(S7_SPACE, i);
    for (uint8_t i = beginPosition; i < endPosition; /*really blank*/) {
        if (string[i - beginPosition] == '.') {
            _spi.writeByte(decode(string[j - 1] | S7_DOT), i - 1);
            j++;
        } else {
            _spi.writeByte(decode(string[j++]), i++);
        }
    }
    for (uint8_t i = endPosition; i < min(_spi.chainLength(), (position + width));
         i++)
        _spi.writeByte(S7_SPACE, i);

    _spi.update();
}

void SegM8::display(String string, uint8_t position, uint8_t width,
    uint8_t flags) {
    uint8_t beginPosition;
    uint8_t endPosition;
    uint8_t j = 0;

    if (flags && SEGM8_ALIGN_LEFT) {
        beginPosition = min(position, _spi.chainLength());
        endPosition = min(_spi.chainLength(), (position + min(width, string.length())));
    } else { // SEGM8_ALIGN_RIGHT
        beginPosition = min((position + (width - string.length())), _spi.chainLength());
        endPosition = min(_spi.chainLength(), (position + width));
    }

    for (uint8_t i = position; i < beginPosition; i++)
        _spi.writeByte(S7_SPACE, i);
    for (uint8_t i = beginPosition; i < endPosition; /*really blank*/) {
        if (string[i - beginPosition] == '.') {
            _spi.writeByte(decode(string[j - 1] | S7_DOT), i - 1);
            j++;
        } else {
            _spi.writeByte(decode(string[j++]), i++);
        }
    }
    for (uint8_t i = endPosition; i < min(_spi.chainLength(), (position + width));
         i++)
        _spi.writeByte(S7_SPACE, i);

    _spi.update();
}

void SegM8::writeSegments(uint8_t mask, uint8_t deviceIndex) {
    _spi.writeByte(mask, deviceIndex);
    _spi.update();
}
