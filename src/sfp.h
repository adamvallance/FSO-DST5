
#ifndef FSO_SFP_H
#define FSO_SFP_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGPIO.h"

class SFP{
    FullExpandedGPIO* gpios;
    int SFPindex;
    public:
        SFP(FullExpandedGPIO*, int); //add in gpios for other setup?
        float getPower();
};

#endif //FSO_I2C_BUFFER_H