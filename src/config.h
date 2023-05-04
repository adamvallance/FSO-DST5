
#ifndef FSO_CONFIG_H
#define FSO_CONFIG_H
//Author Adam Vallance
//This file defines all pin connections as seen on page 7 of the Rev B schematic.
//note we are already using half as many pins as we have available due to extra head row not utilised so gpio could be decreased



//#define STEP_SLEEP_TIME 10 
#define POWER_POLL_SLEEP 100ms
#define BLOCKING_SLEEP 1000ms

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