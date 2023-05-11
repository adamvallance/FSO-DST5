#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H

#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "FullExpandedGPIO.h"
#include <string>




class FSOcontroller{
    DigitalOut nominalRunningLED;
    PwmOut fanPWM;
    FullExpandedGPIO* expandedGPIO;

    public:
        FSOcontroller(PinName* pins, FullExpandedGPIO* expandedGPIO); 
        void start();
        void setError();

        int errorStatus = 0;
    private:
        void pollForPower();
        void exec();

        

};



#endif //FSO_CONTROLLER_H