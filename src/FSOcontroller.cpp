#include "FSOcontroller.h"
//------Pin definitions-------
//unfortunately these could not be declared as members of the class rather as globals within this file.

//I2C interfaces
I2C I2CA(PTB1, PTB0);
I2C I2CB(PTE0, PTE1);
//Fan control pwm
PwmOut FANS(PTA13);
//---FRDM LEDs----
DigitalOut FRDM_LED_RED(LED1);
DigitalOut FRDM_LED_GREEN(LED2);
DigitalOut FRDM_LED_BLUE(LED3); //connected internally to MOTOR_DIR_CTRL_UP
//---GPIO EXPANDERS----
//gpio expander resets 
DigitalOut GPIO_1_RESET_N(PTC8);
DigitalOut GPIO_2_RESET_N(PTA4);
DigitalOut GPIO_3_RESET_N(PTD4);
DigitalOut GPIO_4_RESET_N(PTA1);
//gpio expander interrupt
DigitalIn GPIO_1_INT_N(PTC9);
DigitalIn GPIO_2_INT_N(PTA5);
DigitalIn GPIO_3_INT_N(PTA12);
DigitalIn GPIO_4_INT_N(PTA2);
//---MOTORS----
//motor control digital outs
DigitalOut MOTOR_1_STEP(PTB2);
DigitalOut MOTOR_1_DIR(PTB3);
DigitalOut MOTOR_2_STEP(PTC2);
DigitalOut MOTOR_2_DIR(PTC1);
//motor inputs from buttons
DigitalIn MOTOR_DIR_CTRL_UP(PTD1); //connected internally to FRDM_LED_BLUE
DigitalIn MOTOR_DIR_CTRL_DOWN(PTD3);
DigitalIn MOTOR_DIR_CTRL_RIGHT(PTD2);
DigitalIn MOTOR_DIR_CTRL_LEFT(PTD0);


FSOcontroller::FSOcontroller(){
    initGPIOs();
    while (true) {
        FRDM_LED_RED = !FRDM_LED_RED;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}

void FSOcontroller::initGPIOs(){
    //turn board LEDs off, weirdly they are active low.
    FRDM_LED_RED = 1;
    FRDM_LED_GREEN = 1;
    FRDM_LED_BLUE = 1;
}

// void FSOcontroller::test(){
//     ;//frdm_led_red = 1;
// }

