#ifndef FSO_GPIO_TESTER
#define FSO_GPIO_TESTER
#include "mbed.h"
#include "FullExpandedGPIO.h"
//create instances of this in main
class testClass: public callbackClass{
    FullExpandedGPIO* gpios;
    public:
        testClass(FullExpandedGPIO* gpios);
        void interrupt();
        void toggleDebugGPIO();
};

#endif //FSO_GPIO_TESTER