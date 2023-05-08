//derived from https://github.com/jrj12591/PCAL6524
#ifndef FSO_GPIO_EXPANDER_H
#define FSO_GPIO_EXPANDER_H
#include "mbed.h"
#include "config.h"
#include "GPIOexpanderConfig.h"
#include <cstdint>


class GPIOexpander{
    DigitalOut RESET_N;
    InterruptIn INT_N;
    I2C* i2c;
    int gpioExIndex;

    public:
        GPIOexpander(int I2CaddressIn, PinName*, I2C*, int gpioExIndex); //add in gpios for other setup?
        void write(uint16_t pin, uint8_t state);
        //void setPinMode(uint16_t pin, uint8_t mode);
        uint8_t read(uint16_t pin);
        void reset();
        void setPinDefaults(int);

        //todo 
        void setInterruptHandlerPtr(); 

    private:
        int I2Caddress;
        void writeRegister(uint8_t, uint8_t);
        void writePortRegisters(uint8_t, char);
        uint8_t readRegister(uint8_t);
};


#endif //FSO_GPIO_EXPANDER_H