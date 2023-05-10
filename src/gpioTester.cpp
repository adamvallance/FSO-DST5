#include "gpioTester.h"

gpioTestClass::gpioTestClass(FullExpandedGPIO* gpios):
    gpios(gpios)
{   
    gpios->registerInterrupt(0, this);
    // gpios->registerInterrupt(1, this);
    // gpios->registerInterrupt(2, this);
    // gpios->registerInterrupt(3, this);    
}

void gpioTestClass::interrupt(){
    printf("test interrupt\n");
    ERROR_LED.write(0);
}

void gpioTestClass::toggleDebug(){
    while(true){
        const char testData[3] = {0x09, 0x0, 0x0};//, 0xCC, 0xDD};
        I2CB.write(GPIO_EXPANDER_ADDRESSES[3], &testData[0], 3);
        ERROR_LED = !ERROR_LED;
        // gpios->write(GPIO_DEBUG_LED, 0);
        // //gpios->write(GPIO_DEBUG_LOOP_A, 0);
        // //gpios->write(GPIO_DEBUG_LOOP_B, 0);
        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);
        // gpios->write(GPIO_DEBUG_LED, 1);
        // //gpios->write(GPIO_DEBUG_LOOP_A, 1);
        // //gpios->write(GPIO_DEBUG_LOOP_B, 1);
        //ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);


    }
}