#pragma once

#include "mbed.h"

class Edp
{
    public: 
    Edp(SPI* spi, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName bussy_pin);

    protected:
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);
    
    DigitalOut dc;
    DigitalOut cs;
    DigitalOut reset;
    DigitalIn bussy;
    SPI* spi;
};