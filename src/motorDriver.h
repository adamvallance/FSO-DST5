
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"
#include "config.h"
#include "callbackClass.h"
#include "FullExpandedGPIO.h"

class MotorDriver: public callbackClass{
    FullExpandedGPIO* gpios;
    DigitalOut motor1Step;
    DigitalOut motor1Dir;
    DigitalOut motor2Step;
    DigitalOut motor2Dir;
    
    InterruptIn motorDirCtrlUp;
    InterruptIn motorDirCtrlDown;
    InterruptIn motorDirCtrlLeft;
    InterruptIn motorDirCtrlRight;

    public:
        MotorDriver(PinName*, PinName*, FullExpandedGPIO*); 
        void stepMotor(int);
        void debug(int);
        void start();
        void interrupt();

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
        void wakeUp();
        void sleep();

        bool azStepTriggered = false;
        bool elStepTriggered = false;

        bool currentlyStepping = false;
        bool isAsleep = true;

        Ticker stepTickerAz;
        Ticker stepTickerEl;

        Timeout stopAzStepping;
        Timeout stopElStepping;

        Timeout sleepTimeout;

    ;
};

#endif //FSO_CONTROLLER_H