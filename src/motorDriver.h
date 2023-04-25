
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
        void debug(int);

    private: 
    //callback stubs
        void stepUp(){stepMotor(0);};
        void stepDown(){stepMotor(1);};
        void stepLeft(){stepMotor(2);};
        void stepRight(){stepMotor(3);};








    ;
};

#endif //FSO_CONTROLLER_H