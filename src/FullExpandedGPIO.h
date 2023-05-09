#ifndef FSO_FULL_EXPANDED_GPIO_H
#define FSO_FULL_EXPANDED_GPIO_H
#include "mbed.h"
#include "config.h"
#include <cstdint>
#include "GPIOexpander.h"




class FullExpandedGPIO{
    I2C* i2c;
    //GPIOexpander motorEl_GPIOexpander = {&GPIO_EXPANDER_FRDM_PINS[0][0], GPIO_EXPANDER_ADDRESSES[0],  i2c, 0};
    //GPIOexpander motorAz_GPIOexpander = {&GPIO_EXPANDER_FRDM_PINS[1][0], GPIO_EXPANDER_ADDRESSES[1], i2c, 1};
    //GPIOexpander GPIOexpander3= {&GPIO_EXPANDER_FRDM_PINS[2][0], GPIO_EXPANDER_ADDRESSES[2], i2c, 2};
    GPIOexpander GPIOexpander4= {&GPIO_EXPANDER_FRDM_PINS[3][0], GPIO_EXPANDER_ADDRESSES[3], i2c, 3};
     //--------CREATE GPIO EXPANDERS-------------
     public:
        FullExpandedGPIO(I2C*);
        void write(GPIOexpanderPin, uint8_t state);
        uint8_t read(GPIOexpanderPin);
        void reset();
        void registerInterrupt(int gpioExIndex, callbackClass* cb);

            // //save gpio expander objects in a list of pointers to be passed to classes to access.

        //GPIOexpander* gpioExpanders[4] = {&motorEl_GPIOexpander, &motorAz_GPIOexpander, &GPIOexpander3, &GPIOexpander4};
        GPIOexpander* gpioExpanders[1] = {&GPIOexpander4};

     private:
    


};

//create instances of this in FSOcontroller.h
class gpioTestClass: public callbackClass{
    public:
        gpioTestClass(FullExpandedGPIO* gpios){
            gpios->registerInterrupt(0, this);
        }
        void interrupt(){
            printf("testInterrupt");
            ERROR_LED.write(0);
        }
};

#endif //FSO_FULL_EXPANDED_GPIO_H