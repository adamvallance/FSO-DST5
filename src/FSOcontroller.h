
#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H
#include "mbed.h"
#include "motorDriver.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     100ms
class FSOcontroller{
    public:
        FSOcontroller();
        //void test();

    private: //to change pins, change variables inside src/config.h
        void initGPIOs();







    ;
};

#endif //FSO_CONTROLLER_H