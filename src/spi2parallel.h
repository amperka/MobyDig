#ifndef __SPI2PARALLEL_H__
#define __SPI2PARALLEL_H__

#include <Arduino.h>
#include <SPI.h>

// Low-level class for pceudo-SPI shift register driven devices

class Spi2Parallel {
public:
    // Hardware SPI constructor
    Spi2Parallel(uint8_t pinCS, uint8_t devicesCount,
        uint8_t bitOrder = MSBFIRST);
    // Software SPI constructor
    Spi2Parallel(uint8_t pinCS, uint8_t pinMOSI, uint8_t pinSCK,
        uint8_t devicesCount, uint8_t bitOrder = MSBFIRST);

    ~Spi2Parallel();
    // Use begin once in setup(). `defaultValues` is option array of bits*8.
    // Length of `defaultValues` must be equal `_deviceCount`.
    void begin(uint8_t* defaultValues = NULL);
    // Write all bits to one selected device (realy to internal buffer)
    void writeByte(uint8_t device, uint8_t value);
    // Write one bit to one selected device (realy to internal buffer)
    void writeBit(uint8_t device, uint8_t bit, bool value);

    // Sync internal buffer and real devices chain
    void update();

    // Reset values in all devices. If `_defaultValues` has setted set devices in
    // this state. Otherwise set all bits `LOW`.
    void reset();

    // Returns chain length
    uint8_t chainLength() { return _devicesCount; }

    // Returns device current state
    uint8_t getValue(uint8_t device) { return _devicesChain[device]; }

private:
    uint8_t _pinCS;
    uint8_t _pinMOSI;
    uint8_t _pinSCK;
    uint8_t _devicesCount;
    uint8_t _bitOrder;
    uint8_t* _devicesChain;
    uint8_t* _defaultValues;
    bool _hardwareSPI;
};

#endif // __SPI2PARALLEL_H__
