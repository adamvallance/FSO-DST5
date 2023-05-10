
#ifndef FSO_I2C_BUFFER_H
#define FSO_I2C_BUFFER_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGPIO.h"

class I2CBuffers{
    FullExpandedGPIO* gpios;
    public:
        I2CBuffers(FullExpandedGPIO*); //add in gpios for other setup?
        void selectSFP(int);
        void reset();

    private: 
    //callback stubs


    ;
};

#endif //FSO_I2C_BUFFER_H