/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
// //------Pin definitions-------

// //Fan control pwm
// PwmOut FANS(PTA13);
// //---FRDM LEDs----
// DigitalOut FRDM_LED_RED(PIN_FRDM_LED_RED);
// DigitalOut FRDM_LED_GREEN(PIN_FRDM_LED_GREEN);
// DigitalOut FRDM_LED_BLUE(PIN_FRDM_LED_BLUE); //connected internally to MOTOR_DIR_CTRL_UP
// //---GPIO EXPANDERS----
// //gpio expander resets 
// DigitalOut GPIO_1_RESET_N(PTC8);
// DigitalOut GPIO_2_RESET_N(PTA4);
// DigitalOut GPIO_3_RESET_N(PTD4);
// DigitalOut GPIO_4_RESET_N(PTA1);

// //gpio expander interrupt
// //InterruptIn GPIO_1_INT_N(PTC9); //PROBLEM SETTING THIS TO BE AN INTERRUPT. Tried excluding I2C. This needed for fault detection on motor 1.
// InterruptIn GPIO_2_INT_N(PTA5);
// InterruptIn GPIO_3_INT_N(PTA12);
// InterruptIn GPIO_4_INT_N(PTA2);
// //---MOTORS----


//make motors thread
//make main thread
//DigitalOut greenLED(PIN_FRDM_LED_GREEN);
DigitalOut tempRunning(PIN_FRDM_LED_GREEN);
//DigitalOut errorLED(PIN_FRDM_LED_RED);
class FSOcontroller{

    public:
        FSOcontroller() = default;

        //---------CREATE I2C Interfaces-------
        I2C I2C_A ={PIN_I2CA_SDA, PIN_I2CA_SCL};
        I2C I2C_B = {PIN_I2CB_SDA, PIN_I2CB_SCL};

        //Thread mainThread;
        //------CREATE MOTOR DRIVERS OBJECTS------------------
        Thread azimuthMotorsThread;
        Thread elevationMotorsThread;

        PinName azimuthMotorPins[4] = {PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_DIR_CTRL_LEFT, PIN_MOTOR_DIR_CTRL_RIGHT};
        PinName elevationMotorPins[4] = {PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR, PIN_MOTOR_DIR_CTRL_UP, PIN_MOTOR_DIR_CTRL_DOWN};

        MotorDriver azimuthMotor = {&azimuthMotorPins[0], static_cast<bool>(AZIMUTH_STEP_DIR_LEFT)}; 
        MotorDriver elevationMotor = {&elevationMotorPins[0], static_cast<bool>(ELEVATION_STEP_DIR_UP)}; 

        
        //starts member threads and begins main execution loop. 
        void start(){
            //start motors threads
            azimuthMotorsThread.start(callback(&(this->azimuthMotor), &MotorDriver::start));
            //elevationMotorsThread.start(callback(&(this->elevationMotor), &MotorDriver::start));

            //start main polling thread
            //mainThread.start(callback(this, &FSOcontroller::exec));
            exec();
        }

        std::vector<int> SFPpower;


        //endless execution loop
        void exec(){
            while(true){
                //pollForPower();
                tempRunning = !tempRunning;
                ThisThread::sleep_for(POWER_POLL_SLEEP);
            }
        }

        //Thread pollThread;
        std::vector<int> pollForPower(){
            for (int sfp = 1; sfp<8; sfp++){
                //poll for power
                //SFPpower[sfp-1] = power;
                ;
            }
            //debug print sfp powers                
            return SFPpower;
        }

    private:



};



int main()
{   
    FSOcontroller controller;
    controller.start();
}