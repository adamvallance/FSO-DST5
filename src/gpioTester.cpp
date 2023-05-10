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
    ERROR_LED.write(0);
    printf("test interrupt\n");
}

void gpioTestClass::toggleDebug(){
    // //gpios->write(GPIO_DEBUG_LOOP_A, 1);
    // //gpios->write(GPIO_DEBUG_LOOP_A, 0);
    // gpios->write(GPIO_DEBUG_LOOP_A, 0);
    // gpios->write(GPIO_DEBUG_LOOP_B, 0);


    while(true){
        gpios->write(GPIO_DEBUG_LED, 0);

        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);

        gpios->write(GPIO_DEBUG_LED, 1);
        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);
        ;
    }
}