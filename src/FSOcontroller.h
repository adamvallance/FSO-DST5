#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H

#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "FullExpandedGPIO.h"
#include <string>
#include "sfp.h"




class FSOcontroller{
    DigitalOut nominalRunningLED;
    PwmOut fanPWM;
    FullExpandedGPIO* expandedGPIO;

    //create sfps
    SFP sfpMaster = {expandedGPIO, 0};
    SFP sfp1 = {expandedGPIO, 1};
    SFP sfp2 = {expandedGPIO, 2};
    SFP sfp3 = {expandedGPIO, 3};
    SFP sfp4 = {expandedGPIO, 4};
    SFP sfp5 = {expandedGPIO, 5};
    SFP sfp6 = {expandedGPIO, 6};
    SFP sfp7 = {expandedGPIO, 7};

    SFP* sfps[8] = {&sfpMaster, &sfp1, &sfp2, &sfp3, &sfp4, &sfp5, &sfp6, &sfp7};


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