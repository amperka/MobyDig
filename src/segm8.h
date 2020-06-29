/*
 * This file is a part of SegM8 library.
 *
 * Product page: https://amperka.ru/product/SegM8
 * © Amperka LLC (https://amperka.com, dev@amperka.com)
 * 
 * Author: Yury Botov <by@amperka.com>
 * License: GPLv3, all text here must be included in any redistribution.
 */

#ifndef __SEGM8_H__
#define __SEGM8_H__

#include "font7seg.h"
#include "spi2parallel.h"
#include <Arduino.h>
#include <SPI.h>

constexpr uint8_t SEGM8_ALIGN_RIGHT = 0;
constexpr uint8_t SEGM8_ALIGN_LEFT = 1;
constexpr uint8_t SEGM8_NO_PAD_ZEROS = 0; // ??
constexpr uint8_t SEGM8_PAD_ZEROS = 2;
constexpr uint8_t SEGM8_RADIX_10 = 0;
constexpr uint8_t SEGM8_RADIX_16 = 4;

class SegM8 {
public:
    SegM8(uint8_t pinCS, uint8_t deviceCount = 1);
    SegM8(uint8_t pinCS, uint8_t pinDI, uint8_t pinCLK, uint8_t deviceCount = 1);
    void begin();
    void clear();
    void display(int number, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_RIGHT);
    void display(unsigned int number, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_RIGHT | SEGM8_RADIX_10);
    void display(long number, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_RIGHT);
    void display(unsigned long number, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_RIGHT | SEGM8_RADIX_10);
    void display(float number, uint8_t position, uint8_t width, uint8_t precission = 1, uint8_t flags = SEGM8_ALIGN_LEFT);
    void display(const char* string, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_LEFT);
    void display(String string, uint8_t position, uint8_t width, uint8_t flags = SEGM8_ALIGN_LEFT);
    void writeSegments(uint8_t mask, uint8_t deviceIndex = 0);

private:
    Spi2Parallel _spi;
    uint8_t _deviceCount;
    uint8_t _buffer[11];
};

#endif // __OCTOFET_H__
