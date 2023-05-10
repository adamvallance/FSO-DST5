//derived from https://github.com/jrj12591/PCAL6524
#ifndef FSO_GPIO_EXPANDER_H
#define FSO_GPIO_EXPANDER_H
#include "mbed.h"
#include "config.h"
#include "GPIOexpanderConfig.h"
#include <cstdint>
#include "callbackClass.h"


class GPIOexpander{
    DigitalOut RESET_N;
    InterruptIn INT_N;
    int gpioExIndex;

    public:
        GPIOexpander(PinName* pins, int I2CaddressIn, int gpioExIndex); //add in gpios for other setup?
        void write(uint16_t pin, char state);
        //void setPinMode(uint16_t pin, char mode);
        char read(uint16_t pin);
        void reset();
        void setPinDefaults(int);
        void registerInterrupt(callbackClass* );

        //todo 
        void setInterruptHandlerPtr(); 

    private:
        int I2Caddress;
        void writeRegister(char, char);
        void writePortRegisters(char, const char*);
        char readRegister(char);
};


#endif //FSO_GPIO_EXPANDER_H