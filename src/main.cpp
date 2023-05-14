/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "FSOcontroller.h"
#include "tester.h"
#include "I2CBuffers.h"
#include "xpoint.h"
#include <cmath>


int main()
{   
    printf("Initialising...\n");


    //Create expanded gpio interface
    FullExpandedGPIO expandedGPIO;
    //Create I2C buffers
    I2CBuffers i2cbufs = {&expandedGPIO};
    //Create XPoint switches 
    XPoints xpoints = {&expandedGPIO};

        // // //------CREATE MOTOR DRIVER OBJECT------------------
    
    Thread motorsThread;

    MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0], &expandedGPIO};
    //start motors thread
    motorsThread.start(callback(&motorDriver, &MotorDriver::start));


    //gpio test, make sure gpio expander interrupts are off until crash is fixed
    #ifdef ROUTING_TEST
    Thread testerThread;

    testClass test = {&expandedGPIO, &i2cbufs, &xpoints, &motor_controls_in[0]};
    testerThread.start(callback(&test, &testClass::start));
    while(true){
        ThisThread::sleep_for(100ms);
    }
    #else //normal operation
    //testClass test = {&expandedGPIO, &i2cbufs, &xpoints};
    //testerThread.start(callback(&test, &testClass::toggleDebugGPIO));
    //testerThread.start(callback(&test, &testClass::I2CbufferTest));
    //testerThread.start(callback(&test, &testClass::XPointsTest));

        //Thread controllerThread;
    //create main controller class instantce
    FSOcontroller controller = {&FSO_CONTROLLER_PINS[0], &expandedGPIO, &i2cbufs, &xpoints}; 


    //start the controller to poll for power
    controller.start(); //blocking, has infinite execution loop inside
    #endif



}