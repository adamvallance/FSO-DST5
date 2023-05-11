#ifndef FSO_GPIO_TESTER
#define FSO_GPIO_TESTER
#include "mbed.h"
#include "FullExpandedGPIO.h"
#include "I2CBuffers.h"
#include "xpoint.h"
//create instances of this in main
class testClass: public callbackClass{
    FullExpandedGPIO* gpios;
    I2CBuffers* i2cbufs;
    XPoints* xpoints;
    public:
        testClass(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints);
        void interrupt();
        void toggleDebugGPIO();
        void I2CbufferTest();
        void XPointsTest();
};

#endif //FSO_GPIO_TESTER