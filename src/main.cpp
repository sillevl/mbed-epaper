#include "mbed.h"
 
#include "epd.h"

Serial pc(SERIAL_TX, SERIAL_RX);

DigitalOut myled(LED1);
SPI spi(D11, D12, D13); // mosi, miso, sclk
// DigitalOut cs(D0);

Epd epd(spi, D3, D2, D1, D0); // spi, cs, reset, dc, busy
 
int main() {
    pc.printf("\r\n** e-Paper demo **\r\n")
    if (epd.init() != 0) {
        pc.printf("e-Paper init failed\r\n");
        return;
    }



    while(1) {
        myled = 1; // LED is ON
        wait(0.2); // 200 ms
        myled = 0; // LED is OFF
        wait(1.0); // 1 sec
    }
}