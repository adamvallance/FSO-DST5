/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "config.h"

#include "motorDriver.h"
// //------Pin definitions-------
// //unfortunately these could not be declared as members of the class rather as globals within this file.
// //I2C interfaces
// I2C I2CA(PTB1, PTB0);
// I2C I2CB(PTE0, PTE1);
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


class FSOcontroller{

    public:

        FSOcontroller(){
            initGPIOs();
            PinName motor_controls_out[5]={PIN_FRDM_LED_RED, PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR};
            PinName motor_controls_in[4]={PIN_MOTOR_DIR_CTRL_UP, PIN_MOTOR_DIR_CTRL_DOWN, PIN_MOTOR_DIR_CTRL_LEFT, PIN_MOTOR_DIR_CTRL_RIGHT};
            MotorDriver motorDriver(&motor_controls_out[0], &motor_controls_in[0]);
        }
    private:

        void initGPIOs(){
            //turn board LEDs off, weirdly they are active low.
            // FRDM_LED_RED = 1;
            // FRDM_LED_GREEN = 1;
            // FRDM_LED_BLUE = 1;
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