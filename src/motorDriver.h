
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"

class MotorDriver{
    public:
        MotorDriver(DigitalOut*); //add in gpios for other setup?
        void stepMotor(int);

    private: 
        DigitalOut *motorControls;






    ;
};

#endif //FSO_CONTROLLER_H