#ifndef FSO_FULL_EXPANDED_GPIO_H
#define FSO_FULL_EXPANDED_GPIO_H
#include "mbed.h"
#include "config.h"
#include <cstdint>
#include "GPIOexpander.h"




class FullExpandedGPIO{
    //GPIOexpander motorEl_GPIOexpander = {&GPIO_EXPANDER_FRDM_PINS[0][0], GPIO_EXPANDER_ADDRESSES[0], 0};
    //GPIOexpander motorAz_GPIOexpander = {&GPIO_EXPANDER_FRDM_PINS[1][0], GPIO_EXPANDER_ADDRESSES[1], 1};
    //GPIOexpander GPIOexpander3= {&GPIO_EXPANDER_FRDM_PINS[2][0], GPIO_EXPANDER_ADDRESSES[2], 2};
    GPIOexpander GPIOexpander4= {&GPIO_EXPANDER_FRDM_PINS[3][0],  GPIO_EXPANDER_ADDRESSES[3], 3};
     //--------CREATE GPIO EXPANDERS-------------
     public:
        FullExpandedGPIO();
        void write(GPIOexpanderPin, uint8_t state);
        uint8_t read(GPIOexpanderPin);
        void reset();
        void registerInterrupt(int gpioExIndex, callbackClass* cb);

            // //save gpio expander objects in a list of pointers to be passed to classes to access.

        //GPIOexpander* gpioExpanders[4] = {&motorEl_GPIOexpander, &motorAz_GPIOexpander, &GPIOexpander3, &GPIOexpander4};
        GPIOexpander* gpioExpanders[1] = {&GPIOexpander4};

     private:
    


};


#endif //FSO_FULL_EXPANDED_GPIO_H