/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "FSOcontroller.h"
#include "tester.h"
#include "I2CBuffers.h"


int main()
{   
    printf("Initialising...\n");


    //Create expanded gpio interface
    FullExpandedGPIO expandedGPIO;
    I2CBuffers i2cbufs = {&expandedGPIO};

    //gpio test, make sure only one gpio expander initialised
    Thread testerThread;

    testClass test = {&expandedGPIO, &i2cbufs};
    //testerThread.start(callback(&test, &testClass::toggleDebugGPIO));
    testerThread.start(callback(&test, &testClass::I2CbufferTest));

    //--------CREATE Xpoint switches -------------

    //--------CREATE SFPs -------------
    std::vector<float> SFPpowers;
    int indexHighestPower = 0;


    // //------CREATE MOTOR DRIVER OBJECT------------------
    
    // Thread motorsThread;

    // MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0]};
    // //start motors thread
    // motorsThread.start(callback(&motorDriver, &MotorDriver::start));

    //Thread controllerThread;
    //create main controller class instantce
    FSOcontroller controller = {&FSO_CONTROLLER_PINS[0], &expandedGPIO}; 
    //start the controller to poll for power
    controller.start(); //blocking, has infinite execution loop inside
}