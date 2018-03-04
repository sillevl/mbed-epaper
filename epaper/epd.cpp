#include "epd.h"
#include "demo.c"

#include "images/eo-ict-vives-black.c"
#include "images/eo-ict-vives-red.c"
#include "images/hackerspace-black.c"
#include "images/hackerspace-red.c"
#include "images/lesrooster-black.c"
#include "images/lesrooster-red.c"
#include "images/vives-large.c"

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
    spi->write(command);
    cs = 1;
}

void Epd::sendData(unsigned char data)
{
    dc = 1;
    cs = 0;
    spi->write(data);
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

/**
 * @brief: After this command is transmitted, the chip would enter the deep-sleep mode to save power. 
 *         The deep sleep mode would return to standby by hardware reset. The only one parameter is a 
 *         check code, the command would be executed if check code = 0xA5. 
 *         You can use Epd::Reset() to awaken and use Epd::Init() to initialize.
 */
void Epd::sleep()
{
    sendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
    sendData(0xF7);     // border floating
    sendCommand(POWER_OFF);
    waitUntilIdle();
    sendCommand(DEEP_SLEEP);
    sendData(0x15);
}

void Epd::displayFrame()
{
    sendCommand(DISPLAY_REFRESH);
    Thread::wait(100);
    waitUntilIdle();
}

void Epd::demo()
{
    sendCommand(DATA_START_TRANSMISSION_1);
    Thread::wait(2);
    for(int i = 0; i < this->width / 8 * this->height; i++) {
        sendData(gImage_lesrooster_black[i]);
    }
    Thread::wait(2);

    sendCommand(DATA_START_TRANSMISSION_2);
    Thread::wait(2);
    for(int i = 0; i < this->width / 8 * this->height; i++) {
        sendData(gImage_lesrooster_red[i]);
    }
    Thread::wait(2);

    displayFrame();
}