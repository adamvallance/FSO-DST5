#ifndef FSO_GPIO_CALLBACK_CLASS
#define FSO_GPIO_CALLBACK_CLASS
#include "mbed.h"
#include "config.h"

//global error led
extern DigitalOut ERROR_LED;
extern I2C I2CA;
extern I2C I2CB;

class callbackClass{
    public:
        virtual void interrupt() = 0;
};


#endif //FSO_GPIO_CALLBACK_CLASS