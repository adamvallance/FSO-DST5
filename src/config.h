
#ifndef FSO_CONFIG_H
#define FSO_CONFIG_H
#include "stdint.h"
#include "mbed.h"
#include "GPIOexpanderConfig.h"
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


//-------------------------------------GPIO Expander Configuration-------------------
static const int GPIO_EXPANDER_ADDRESSES[4] = {0x20, 0x21, 0x22, 0x23};

//for each of these the rows are each gpio expander, the items in each row are for each of the three ports P0, P1 and P2
//SETS PINS TO INPUT (1) or OUTPUT (0) as a mask for 8 BITS
//defaulting to output for NC
static const char PCAL6524_CONFIGURATION[4][3] = {
    {0x0, 0x0, 0x8},  //U2 
    {0x0, 0x0, 0x8}, //U3
    {0x0, 0x55, 0x55}, //U4 //P1 and P2 01010101
    {0xFF, 0xFE, 0x40}, //U5 present and los inputs + debug
};
//SETS PINS TO PullUp or PullDown (1) or No PullUP/PullDown (0)
static const char PCAL6524_RESISTOR_PULL_ENABLE[4][3] = {
    {0x0, 0x0, 0x8},  //pulled up motor_x_fault
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55}, //pull up all sfp_fault
    {0xFF, 0xFE, 0x0}, //pull up all present and los
};
//Sets pins to 1 PU, 0 PD if enabled by mask see above
static const char PCAL6524_RESISTOR_PULL_SELECTION[4][3] = {
    {0x0, 0x0, 0x8},  
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55},
    {0xFF, 0xFE, 0x0},
};
//Sets pins to 1 No Interrupt, 0 Interrupt if an input
static const char PCAL6524_INTERRUPT_MASK[4][3] = {
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_1_FAULT_N  
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_2_FAULT_N
    {0xFF, 0xAA, 0xAA}, //Interrupt all sfp_fault
    {0xFF, 0xFF, 0xFF}, //Interrupt on sfp_out_los but no others
};

static PinName GPIO_EXPANDER_PINS[4][2] = {
    {PIN_GPIO_1_RESET_N, PIN_GPIO_1_INT_N},
    {PIN_GPIO_2_RESET_N, PIN_GPIO_2_INT_N},
    {PIN_GPIO_3_RESET_N, PIN_GPIO_3_INT_N},
    {PIN_GPIO_4_RESET_N, PIN_GPIO_4_INT_N},

};
//maybe add interrupt on sfp_out_los (PCAL6524_Interupt_mask[4][3]=FE)
//Should be default configured as push-pull with logic 0s in 0x5C, see table 40

struct GPIOexpanderPin{
    uint8_t gpioExIndex;
    uint16_t gpioExPinNumber;
};

//GPIO Accessible Pins. Defigned as GPIO expander index, gpio expander pin
//GPIO EXPANDER 0 (U2)
static const GPIOexpanderPin GPIO_MOTOR_1_ADEC = {0, P0_0};
static const GPIOexpanderPin GPIO_MOTOR_1_ENBL_N = {0, P0_1};
static const GPIOexpanderPin GPIO_MOTOR_1_SLEEP_N = {0, P0_2};
static const GPIOexpanderPin GPIO_MOTOR_1_DEC0_OE_N = {0, P0_4};
static const GPIOexpanderPin GPIO_MOTOR_1_DEC0 = {0, P0_5};
static const GPIOexpanderPin GPIO_MOTOR_1_DEC1_OE_N = {0, P0_6};
static const GPIOexpanderPin GPIO_MOTOR_1_DEC1 = {0, P0_7};
static const GPIOexpanderPin GPIO_MOTOR_1_I0_OE_N = {0, P1_0};
static const GPIOexpanderPin GPIO_MOTOR_1_I0 = {0, P1_1};
static const GPIOexpanderPin GPIO_MOTOR_1_I1_OE_N = {0, P1_2};
static const GPIOexpanderPin GPIO_MOTOR_1_I1 = {0, P1_3};
static const GPIOexpanderPin GPIO_MOTOR_1_M0_OE_N = {0, P1_4};
static const GPIOexpanderPin GPIO_MOTOR_1_M0 = {0, P1_5};
static const GPIOexpanderPin GPIO_MOTOR_1_M1_OE_N = {0, P1_6};
static const GPIOexpanderPin GPIO_MOTOR_1_M1 = {0, P1_7};
static const GPIOexpanderPin GPIO_MOTOR_1_TOFF_OE_N = {0, P2_0};
static const GPIOexpanderPin GPIO_MOTOR_1_TOFF = {0, P2_1};
static const GPIOexpanderPin GPIO_MOTOR_1_FAULT_N = {0, P2_3};

//GPIO EXPANDER 1 (U3)
static const GPIOexpanderPin GPIO_MOTOR_2_ADEC = {1, P0_0};
static const GPIOexpanderPin GPIO_MOTOR_2_ENBL_N = {1, P0_1};
static const GPIOexpanderPin GPIO_MOTOR_2_SLEEP_N = {1, P0_2};
static const GPIOexpanderPin GPIO_MOTOR_2_DEC0_OE_N = {1, P0_4};
static const GPIOexpanderPin GPIO_MOTOR_2_DEC0 = {1, P0_5};
static const GPIOexpanderPin GPIO_MOTOR_2_DEC1_OE_N = {1, P0_6};
static const GPIOexpanderPin GPIO_MOTOR_2_DEC1 = {1, P0_7};
static const GPIOexpanderPin GPIO_MOTOR_2_I0_OE_N = {1, P1_0};
static const GPIOexpanderPin GPIO_MOTOR_2_I0 = {1, P1_1};
static const GPIOexpanderPin GPIO_MOTOR_2_I1_OE_N = {1, P1_2};
static const GPIOexpanderPin GPIO_MOTOR_2_I1 = {1, P1_3};
static const GPIOexpanderPin GPIO_MOTOR_2_M0_OE_N = {1, P1_4};
static const GPIOexpanderPin GPIO_MOTOR_2_M0 = {1, P1_5};
static const GPIOexpanderPin GPIO_MOTOR_2_M1_OE_N = {1, P1_6};
static const GPIOexpanderPin GPIO_MOTOR_2_M1 = {1, P1_7};
static const GPIOexpanderPin GPIO_MOTOR_2_TOFF_OE_N = {1, P2_0};
static const GPIOexpanderPin GPIO_MOTOR_2_TOFF = {1, P2_1};
static const GPIOexpanderPin GPIO_MOTOR_2_FAULT_N = {1, P2_3};

//GPIO EXPANDER 2 (U4)
static const GPIOexpanderPin GPIO_XPOINT_RX_EQ = {2, P0_0};
static const GPIOexpanderPin GPIO_XPOINT_RX_PRE = {2, P0_1};
static const GPIOexpanderPin GPIO_XPOINT_RX_SWT = {2, P0_2};
static const GPIOexpanderPin GPIO_XPOINT_TX_EQ = {2, P0_3};
static const GPIOexpanderPin GPIO_XPOINT_TX_PRE = {2, P0_4};
static const GPIOexpanderPin GPIO_XPOINT_TX_SWT = {2, P0_5};
static const GPIOexpanderPin GPIO_XPOINT_RX_RES_N = {2, P0_6};
static const GPIOexpanderPin GPIO_XPOINT_TX_RES_N = {2, P0_7};
static const GPIOexpanderPin GPIO_SFP_1_TX_FAULT = {2, P1_0};
static const GPIOexpanderPin GPIO_SFP_1_TX_DISABLE = {2, P1_1};
static const GPIOexpanderPin GPIO_SFP_2_TX_FAULT = {2, P1_2};
static const GPIOexpanderPin GPIO_SFP_2_TX_DISABLE = {2, P1_3};
static const GPIOexpanderPin GPIO_SFP_3_TX_FAULT = {2, P1_4};
static const GPIOexpanderPin GPIO_SFP_3_TX_DISABLE = {2, P1_5};
static const GPIOexpanderPin GPIO_SFP_4_TX_FAULT = {2, P1_6};
static const GPIOexpanderPin GPIO_SFP_4_TX_DISABLE = {2, P1_7};
static const GPIOexpanderPin GPIO_SFP_5_TX_FAULT = {2, P2_0};
static const GPIOexpanderPin GPIO_SFP_5_TX_DISABLE = {2, P2_1};
static const GPIOexpanderPin GPIO_SFP_6_TX_FAULT = {2, P2_2};
static const GPIOexpanderPin GPIO_SFP_6_TX_DISABLE = {2, P2_3};
static const GPIOexpanderPin GPIO_SFP_7_TX_FAULT = {2, P2_4};
static const GPIOexpanderPin GPIO_SFP_7_TX_DISABLE = {2, P2_5};
static const GPIOexpanderPin GPIO_SFP_OUT_TX_FAULT = {2, P2_6};
static const GPIOexpanderPin GPIO_SFP_OUT_TX_DISABLE = {2, P2_7};

//GPIO EXPANDER 3 (U5)
static const GPIOexpanderPin GPIO_SFP_OUT_PRESENT = {3, P0_0};
static const GPIOexpanderPin GPIO_SFP_7_PRESENT = {3, P0_1};
static const GPIOexpanderPin GPIO_SFP_6_PRESENT = {3, P0_2};
static const GPIOexpanderPin GPIO_SFP_5_PRESENT = {3, P0_3};
static const GPIOexpanderPin GPIO_SFP_4_PRESENT = {3, P0_4};
static const GPIOexpanderPin GPIO_SFP_3_PRESENT = {3, P0_5};
static const GPIOexpanderPin GPIO_SFP_2_PRESENT = {3, P0_6};
static const GPIOexpanderPin GPIO_SFP_1_PRESENT = {3, P0_7};
static const GPIOexpanderPin GPIO_SFP_1_LOS = {3, P1_1};
static const GPIOexpanderPin GPIO_SFP_2_LOS = {3, P1_2};
static const GPIOexpanderPin GPIO_SFP_3_LOS = {3, P1_3};
static const GPIOexpanderPin GPIO_SFP_4_LOS = {3, P1_4};
static const GPIOexpanderPin GPIO_SFP_5_LOS = {3, P1_5};
static const GPIOexpanderPin GPIO_SFP_6_LOS = {3, P1_6};
static const GPIOexpanderPin GPIO_SFP_7_LOS = {3, P1_7};
static const GPIOexpanderPin GPIO_SFP_OUT_LOS = {3, P2_0};
static const GPIOexpanderPin GPIO_I2CB_SFP_RESET_N = {3, P2_2};
static const GPIOexpanderPin GPIO_I2CA_SFP_RESET_N = {3, P2_3};
static const GPIOexpanderPin GPIO_DEBUG_LOOP_A = {3, P2_5};
static const GPIOexpanderPin GPIO_DEBUG_LOOP_B = {3, P2_6};
static const GPIOexpanderPin GPIO_DEBUG_LED = {3, P2_7};



//Motors Pin list
static PinName motor_controls_out[4] = {PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR};
static PinName motor_controls_in[4]={PIN_MOTOR_DIR_CTRL_UP, PIN_MOTOR_DIR_CTRL_DOWN, PIN_MOTOR_DIR_CTRL_LEFT, PIN_MOTOR_DIR_CTRL_RIGHT};




#endif //FSO_CONFIG_H