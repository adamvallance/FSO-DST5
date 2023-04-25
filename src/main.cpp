/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "motorDriver.h"
//------Pin definitions-------
//unfortunately these could not be declared as members of the class rather as globals within this file.
//note we are already using half as many pins as we have available due to extra head row not utilised so gpio could be decreased
//I2C interfaces
I2C I2CA(PTB1, PTB0);
I2C I2CB(PTE0, PTE1);
//Fan control pwm
PwmOut FANS(PTA13);
//---FRDM LEDs----
DigitalOut FRDM_LED_RED(LED1);
DigitalOut FRDM_LED_GREEN(LED2);
// //DigitalOut FRDM_LED_BLUE(LED3); //connected internally to MOTOR_DIR_CTRL_UP
//---GPIO EXPANDERS----
//gpio expander resets 
DigitalOut GPIO_1_RESET_N(PTC8);
DigitalOut GPIO_2_RESET_N(PTA4);
DigitalOut GPIO_3_RESET_N(PTD4);
DigitalOut GPIO_4_RESET_N(PTA1);

//gpio expander interrupt
//InterruptIn GPIO_1_INT_N(PTC9); //PROBLEM SETTING THIS TO BE AN INTERRUPT. Tried excluding I2C. This needed for fault detection on motor 1.
InterruptIn GPIO_2_INT_N(PTA5);
InterruptIn GPIO_3_INT_N(PTA12);
InterruptIn GPIO_4_INT_N(PTA2);
//---MOTORS----
//motor control digital outs
// DigitalOut MOTOR_1_STEP(PTB2);
// DigitalOut MOTOR_1_DIR(PTB3);
// DigitalOut MOTOR_2_STEP(PTC2);
// DigitalOut MOTOR_2_DIR(PTC1);
//DigitalOut MOTOR_CONTROLS_OUT[] = {LED1, MOTOR_1_STEP, MOTOR_1_DIR, MOTOR_2_STEP, MOTOR_2_DIR};
PinName motor_controls_out[5]={LED1, PTB2, PTB3, PTC2, PTC1};

// //motor inputs from buttons. //Non copyable so assigned directly to motor controller
InterruptIn MOTOR_DIR_CTRL_UP(PTD1); //connected internally to FRDM_LED_BLUE
InterruptIn MOTOR_DIR_CTRL_DOWN(PTD3);
InterruptIn MOTOR_DIR_CTRL_RIGHT(PTD2);
InterruptIn MOTOR_DIR_CTRL_LEFT(PTD0);
PinName motor_controls_in[] = {PTD1, PTD3, PTD2, PTD0};

class FSOcontroller{
    public:
        FSOcontroller(){
            initGPIOs();
            MotorDriver motorDriver(&motor_controls_out[0]);
        }
    private:

        void initGPIOs(){
            //turn board LEDs off, weirdly they are active low.
            FRDM_LED_RED = 1;
            FRDM_LED_GREEN = 1;
            //FRDM_LED_BLUE = 1;
        }

        void registerInterruptCallbacks(){
            // MOTOR_DIR_CTRL_UP.fall(callback(&motorDriver));
            // MOTOR_DIR_CTRL_DOWN.fall();
            // MOTOR_DIR_CTRL_LEFT.fall();
            // MOTOR_DIR_CTRL_RIGHT.fall();
        }

};



int main()
{
    FSOcontroller();
}