#include "mbed.h"
 
#include "epd.h"

DigitalOut myled(LED1);
SPI spi(D11, D12, D13); // mosi, miso, sclk
// DigitalOut cs(D0);

Epd epd(&spi, D2, D1, D0); // spi, cs, reset, dc
 
int main() {



    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        wait(1.0); // 1 sec
    }
}