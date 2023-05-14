
#ifndef FSO_CONFIG_H
#define FSO_CONFIG_H
#include "stdint.h"
#include "mbed.h"
#include "GPIOexpanderConfig.h"
//Author Adam Vallance
//This file defines operational condition and pin connections as seen on page 7 of the Rev B schematic.

#define VERBOSE_MOTOR_DEBUG
//#define VERBOSE_XPOINT_SWITCH_DEBUG //prints out operations on every switch
//#define ROUTING_TEST //skips routing based on powers and sticks with buttons
#define ROUTE_TX_ONLY_ONE_FIBRE //back propogation method to determine
//#define ROUTE_TX_ONLY_ONE_FIBRE_ROUTE_INDIVIDUALLY //uncomment to do tx routes every poll cycle. Without this the tx are still disabled/enabled using gpios
#define ROUTE_TX_ONLY_ONE_FIBRE_ENABLE_ALL_ON_FLASH //enables flash of all TX on if highest power is less than SFP_LOW_POWER_THRESHOLD
#define DISABLE_FAST_POWER_POLL //add for slow speed polling
//#define DISABLE_POWER_POLL
#define DEBUG_OUTPUT_POWERS //comment this to disable printing of powers.
#define DEBUG_OUTPUT_POWERS_DBM //comment to have in units of uW

// #define POLL_SPEED_TEST
// #define POWER_POLL_SLEEP_FORCE_SWITCH
// #define POWER_POLL_TEST_FORCE_SWITCH
// #define POWER_POLL_FORCE_SWITCH_RX
// #define POWER_POLL_FORCE_SWITCH_TX
// #define POWER_POLL_FORCE_TOGGLE_DISABLE

#ifdef ROUTE_TX_ONLY_ONE_FIBRE
static const float SFP_LOW_POWER_THRESHOLD = 1; //idk set this to better value
#endif
//-----------Operational configuration-------------------------


//general threads
#define POWER_POLL_SLEEP 500ms
#define BLOCKING_SLEEP 1s
#define GPIO_TEST_HALF_PERIOD 500ms
//stepper motors
#define AZIMUTH_STEP_DIR_LEFT 0 //swap these around to invert motor direction
#define AZIMUTH_STEP_DIR_RIGHT 1
#define ELEVATION_STEP_DIR_UP 0
#define ELEVATION_STEP_DIR_DOWN 1
#define HALF_STEP_TIME 2ms //debug change this 
#define TIME_MOTOR_STEPPING 5s //use this and above to set number of steps for default. 
#define MOTOR_SLEEP_TIMEOUT 10s //motor drivers go to low power mode after this time
#define MOTOR_N_STEPS 10
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

//FSO controller pins
static PinName FSO_CONTROLLER_PINS[2] = {PIN_FRDM_LED_GREEN, PIN_FAN_PWM};
//-------------------------------------GPIO Expander Configuration-------------------
static const int GPIO_EXPANDER_ADDRESSES[4] = {0x40, 0x42, 0x44, 0x46};

//for each of these the rows are each gpio expander, the items in each row are for each of the three ports P0, P1 and P2
//SETS PINS TO INPUT (1) or OUTPUT (0) as a mask for 8 BITS
//defaulting to output for NC
//CHECK THESE PX_7 is msb and PX_0 is lsb
static const char PCAL6524_CONFIGURATION[4][3] = {
    {0x0, 0x0, 0x8},  //U2 
    {0x0, 0x0, 0x8}, //U3
    {0x0, 0x55, 0x55}, //U4 //P1 and P2 01010101
    //{0xFF, 0xFF, 0x0F}, //U5 present and los inputs + debug
    {0xFF, 0xFF, 0x2F}, //TP5 as input 
};
//SETS PINS TO PullUp or PullDown (1) or No PullUP/PullDown (0)
static const char PCAL6524_RESISTOR_PULL_ENABLE[4][3] = {
    {0x0, 0x0, 0x8},  //pulled up motor_x_fault
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55}, //pull up all sfp_fault
    //{0xFF, 0xFE, 0x1}, //pull up all present and los

    {0xFF, 0xFE, 0x21}, //debug tp5 input
};
//Sets pins to 1 PU, 0 PD if enabled by mask see above
static const char PCAL6524_RESISTOR_PULL_SELECTION[4][3] = {
    {0x0, 0x0, 0x8},  
    {0x0, 0x0, 0x8},
    {0x0, 0x55, 0x55},
    //{0xFF, 0xFE, 0x1}
    {0xFF, 0xFE, 0x21}, //debug tp5 input
};
//Sets pins to 1 No Interrupt, 0 Interrupt if an input
static const char PCAL6524_INTERRUPT_MASK[4][3] = {
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_1_FAULT_N  
    {0xFF, 0xFF, 0xF7}, //Interrupt on MOTOR_2_FAULT_N
    {0xFF, 0xAA, 0xAA}, //Interrupt all sfp_fault
    //{0xFF, 0xFF, 0x1}, //Interrupt on sfp_out_los but no others
    {0xFF, 0xFF, 0x21} //tp5 as interrupt
};

//Note this is in a different order from schematic, rows align to U4, U5, U2, U3, not as names suggest
//todo clean this up
static PinName GPIO_EXPANDER_FRDM_PINS[4][2] = {
    {PIN_GPIO_3_RESET_N, PIN_GPIO_3_INT_N},
    {PIN_GPIO_4_RESET_N, PIN_GPIO_4_INT_N},
    {PIN_GPIO_1_RESET_N, PIN_GPIO_1_INT_N},
    {PIN_GPIO_2_RESET_N, PIN_GPIO_2_INT_N},


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

static const char GPIO_EXPANDER_RESET[2] = {0x0, 0x6};

//I2C buffers
static const char I2C_BUFFER_ADDRESSES[2] = {0xE0, 0xE2};

static const char I2C_BUFFER_SELECT[8] = {
                                        0xF8, //channel 0 //1 for no reset
                                        0x9, //channel 1
                                        0xA, //channel 2
                                        0xB, //channel 3
                                        0xC, //channel 4
                                        0xD, //channel 5
                                        0xE, //channel 6
                                        0xF, //channel 7
};

//treating sfpOut as sfp0
static const char I2C_BUFFER_SELECT_SFP[8][2] = {
    {I2C_BUFFER_ADDRESSES[1], I2C_BUFFER_SELECT[0]}, //sfp0 (OUT) on channel 0 buf 1 (U21)
    {I2C_BUFFER_ADDRESSES[0], I2C_BUFFER_SELECT[3]}, //SFP1 on channel 3 buf 0 (u6)
    {I2C_BUFFER_ADDRESSES[0], I2C_BUFFER_SELECT[0]}, //sfp2 on channel 0 buf 0
    {I2C_BUFFER_ADDRESSES[0], I2C_BUFFER_SELECT[1]}, //sfp3 on channel 1 buf 0
    {I2C_BUFFER_ADDRESSES[0], I2C_BUFFER_SELECT[2]}, //sfp4 on channel 2 buf 0
    {I2C_BUFFER_ADDRESSES[1], I2C_BUFFER_SELECT[3]}, //sfp5 on channel 3 buf 1
    {I2C_BUFFER_ADDRESSES[1], I2C_BUFFER_SELECT[2]}, //sfp6 on channel 2 buf 1
    {I2C_BUFFER_ADDRESSES[1], I2C_BUFFER_SELECT[1]}, //sfp7 on channel 1 buf 1
};

static const char I2C_BUFFER_RESET = 0x8;
static const char I2C_BUFFER_NO_SELECTION = 0x0;


//------------xpoints
//register addresses
static const char XPOINT_OUTPUT_PORT_0 = 0x0;
static const char XPOINT_OUTPUT_PORT_1 = 0x1;
static const char XPOINT_OUTPUT_PORT_2 = 0x2;
static const char XPOINT_OUTPUT_PORT_3 = 0x3;
static const char XPOINT_OUTPUT_PORT_4 = 0x4;
static const char XPOINT_OUTPUT_PORT_5 = 0x5;
static const char XPOINT_OUTPUT_PORT_6 = 0x6;
static const char XPOINT_OUTPUT_PORT_7 = 0x7;
static const char XPOINT_INPUT_PORT_0 = 0x8;
static const char XPOINT_INPUT_PORT_1 = 0x9;
static const char XPOINT_INPUT_PORT_2 = 0xA;
static const char XPOINT_INPUT_PORT_3 = 0xB;
static const char XPOINT_INPUT_PORT_4 = 0xC;
static const char XPOINT_INPUT_PORT_5 = 0xD;
static const char XPOINT_INPUT_PORT_6 = 0xE;
static const char XPOINT_INPUT_PORT_7 = 0xF;
static const char XPOINT_SWITCH_CONTROL = 0x10;

static const char XPOINT_OUTPUT_PORTS[8]={
    XPOINT_OUTPUT_PORT_0,
    XPOINT_OUTPUT_PORT_1,
    XPOINT_OUTPUT_PORT_2,
    XPOINT_OUTPUT_PORT_3,
    XPOINT_OUTPUT_PORT_4,
    XPOINT_OUTPUT_PORT_5,
    XPOINT_OUTPUT_PORT_6,
    XPOINT_OUTPUT_PORT_7,
};
static const char XPOINT_INPUT_PORTS[8]={
    XPOINT_INPUT_PORT_0,
    XPOINT_INPUT_PORT_1,
    XPOINT_INPUT_PORT_2,
    XPOINT_INPUT_PORT_3,
    XPOINT_INPUT_PORT_4,
    XPOINT_INPUT_PORT_5,
    XPOINT_INPUT_PORT_6,
    XPOINT_INPUT_PORT_7,
};


static const char XPOINT_TX_I2C_ADDRESS = 0x58;
static const char XPOINT_RX_I2C_ADDRESS = 0x5A; 

static const char XPOINT_CLEAR_TX[8][2]{ //to clear tx connect to port 1 (grounded)
    {XPOINT_OUTPUT_PORTS[0], 0x20}, //set to channel 1 //ABCXXXX, ABC = OUTPUT PORT NO
    {XPOINT_OUTPUT_PORTS[1], 0x20}, 
    {XPOINT_OUTPUT_PORTS[2], 0x20}, 
    {XPOINT_OUTPUT_PORTS[3], 0x20}, 
    {XPOINT_OUTPUT_PORTS[4], 0x20}, 
    {XPOINT_OUTPUT_PORTS[5], 0x20}, 
    {XPOINT_OUTPUT_PORTS[6], 0x20}, 
    {XPOINT_OUTPUT_PORTS[7], 0x20}
};

static const char XPOINT_ROUTE_TX[8][2]{
    {XPOINT_OUTPUT_PORTS[0], 0}, 
    {XPOINT_OUTPUT_PORTS[1], 0}, 
    {XPOINT_OUTPUT_PORTS[2], 0}, 
    {XPOINT_OUTPUT_PORTS[3], 0}, 
    {XPOINT_OUTPUT_PORTS[4], 0}, 
    {XPOINT_OUTPUT_PORTS[5], 0}, 
    {XPOINT_OUTPUT_PORTS[6], 0}, 
    {XPOINT_OUTPUT_PORTS[7], 0} //not used
};

static const char XPOINT_ROUTE_RX[8][2]{ //ABCXXXXX, ABC = OUTPUT PORT NO 
    {XPOINT_OUTPUT_PORTS[0], 0xC0}, //sfp1 //channel 6
    {XPOINT_OUTPUT_PORTS[0], 0xA0}, //sfp2 //channel 5
    {XPOINT_OUTPUT_PORTS[0], 0x80}, //sfp3 //channel 4
    {XPOINT_OUTPUT_PORTS[0], 0x60}, //sfp4 //channel 3
    {XPOINT_OUTPUT_PORTS[0], 0x40}, //sfp5 //channel 2
    {XPOINT_OUTPUT_PORTS[0], 0x20}, //sfp6 //channel 1
    {XPOINT_OUTPUT_PORTS[0], 0}, //sfp7 //channel 0
    {XPOINT_OUTPUT_PORTS[0], 0}, //not used
};

//Motors Pin list
static PinName motor_controls_out[4] = {PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR};
static PinName motor_controls_in[4]={PIN_MOTOR_DIR_CTRL_UP, PIN_MOTOR_DIR_CTRL_DOWN, PIN_MOTOR_DIR_CTRL_LEFT, PIN_MOTOR_DIR_CTRL_RIGHT};

//-------------SFPs
static const char SFP_I2C_ADDRESS = 0xA2;

//I2C Addresses of devices and selected registers.
static const char SFP_RX_POWER_REG_ADDRESS = 0x68;
static int SFP_POWER_BYTE_LEN = 2;
static const GPIOexpanderPin SFP_TX_DISABLE[8] = {
    GPIO_SFP_OUT_TX_DISABLE,
    GPIO_SFP_1_TX_DISABLE,
    GPIO_SFP_2_TX_DISABLE,
    GPIO_SFP_3_TX_DISABLE,
    GPIO_SFP_4_TX_DISABLE,
    GPIO_SFP_5_TX_DISABLE,
    GPIO_SFP_6_TX_DISABLE,
    GPIO_SFP_7_TX_DISABLE,

};

static const float POWER_READING_CONV_DBM = 1e-4; //MULTIPLICATION
static const int POWER_READING_CONV_UW = 0.1;//MULTIPLICATION


#endif //FSO_CONFIG_H