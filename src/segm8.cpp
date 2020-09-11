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
    S7_TOP_UNDERLINE, // /
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
    S7_TOP_UNDERLINE, // '\'
    S7_RIGHT, // ]
    S7_DEGREE, // ^
    S7_UNDERSCORE, // _
};

static uint8_t decode(uint8_t c) {
    if (c > 95 && c < 128) {
        c -= 64;
        return font[c];
    } else if (c > 31) {
        c -= 32;
        return font[c];
    } else
        return S7_TOP_UNDERLINE;
}

static uint8_t decodeDigit(uint8_t digit) {
    if (digit <= 9)
        return digit + '0';
    else if (digit >= 10 && digit <= 15)
        return digit - 10 + 'A';
    else
        return 'N';
}

SegM8::SegM8(uint8_t pinCS, uint8_t deviceCount)
    : _spi(pinCS, deviceCount)
    , _deviceCount(deviceCount) { }

SegM8::SegM8(uint8_t pinCS, uint8_t pinDI, uint8_t pinCLK, uint8_t deviceCount)
    : _spi(pinCS, pinDI, pinCLK, deviceCount)
    , _deviceCount(deviceCount) { }

void SegM8::begin() {
    _spi.begin();
    clear();
}

void SegM8::clear() {
    for (uint8_t i = 0; i < _spi.chainLength(); i++)
        _spi.writeByte(S7_SPACE, i);
    _spi.update();
}

void SegM8::display(int16_t number, uint8_t position, uint8_t width, uint8_t flags) {
    if (number < 0) {
        display((uint32_t)(-number), position, width,
            (flags & 0b11111011) | SEGM8_NEGATIVE);
    } else {
        display((uint32_t)(number), position, width, flags | SEGM8_POSITIVE);
    }
}

void SegM8::display(uint16_t number, uint8_t position, uint8_t width, uint8_t flags) {
    display((uint32_t)number, position, width, flags | SEGM8_POSITIVE);
}

void SegM8::display(int32_t number, uint8_t position, uint8_t width, uint8_t flags) {
    if (number < 0) {
        display((uint32_t)(-number), position, width,
            (flags & 0b11111011) | SEGM8_NEGATIVE);
    } else {
        display((uint32_t)(number), position, width, flags | SEGM8_POSITIVE);
    }
}

void SegM8::display(uint32_t number, uint8_t position, uint8_t width, uint8_t flags) {
    uint8_t index = sizeof(_buffer) - 2;
    uint8_t radix = (flags & SEGM8_RADIX_16) ? 16 : 10;
    uint8_t w = width;

    // clear buffer
    for (uint8_t i = 0; i < sizeof(_buffer); i++)
        _buffer[i] = 0;

    // fill buffer
    if (number == 0) {
        if (flags & SEGM8_PAD_ZEROS) {
            while (w > 0) {
                _buffer[index--] = decodeDigit(0);
                w--;
            }
            index++;
        } else {
            _buffer[index] = decodeDigit(0);
        }
    } else {
        for (uint8_t i = index; i > 0; i--) {
            _buffer[i] = decodeDigit(number % radix);
            number /= radix;
            w--;
            if ((number == 0 && (!(flags & SEGM8_PAD_ZEROS))) || ((number == 0 && ((flags & SEGM8_PAD_ZEROS))) && ((!(flags & SEGM8_NEGATIVE)) && w <= 0)) || ((number == 0 && ((flags & SEGM8_PAD_ZEROS))) && ((flags & SEGM8_NEGATIVE) && w <= 1))) {
                index = i;
                break;
            }
        }
    }

    // add sign
    if (flags & SEGM8_NEGATIVE) {
        _buffer[--index] = '-';
    }

    // test result width and display buffer
    if ((uint8_t)strlen((const char*)&_buffer[index]) < width + 1)
        display((const char*)&_buffer[index], position, width, flags);
    else {
        for (uint8_t i = sizeof(_buffer) - 1 - width; i < sizeof(_buffer) - 1; i++)
            _buffer[i] = '!';
        display((const char*)&_buffer[sizeof(_buffer) - 1 - width], position,
            width, flags);
    }
}

void SegM8::display(double number, uint8_t position, uint8_t width, uint8_t precission, uint8_t flags) {
    bool isNegative = false;

    for (uint8_t i = 0; i < sizeof(_buffer); i++) // clear buffer
        _buffer[i] = 0;
    int8_t index = sizeof(_buffer) - 2; // start fill from back

    int32_t prec = 1;
    for (uint8_t i = 0; i < precission; i++)
        prec *= 10;

    int32_t bothParts = number * prec;
    int32_t rightPart = abs(bothParts % prec);
    int32_t leftPart = bothParts / prec;

    if (leftPart < 0) { // store information about sign
        leftPart = -leftPart;
        isNegative = true;
    }

    for (int8_t i = index; i > (index - precission); i--) { // store right part with pad zeros
        _buffer[i] = decodeDigit(rightPart % 10);
        rightPart /= 10;
    }

    _buffer[index - precission] = '.'; // store point

    for (int8_t i = (index - precission - 1); i >= 0; i--) { // store left part
        _buffer[i] = decodeDigit(leftPart % 10);
        leftPart /= 10;
        if (leftPart == 0) {
            index = i;
            break;
        };
    }

    if (isNegative && index > 0) { // store sign
        if (flags & SEGM8_PAD_ZEROS) {
            while ((int8_t)(sizeof(_buffer) - 2 - index) < (int8_t)(width - 1)) {
                _buffer[--index] = '0';
            }
        }
        _buffer[--index] = '-';
    } else {
        if (flags & SEGM8_PAD_ZEROS) {
            while ((int8_t)(sizeof(_buffer) - 2 - index) < (int8_t)width) {
                _buffer[--index] = '0';
            }
        }
    }

    display((const char*)&_buffer[index], position, width, flags); // print!
}

void SegM8::display(const char* string, uint8_t position, uint8_t width, uint8_t flags) {
    uint8_t beginPosition;
    uint8_t endPosition;
    uint8_t j = 0, i = 0;

    uint8_t trueLength = 0; // used chars in the input buffer
    uint8_t trueWidth = 0; // length of result

    uint8_t prev = 0;
    uint8_t curr = 0;
    uint8_t buf[32]; // define maximum field size as 32 modules

    for(i = 0; i < strlen(string) && trueLength < 32; i++) {
        curr = string[i];
        if(curr == '.' && (prev == 0 || prev == '.')) { // first symbol is dot or dot after dot
            buf[trueLength++] = S7_SPACE | S7_DOT;
            trueWidth++;
        } else if(curr == '.') { // dot after character
            buf[trueLength - 1] = buf[trueLength - 1] | S7_DOT;
        } else { // character
            buf[trueLength++] = decode(curr);
            trueWidth++;
        }
        if(trueWidth == width && (curr == '.' || string[i+1] != '.'))
            break;
        prev = curr;
    }

    if (flags & SEGM8_ALIGN_LEFT) {
        beginPosition = position;
        endPosition = min(_spi.chainLength(), (position + trueWidth));
    } else { // SEGM8_ALIGN_RIGHT
        if (trueWidth == width) {
            beginPosition = position;
        } else {
            beginPosition = position + (width - trueWidth);
        }
        endPosition = min(_spi.chainLength(), (position + width));
    }

    for (i = position; i < beginPosition; i++) // left spaces
        _spi.writeByte(S7_SPACE, i);

    i = beginPosition;

    for(j = 0; j < trueWidth; j++)
        _spi.writeByte(buf[j], i++);

    for (i = endPosition + 1; i < min(_spi.chainLength(), (position + width)); i++) // right spaces
        _spi.writeByte(S7_SPACE, i);

    _spi.update();
}

void SegM8::display(String string, uint8_t position, uint8_t width, uint8_t flags) {
    display(string.c_str(), position, width, flags);
}

void SegM8::writeSegments(uint8_t mask, uint8_t deviceIndex) {
    _spi.writeByte(mask, deviceIndex);
    _spi.update();
}
