
#ifndef FSO_MOTOR_DRIVER_H
#define FSO_MOTOR_DRIVER_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGPIO.h"

class MotorDriver{
    FullExpandedGPIO* gpios;
    DigitalOut motor1Step;
    DigitalOut motor1Dir;
    DigitalOut motor2Step;
    DigitalOut motor2Dir;
    
    DigitalIn motorDirCtrlUp;
    DigitalIn motorDirCtrlDown;
    DigitalIn motorDirCtrlLeft;
    DigitalIn motorDirCtrlRight;

    DigitalOut led;

    DigitalOut* steps[2] = {&motor1Step, &motor2Step};

    public:
        MotorDriver(PinName*, FullExpandedGPIO*); 
        void stepMotor(int);
        void start();

    private: 
    void doStep(int );

        void exec();
        void readInputs();
        void applySettings();


    ;
};

#endif //FSO_CONTROLLER_H