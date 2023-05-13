
#ifndef FSO_SFP_H
#define FSO_SFP_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGPIO.h"
#include "I2CBuffers.h" 

class SFP{
    FullExpandedGPIO* gpios;
    I2CBuffers* i2cbufs;
    int SFPindex;
    public:
        SFP(FullExpandedGPIO*, I2CBuffers*, int); //add in gpios for other setup?
        float getRXPower();
        void disableTX();
        void enableTX();
};

#endif //FSO_I2C_BUFFER_H