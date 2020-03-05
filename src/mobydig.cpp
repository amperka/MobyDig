#include "mobydig.h"

static constexpr uint8_t font7seg[] = {
    0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, // 0 1 2 3 4
    0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, // 5 6 7 8 9

    0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, // A B C D E
    0b01110001, 0b00111101, 0b01110110, 0b00000110, 0b00001110, // F G H I J
    0b00000000, 0b00111000, 0b00000000, 0b01010100, 0b00111111, // K L M N O
    0b01110011, 0b01100111, 0b01010000, 0b01101101, 0b01111000, // P Q R S T
    0b00111110, 0b00000000, 0b00000000, 0b00000000, 0b01101110, // U V W X Y
    0b00000000, // Z

    0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, // a b c d e
    0b01110001, 0b00111101, 0b01110110, 0b00000110, 0b00001110, // f g h i j
    0b00000000, 0b00111000, 0b00000000, 0b01010100, 0b00111111, // k l m n o
    0b01110011, 0b01100111, 0b01010000, 0b01101101, 0b01111000, // p q r s t
    0b00111110, 0b00000000, 0b00000000, 0b00000000, 0b01101110, // u v w x y
    0b00000000, // z

    0b00000000, 0b01000000, 0b00001000, 0b01100011              // blank - _ gradus
};

void MobyDig::begin(const char* resetString) {
    if (resetString) {
        uint8_t* resetValues = new uint8_t[_interface.chainLength() * sizeof(char)];
        uint8_t i = 0, j = 0;
        while (i < strlen(resetString)) {
            if (resetString[j] == '.' && j != 0) {
                resetValues[i - 1] = _char2font(resetString[j - 1]) | 0b10000000;
                j++;
            } else {
                resetValues[i] = _char2font(resetString[j]);
            }
            i++;
            j++;
            if (i > _interface.chainLength() || resetString[j] == 0)
                break;
        }
        _interface.begin(resetValues);
    } else {
        _interface.begin();
    }
}

void MobyDig::printf(const char* format, ...) {
    char* buf = new char[_interface.chainLength() * 2 * sizeof(char) + 1];
    if (buf == NULL) {
        _interface.writeByte(0, 0b01111001);
        _interface.update();
    }

    va_list args;
    va_start(args, format);
    uint8_t len = vsnprintf(buf, _interface.chainLength() * 2 * sizeof(char), format, args);
    va_end(args);

    if (len >= 0)
        buf[len] = 0; // in windows gcc version xsprintf does not work properly
    else {
        buf[0] = 'E';
        buf[1] = 0;
    }

    uint8_t i = 0, j = 0;
    while (i < strlen(buf)) {
        if (buf[j] == '.' && j != 0) {
            _interface.writeByte(i - 1, _char2font(buf[j - 1]) | 0b10000000);
            j++;
        } else {
            _interface.writeByte(i, _char2font(buf[j]));
        }
        i++;
        j++;
        if (i > _interface.chainLength() || buf[j] == 0)
            break;
    }
    _interface.update();
    delete buf;
}

void MobyDig::setSegments(uint8_t device, uint8_t segments) {
    _interface.writeByte(device, segments);
    _interface.update();
}

void MobyDig::reset() { _interface.reset(); }

uint8_t MobyDig::_char2font(char c) {
    uint8_t result = '9' + 'Z' + 'z' - '0' - 'A' - 'a' + 2;
    if (c >= '0' && c <= '9') {
        result = c - '0';
    } else if (c >= 'A' && c <= 'Z') {
        result = c - 'A' + '9' - '0' + 1;
    } else if (c >= 'a' && c <= 'z') {
        result = c - 'a' + '9' + 'Z' - '0' - 'A' + 2;
    } else if (c == ' ') {
        result += 1;
    } else if (c == '-') {
        result += 2;
    } else if (c == '_') {
        result += 3;
    } else if (c == '^') { // градус
        result += 4;
    } else {
        result += 1;
    }
    return font7seg[result];
}
