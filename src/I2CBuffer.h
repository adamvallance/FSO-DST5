
#ifndef FSO_I2C_BUFFER_H
#define FSO_I2C_BUFFER_H
#include "mbed.h"
#include "config.h"

class I2CBuffer{
    DigitalOut reset;
    I2C* i2c;

    public:
        I2CBuffer(PinName, I2C* i2c); //add in gpios for other setup?


    private: 
    //callback stubs


    ;
};

#endif //FSO_I2C_BUFFER_H