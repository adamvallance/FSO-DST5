
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"
#include "config.h"

class MotorDriver{
    DigitalOut motorStep;
    DigitalOut motorDir;

    InterruptIn motorDirCtrlClockwise;
    InterruptIn motorDirCtrlAnticlockwise;
    bool clockwiseSymbol;


    public:
        MotorDriver(PinName*, bool); //add in gpios for other setup?
        void stepMotor(int);
        void debug(int);
        void start();


    private: 
        //callback stubs
        void stepCW(){stepMotor(0);}; 
        void stepACW(){stepMotor(1);};


        //motor exectution loop
        void exec();
    ;
};

#endif //FSO_CONTROLLER_H