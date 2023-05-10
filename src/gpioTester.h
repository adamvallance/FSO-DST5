#ifndef FSO_GPIO_TESTER
#define FSO_GPIO_TESTER
#include "mbed.h"
#include "FullExpandedGPIO.h"
//create instances of this in main
class gpioTestClass: public callbackClass{
    FullExpandedGPIO* gpios;
    public:
        gpioTestClass(FullExpandedGPIO* gpios);
        void interrupt();
        void toggleDebug();
};

#endif //FSO_GPIO_TESTER