
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"
#include "config.h"

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
        void start();

    private: 
    //callback stubs
        void stepUp(){stepMotor(0);}; //replace to 0,1,2,3
        void stepDown(){stepMotor(0);};
        void stepLeft(){stepMotor(0);};
        void stepRight(){stepMotor(0);};

        void exec();
        // void stepUp(){debug(0);};
        // void stepDown(){debug(0);};
        // void stepLeft(){debug(0);};
        // void stepRight(){debug(0);};

    ;
};

#endif //FSO_CONTROLLER_H