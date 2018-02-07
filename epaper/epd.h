#pragma once

#include "mbed.h"

class Epd
{
    public: 
    Epd(SPI* spi, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName busy_pin);

    protected:
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);

    void waitUntilIdle();
    void reset();
    
    DigitalOut dc;
    DigitalOut cs;
    DigitalOut reset;
    DigitalIn busy;
    SPI* spi;
};