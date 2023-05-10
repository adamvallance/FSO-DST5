#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H

#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "I2CBuffer.h"
#include "GPIOexpander.h"
#include "FullExpandedGPIO.h"
#include <string>




class FSOcontroller{
    DigitalOut nominalRunningLED;
    PwmOut fanPWM;
    I2C* I2CA;
    I2C* I2CB;
    FullExpandedGPIO* expandedGPIO;

    public:
        FSOcontroller(PinName* pins, FullExpandedGPIO* expandedGPIO, I2C* I2CA, I2C* I2CB);
        void start();
        void setError();

        int errorStatus = 0;
    private:
        void pollForPower();
        void exec();

        

};



#endif //FSO_CONTROLLER_H