/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "config.h"
#include <vector>
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


//make motors thread
//make main thread
//DigitalOut greenLED(PIN_FRDM_LED_GREEN);
DigitalOut tempRunning(PIN_FRDM_LED_GREEN);
class FSOcontroller{

    public:
        FSOcontroller() = default;


        //---------CREATE I2C Interfaces-------
        I2C I2C_A ={PIN_I2CA_SDA, PIN_I2CA_SCL};
        I2C I2C_B = {PIN_I2CB_SDA, PIN_I2CB_SCL};


        //------CREATE MOTOR DRIVER OBJECT------------------
        Thread motorsThread;
        //PinName motor_controls_out[5]={PIN_FRDM_LED_RED, PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR};
        PinName motor_controls_out[4] = {PIN_MOTOR_1_STEP, PIN_MOTOR_1_DIR, PIN_MOTOR_2_STEP, PIN_MOTOR_2_DIR};
        PinName motor_controls_in[4]={PIN_MOTOR_DIR_CTRL_UP, PIN_MOTOR_DIR_CTRL_DOWN, PIN_MOTOR_DIR_CTRL_LEFT, PIN_MOTOR_DIR_CTRL_RIGHT};
        MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0]};

        

        void start(){
            //start motors thread
            motorsThread.start(callback(&(this->motorDriver), &MotorDriver::start));

            //start main polling thread
            exec();
        }



        //endless execution loop
        void exec(){
            while(true){
                printf("running");
                //pollForPower();
                tempRunning = !tempRunning;
                ThisThread::sleep_for(POWER_POLL_SLEEP);
            }
        }

        //// Thread pollThread;
        //// maybe parallelise this more.
        //// maybe add in checking for RX_LOS. If RX_LOS interrupt triggered then switch and poll..
        char power[2];
        int maxPower;
        unsigned short int powerInt; //16 bit unsigned
        std::vector<float> SFPpowers;
        int indexHighestPower;
        void pollForPower(){
            for (int sfp = 1; sfp<8; sfp++){
                if (sfp<5){
                    I2CbufferA.setOn(sfp);
                    I2CA.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
                    I2CA.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN); //power is two bytes
                }else{
                    I2CbufferB.setOn(sfp);
                    I2CB.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
                    I2CB.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN);
                }         
                //poll for power
                powerInt = (power[0] << 8) + power[1]; //unsigned int
                SFPpowers[sfp-1] = power*RX_POWER_WEIGHT_4 + power*RX_POWER_WEIGHT_3 + power*RX_POWER_WEIGHT_2 + power*RX_POWER_WEIGHT1 + RX_POWER_WEIGHT_0;
                //check if this is needed or is internally calibrated. If internally calibrated simply use power*rx_power_weight1.
                //poll and check these first then decide whether to read these every time on init or use hard coded.
            }
            #ifdef DEBUG_OUTPUT_POWERS
            printf("POWERS ");
            for (auto pwr: SFPpowers){
                
            }
            //printf(powers)...
            #endif
            indexHighestPower = std::distance(SFPpowers.begin(), std::max_element(SFPpowers.begin(), SFPpowers.end())); 
            RX_CROSSPOINT.route(indexHighestPower+1); //for highest power at sfp 2 (position 1) route to position 1 + 1 = 2                            
        }

    private:



};



int main()
{   
    FSOcontroller controller;
    controller.start();
}