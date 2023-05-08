
#ifndef FSO_CONFIG_H
#define FSO_CONFIG_H
#include "stdint.h"
//Author Adam Vallance
//This file defines operational condition and pin connections as seen on page 7 of the Rev B schematic.


//-----------Operational configuration-------------------------
#define DEBUG_OUTPUT_POWERS //comment this to disable printing of powers.


//general threads
#define POWER_POLL_SLEEP 100ms
#define BLOCKING_SLEEP 1000ms
//stepper motors
#define AZIMUTH_STEP_DIR_LEFT 0 //swap these around to invert motor direction
#define AZIMUTH_STEP_DIR_RIGHT 1
#define ELEVATION_STEP_DIR_UP 0
#define ELEVATION_STEP_DIR_DOWN 1
#define HALF_STEP_TIME 200ms //debug change this 
#define TIME_MOTOR_STEPPING 5s //use this and above to set number of steps for default. 



//I2C Addresses of devices and selected registers.
#define I2C_SFP_ADDRESS 0xA2
#define SFP_RX_POWER_ADDRESS 104 
#define SFP_POWER_BYTE_LEN 2

//FAN
#define FAN_PWM_DUTY 0.5
#define FAN_PWM_PERIOD 0.00005 //20kHz

//-------------------------------------GPIO Expander Configuration-------------------
//for each of these the rows are each gpio expander, the items in each row are for each of the three ports P0, P1 and P2

//SETS PINS TO INPUT (1) or OUTPUT (0) as a mask for 8 BITS
//defaulting to output for NC
const char PCAL6524_CONFIGURATION[4][3] = {
    {0x0, 0x0, 0x8},  //U2 
    {0x0, 0x0, 0x8}, //U3
    {0x0, 0x55, 0x55}, //U4 //P1 and P2 01010101
    {0xFF, 0xFE, 0x40}, //U5 present and los inputs + debug
};
//SETS PINS TO PullUp or PullDown (1) or No PullUP/PullDown (0)
const char PCAL6524_RESISTOR_PULL_ENABLE[4][3] = {
    {0x0, 0x0, 0x8},  //pulled up motor_x_fault
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55}, //pull up all sfp_fault
    {0xFF, 0xFE, 0x0}, //pull up all present and los
};
//Sets pins to 1 PU, 0 PD if enabled by mask see above
const char PCAL6524_RESISTOR_PULL_SELECTION[4][3] = {
    {0x0, 0x0, 0x8},  
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55},
    {0xFF, 0xFE, 0x0},
};
//Sets pins to 1 No Interrupt, 0 Interrupt if an input
const char PCAL6524_INTERRUPT_MASK[4][3] = {
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_1_FAULT_N  
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_2_FAULT_N
    {0xFF, 0xAA, 0xAA}, //Interrupt all sfp_fault
    {0xFF, 0xFF, 0xFF}, //Interrupt on sfp_out_los but no others
};

//maybe add interrupt on sfp_out_los (PCAL6524_Interupt_mask[4][3]=FE)
//Should be default configured as push-pull with logic 0s in 0x5C, see table 40

//-------------------------------------PINOUT-------------------
//note we are already using half as many pins as we have available due to extra head row not utilised so gpio could be decreased
//---FRDM LEDs----
#define PIN_FRDM_LED_RED LED1
#define PIN_FRDM_LED_GREEN LED2
#define PIN_FRDM_LED_BLUE LED3// Internally connected to PTD1
//Fan control pwm
#define PIN_FAN_PWM PTA13

//I2C. Note that 'I2CA' here corresponds to 'I2C_0' on the schematic whilst 'I2CB' corresponds to 'I2C'
#define PIN_I2CA_SDA PTB1
#define PIN_I2CA_SCL PTB0
#define PIN_I2CB_SDA PTE0
#define PIN_I2CB_SCL PTE1

//---GPIO EXPANDERS----
//gpio expander resets 
#define PIN_GPIO_1_RESET_N PTC8
#define PIN_GPIO_2_RESET_N PTA4
#define PIN_GPIO_3_RESET_N PTD4
#define PIN_GPIO_4_RESET_N PTA1
//gpio expander interrupt
#define PIN_GPIO_1_INT_N PTC9 //having issues setting this as an interrupt.
#define PIN_GPIO_2_INT_N PTA5
#define PIN_GPIO_3_INT_N PTA12
#define PIN_GPIO_4_INT_N PTA2

//---MOTORS----
//motor control digital outs
#define PIN_MOTOR_1_STEP PTB2
#define PIN_MOTOR_1_DIR PTB3
#define PIN_MOTOR_2_STEP PTC2
#define PIN_MOTOR_2_DIR PTC1
//motor input buttons
#define PIN_MOTOR_DIR_CTRL_UP PTD1
#define PIN_MOTOR_DIR_CTRL_DOWN PTD3
#define PIN_MOTOR_DIR_CTRL_LEFT PTD0
#define PIN_MOTOR_DIR_CTRL_RIGHT PTD2

#endif //FSO_CONFIG_H