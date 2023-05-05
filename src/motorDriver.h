
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
        void stepDown(){stepMotor(1);};
        void stepLeft(){stepMotor(2);};
        void stepRight(){stepMotor(3);};

        void doHalfStepAz();
        void doHalfStepEl();
        void stopStepAz();
        void stopStepEl();
        void exec();

        bool azStepTriggered = false;
        bool elStepTriggered = false;

        bool currentlyStepping = false;

        Ticker stepTickerAz;
        Ticker stepTickerEl;

        Timeout stopAzStepping;
        Timeout stopElStepping;


    ;
};

#endif //FSO_CONTROLLER_H