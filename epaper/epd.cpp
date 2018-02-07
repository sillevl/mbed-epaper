#include "epd.h"

Epd::Epd(SPI* spi, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName busy_pin):
 cs(cs_pin), reset(reset_pin), dc(dc_pin), busy(busy_pin)
{
    this->spi = spi;
}

void Epd::sendCommand(unsigned char command)
{
    dc = 0;
    spi->transfer(command);
}

void Epd::sendData(unsigned char data)
{
    dc = 1;
    spi->transfer(data);
}

void Epd::waitUntilIdle()
{
    while(busy == 0){   // 0:busy, 1: idle
        Thread::wait(100);
    }
}

void Epd::reset()
{
    reset = 0;
    Thread::wait(200);
    reset = 1;
    Thread::wait(200);
}