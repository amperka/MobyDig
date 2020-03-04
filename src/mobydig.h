#ifndef __MOBYDIG_H__
#define __MOBYDIG_H__

#include "spi2parallel.h"
#include "stdarg.h"

class MobyDig {
public:
    MobyDig(uint8_t pinCS, uint8_t devicesCount)
        : _interface(pinCS, devicesCount) {}
    MobyDig(uint8_t pinCS, uint8_t pinMOSI, uint8_t pinSCK, uint8_t devicesCount)
        : _interface(pinCS, pinMOSI, pinSCK, devicesCount) {}

    void begin(const char* resetString = NULL);

    void printf(const char* format, ...);
    void setSegments(uint8_t device, uint8_t segments);

    void reset();

private:
    uint8_t _char2font(char c);
    Spi2Parallel _interface;
};

#endif
