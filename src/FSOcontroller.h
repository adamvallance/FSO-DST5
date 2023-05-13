#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H

#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "FullExpandedGPIO.h"
#include <string>
#include "sfp.h"
#include "iterator"
#include "I2CBuffers.h"
#include "xpoint.h"




class FSOcontroller{
    DigitalOut nominalRunningLED;
    PwmOut fanPWM;
    FullExpandedGPIO* gpios;
    I2CBuffers* i2cbufs;
    XPoints* xpoints;
    //create sfps
    SFP sfpMaster = {gpios, i2cbufs, 0};
    SFP sfp1 = {gpios,i2cbufs, 1};
    SFP sfp2 = {gpios,i2cbufs, 2};
    SFP sfp3 = {gpios,i2cbufs, 3};
    SFP sfp4 = {gpios,i2cbufs, 4};
    SFP sfp5 = {gpios,i2cbufs, 5};
    SFP sfp6 = {gpios,i2cbufs, 6};
    SFP sfp7 = {gpios,i2cbufs, 7};

    SFP* sfps[8] = {&sfpMaster, &sfp1, &sfp2, &sfp3, &sfp4, &sfp5, &sfp6, &sfp7};


    public:
        FSOcontroller(PinName* pins, FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, XPoints* xpoints); 
        void start();
        void setError();
        void disableSFPs();

        int errorStatus = 0;
    private:
        void pollForPower();
        void exec();
        std::vector<int> SFPpowers;
        int highestPowerSFP = 1;
        int prevHighestPowerSFP = 1;
#ifdef ROUTE_TX_ONLY_ONE_FIBRE
        bool allOnAfterLowPower=false;
#endif

};



#endif //FSO_CONTROLLER_H