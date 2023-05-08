#ifndef FSO_FULL_EXPANDED_GPIO_H
#define FSO_FULL_EXPANDED_GPIO_H
#include "mbed.h"
#include "config.h"
#include <cstdint>
#include "GPIOexpander.h"

class FullExpandedGPIO{
    I2C* i2c;
    GPIOexpander motorEl_GPIOexpander = {GPIO_EXPANDER_ADDRESSES[0], GPIO_EXPANDER_PINS[0], i2c, 0};
    GPIOexpander motorAz_GPIOexpander = {GPIO_EXPANDER_ADDRESSES[1], GPIO_EXPANDER_PINS[1], i2c, 1};
    GPIOexpander GPIOexpander3= {GPIO_EXPANDER_ADDRESSES[2], GPIO_EXPANDER_PINS[2], i2c, 2};
    GPIOexpander GPIOexpander4= {GPIO_EXPANDER_ADDRESSES[3], GPIO_EXPANDER_PINS[3], i2c, 3};
     //--------CREATE GPIO EXPANDERS-------------
     public:
     FullExpandedGPIO(I2C*);
     void write(GPIOexpanderPin, uint8_t state);
     uint8_t read(GPIOexpanderPin);
     void reset();

     private:
    
    // //save gpio expander objects in a list of pointers to be passed to classes to access.

    GPIOexpander* gpioExpanders[4] = {&motorEl_GPIOexpander, &motorAz_GPIOexpander, &GPIOexpander3, &GPIOexpander4};


};

#endif //FSO_FULL_EXPANDED_GPIO_H