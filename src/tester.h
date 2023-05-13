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
#ifdef ROUTING_TEST
    PinName* pins;
    DigitalIn TX1On;
    DigitalIn TX2On;
    DigitalIn SwapRXBtn;
    DigitalIn bothOnOrReset;
    public:
        testClass(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints, PinName* pins);
        void XPointsTX1On();
        void XPointsTX2On();
        void IncrementRX();
        void bothOn();
        void start();
        int current = 7;
        bool allTxOn = false;
#else //normal
    public:
        testClass(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints);
#endif
        void interrupt();
        void toggleDebugGPIO();
        void I2CbufferTest();
        void XPointsTest();
};

#endif //FSO_GPIO_TESTER