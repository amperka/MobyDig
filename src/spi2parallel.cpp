#include "spi2parallel.h"

Spi2Parallel::Spi2Parallel(uint8_t pinCS, uint8_t devicesCount,
    uint8_t bitOrder) {
    _pinCS = pinCS;
    _devicesCount = devicesCount;
    _bitOrder = bitOrder;
    _devicesChain = new uint8_t[_devicesCount];
    _hardwareSPI = true;
    _defaultValues = NULL;
}

Spi2Parallel::Spi2Parallel(uint8_t pinCS, uint8_t pinMOSI, uint8_t pinSCK,
    uint8_t devicesCount, uint8_t bitOrder) {
    _pinCS = pinCS;
    _pinMOSI = pinMOSI;
    _pinSCK = pinSCK;
    _devicesCount = devicesCount;
    _bitOrder = bitOrder;
    _devicesChain = new uint8_t[_devicesCount];
    _hardwareSPI = false;
    _defaultValues = NULL;
}

Spi2Parallel::~Spi2Parallel() {
    if (_devicesChain != NULL) {
        delete[] _devicesChain;
    }
}

void Spi2Parallel::begin(uint8_t* defaultValues) {
    _defaultValues = defaultValues;
    pinMode(_pinCS, OUTPUT);
    digitalWrite(_pinCS, LOW);
    if (_hardwareSPI) {
        // SPI.beginTransaction(SPISettings(1000000, _bitOrder, SPI_MODE0));
        SPI.begin();
        SPI.setBitOrder(_bitOrder);
    } else {
        pinMode(_pinSCK, OUTPUT);
        pinMode(_pinMOSI, OUTPUT);
        digitalWrite(_pinSCK, LOW);
        digitalWrite(_pinMOSI, LOW);
    }
    reset();
}

void Spi2Parallel::writeByte(uint8_t device, uint8_t value) {
    _devicesChain[device] = value;
}

void Spi2Parallel::writeBit(uint8_t device, uint8_t bit, bool value) {
    if (value)
        _devicesChain[device] |= (1 << bit);
    else
        _devicesChain[device] &= ~(1 << bit);
}

void Spi2Parallel::reset() {
    for (uint8_t device = 0; device < _devicesCount; device++) {
        if (_defaultValues == NULL)
            writeByte(device, 0);
        else
            writeByte(device, _defaultValues[device]);
    }
    update();
}

void Spi2Parallel::update() {
    // start condition
    if (!_hardwareSPI) {
        digitalWrite(_pinSCK, LOW);
        digitalWrite(_pinMOSI, LOW);
    }
    digitalWrite(_pinCS, LOW);
    // bit stream output
    for (int8_t i = _devicesCount - 1; i >= 0; i--) {
        if (_hardwareSPI)
            SPI.transfer(_devicesChain[i]);
        else
            shiftOut(_pinMOSI, _pinSCK, _bitOrder, _devicesChain[i]);
    }
    // end condition
    digitalWrite(_pinCS, HIGH);
    if (!_hardwareSPI) {
        digitalWrite(_pinMOSI, LOW);
        digitalWrite(_pinSCK, LOW);
    }
}
