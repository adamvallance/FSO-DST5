
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"

class MotorDriver{
    DigitalOut motor1Step;
    DigitalOut motor1Dir;
    DigitalOut motor2Step;
    DigitalOut motor2Dir;
    
    InterruptIn motorDirCtrlUp;
    InterruptIn motorDirCtrlDown;
    InterruptIn motorDirCtrlLeft;
    InterruptIn motorDirCtrlRight;

    public:
        MotorDriver(PinName*, PinName*); //add in gpios for other setup?
        void stepMotor(int);

    private: 






    ;
};

#endif //FSO_CONTROLLER_H