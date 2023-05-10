/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "FSOcontroller.h"


int main()
{   
    printf("Initialising...\n");
    //---------CREATE I2C Interfaces-------
    I2C I2CA ={PIN_I2CA_SDA, PIN_I2CA_SCL};
    I2C I2CB = {PIN_I2CB_SDA, PIN_I2CB_SCL};

    FullExpandedGPIO expandedGPIO = {&I2CB};
    gpioTestClass test = {&expandedGPIO};
    
    //--------CREATE Xpoint switches -------------

    //--------CREATE SFPs -------------
    std::vector<float> SFPpowers;
    int indexHighestPower = 0;


    //------CREATE MOTOR DRIVER OBJECT------------------
    Thread motorsThread;
    MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0]};
    //start motors thread
    motorsThread.start(callback(&motorDriver, &MotorDriver::start));

    //create main controller class instantce
    FSOcontroller controller = {&FSO_CONTROLLER_PINS[0], &expandedGPIO, &I2CA, &I2CB};
    //start the controller to poll for power
    controller.start(); //blocking, has infinite execution loop inside
}