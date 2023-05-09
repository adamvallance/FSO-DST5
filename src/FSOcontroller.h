#ifndef FSO_CONTROLLER_H
#define FSO_CONTROLLER_H

#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "I2CBuffer.h"
#include "GPIOexpander.h"
#include "FullExpandedGPIO.h"
#include <string>

class FSOcontroller{
    DigitalOut nominalRunningLED;
    DigitalOut errorRunningLED;
    PwmOut fanPWM;

    public:
        FSOcontroller(PinName* pins);
        void start();
        void setError();

        int errorStatus = 0;
    private:
        void pollForPower();
        void exec();

        //---------CREATE I2C Interfaces-------
        I2C I2CA ={PIN_I2CA_SDA, PIN_I2CA_SCL};
        I2C I2CB = {PIN_I2CB_SDA, PIN_I2CB_SCL};

        //FullExpandedGPIO expandedGPIO = {&I2CB};
        
        //--------CREATE Xpoint switches -------------

        //--------CREATE SFPs -------------
        std::vector<float> SFPpowers;
        int indexHighestPower = 0;


        //------CREATE MOTOR DRIVER OBJECT------------------
        Thread motorsThread;
        MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0]};

};



#endif //FSO_CONTROLLER_H