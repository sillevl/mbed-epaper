#include "epd.h"

Epd::Epd(SPI& spi_object, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName busy_pin):
 spi(spi_object), cs(cs_pin), display_reset(reset_pin), dc(dc_pin), busy(busy_pin)
{
    this->spi = spi;
}

void Epd::sendCommand(unsigned char command)
{
    dc = 0;
    //spi->transfer(command);
}

void Epd::sendData(unsigned char data)
{
    dc = 1;
    //spi->transfer(data);
}

void Epd::waitUntilIdle()
{
    while(busy == 0){   // 0:busy, 1: idle
        Thread::wait(100);
    }
}

void Epd::reset()
{
    display_reset = 0;
    Thread::wait(200);
    display_reset = 1;
    Thread::wait(200);
}