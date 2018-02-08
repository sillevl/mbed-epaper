#include "epd.h"

Epd::Epd(SPI* spi, PinName cs_pin, PinName reset_pin, PinName dc_pin, PinName busy_pin):
  cs(cs_pin), display_reset(reset_pin), dc(dc_pin), busy(busy_pin)
{
    this->spi = spi;
    spi->format(8, 0);
    spi->frequency(2000000);
    width = 400;
    height = 300;
    init();
}

void Epd::init()
{
    reset();
    sendCommand(BOOSTER_SOFT_START);
    sendData(0x17);
    sendData(0x17);
    sendData(0x17);
    sendCommand(POWER_ON);
    waitUntilIdle();
    sendCommand(PANEL_SETTING);
    sendData(0x0F);
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

void Epd::clearFrame()
{
    sendCommand(DATA_START_TRANSMISSION_1);
    Thread::wait(2);
    for(int i = 0; i < width / 8 * height; i++) {
        sendData(0xFF);
    }
    Thread::wait(2);
    sendCommand(DATA_START_TRANSMISSION_2);
    Thread::wait(2);
    for(int i = 0; i < width / 8 * height; i++) {
        sendData(0xFF);
    }
    Thread::wait(2);
}