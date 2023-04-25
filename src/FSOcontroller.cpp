#include "FSOcontroller.h"
//All definitions of pins follow. To adjust pin numbers change in config.h.
//digital pins cannot be declared as members of a class.

//for some reason, on board leds are active low idk why
DigitalOut frdm_led_green(LED2);
DigitalOut frdm_led_blue(LED3);
DigitalOut frdm_led_red(LED1);


FSOcontroller::FSOcontroller(){
    initGPIOs();
    while (true) {
        frdm_led_red = !frdm_led_red;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void FSOcontroller::initGPIOs(){
    //turn board LEDs off, weirdly they are active low.
    frdm_led_green = 1;
    frdm_led_red = 1;
    frdm_led_blue = 1;
}

// void FSOcontroller::test(){
//     ;//frdm_led_red = 1;
// }

