#include "epd.h"

Epd::Epd(SPI& spi_object, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName busy_pin):
 spi(spi_object), cs(cs_pin), display_reset(reset_pin), dc(dc_pin), busy(busy_pin)
{
    spi.format(8, 0);
    spi.frequency(2000000);
}

int Epd::init()
{
    // if (IfInit() != 0) {
    //     return -1;
    // }
    reset();
    sendCommand(BOOSTER_SOFT_START);
    sendData(0x17);
    sendData(0x17);
    sendData(0x17);
    sendCommand(POWER_ON);
    waitUntilIdle();
    sendCommand(PANEL_SETTING);
    sendData(0x0F);
    return 0;
}

void Epd::sendCommand(unsigned char command)
{
    dc = 0;
    cs = 0;
    //spi->transfer(command);
    cs = 1;
}

void Epd::sendData(unsigned char data)
{
    dc = 1;
    cs = 0;
    //spi->transfer(data);
    cs = 1;
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