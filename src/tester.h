#ifndef FSO_GPIO_TESTER
#define FSO_GPIO_TESTER
#include "mbed.h"
#include "FullExpandedGPIO.h"
#include "I2CBuffers.h"
//create instances of this in main
class testClass: public callbackClass{
    FullExpandedGPIO* gpios;
    I2CBuffers* i2cbufs;
    public:
        testClass(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs);
        void interrupt();
        void toggleDebugGPIO();
        void I2CbufferTest();
};

#endif //FSO_GPIO_TESTER