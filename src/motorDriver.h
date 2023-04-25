
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"

class MotorDriver{
    DigitalOut stepUp;
    DigitalOut stepDown;
    DigitalOut stepLeft;
    DigitalOut stepRight;
    
    public:
        MotorDriver(PinName*); //add in gpios for other setup?
        void stepMotor(int);

    private: 
        DigitalOut *motorControls;






    ;
};

#endif //FSO_CONTROLLER_H