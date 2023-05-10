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
    //gpios->write(GPIO_DEBUG_LOOP_A, 1);
    //gpios->write(GPIO_DEBUG_LOOP_A, 0);
    gpios->write(GPIO_DEBUG_LOOP_A, 0);


    while(true){
        gpios->write(GPIO_DEBUG_LED, 1);
        //gpios->gpioExpanders[0]->reset();

        ThisThread::sleep_for(GPIO_TEST_HALF_PERIOD);


    }
}