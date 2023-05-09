/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "config.h"
#include <vector>
#include "motorDriver.h"
#include "I2CBuffer.h"
#include "GPIOexpander.h"
#include "FullExpandedGPIO.h"
#include "FSOcontroller.h"
#include <string>
 

// //make motors thread
// //make main thread
// //DigitalOut greenLED(PIN_FRDM_LED_GREEN);
// DigitalOut nominalRunning(PIN_FRDM_LED_GREEN);
// DigitalOut errorRunning(PIN_FRDM_LED_RED);

// PwmOut fanPWM(PIN_FAN_PWM);
// class FSOcontroller{
// 	public:
//     FSOcontroller() = default;


//     //---------CREATE I2C Interfaces-------
//     I2C I2CA ={PIN_I2CA_SDA, PIN_I2CA_SCL};
//     I2C I2CB = {PIN_I2CB_SDA, PIN_I2CB_SCL};


//     //--------CREATE GPIO EXPANDERS-------------
//     // GPIOexpander motorEl_GPIOexpander = {GPIO_EXPANDER_ADDRESSES[0], GPIO_EXPANDER_PINS[0], &I2C_B, 0};
//     // GPIOexpander motorAz_GPIOexpander = {GPIO_EXPANDER_ADDRESSES[1], GPIO_EXPANDER_PINS[1], &I2C_B, 1};
//     // GPIOexpander GPIOexpander3= {GPIO_EXPANDER_ADDRESSES[2], GPIO_EXPANDER_PINS[2], &I2C_B, 2};
//     // GPIOexpander GPIOexpander4= {GPIO_EXPANDER_ADDRESSES[3], GPIO_EXPANDER_PINS[3], &I2C_B, 3};
//     // //save gpio expander objects in a list of pointers to be passed to classes to access.
//     // GPIOexpander* expandedGPIO[4] = {&motorEl_GPIOexpander, &motorAz_GPIOexpander, &GPIOexpander3, &GPIOexpander4};
//     FullExpandedGPIO expandedGPIO = {&I2CB};
//     //--------CREATE I2C Buffers -------------
//     // I2CBuffer I2CbufferA = {PIN_};
//     // I2CBuffer I2CbufferB = {};

//     //--------CREATE Xpoint switches -------------

//     //--------CREATE SFPs -------------

//     //------CREATE MOTOR DRIVER OBJECT------------------
//     Thread motorsThread;
//     MotorDriver motorDriver = {&motor_controls_out[0], &motor_controls_in[0]};


//         void start(){

//             fanPWM.period(FAN_PWM_PERIOD);
//             fanPWM.write(FAN_PWM_DUTY);

//             //start motors thread
//             motorsThread.start(callback(&(this->motorDriver), &MotorDriver::start));

//             //start main polling thread
//         exec();
//     }


//     int errorStatus = 0;

//     //endless execution loop
//     void exec(){
//         printf("Initialisation complete. Begining power tracking.\n");
//         while(true){
//             //pollForPower();
//             if (errorStatus==0){
//                 nominalRunning = !nominalRunning;
//             }else{
//                 errorStatus = !errorRunning;
//             }
//             ThisThread::sleep_for(POWER_POLL_SLEEP);
//             //expandedGPIO.write(GPIO_DEBUG_LED, tempRunning.read()); //toggle GPIO expander LED
//         }
//     }



//     void setError(){
//         errorStatus = 1;
//         nominalRunning = 0;
//     }

//     //// Thread pollThread;
//     //// maybe parallelise this more.
//     //// maybe add in checking for RX_LOS. If RX_LOS interrupt triggered then switch and poll..
//     std::vector<float> SFPpowers;
//     int indexHighestPower =0;
//     void pollForPower(){
// //        char power[2];
// //        unsigned short int powerInt; //16 bit unsigned
// //        for (int sfp = 1; sfp<8; sfp++){
// //            if (sfp<5){
// //                I2CbufferA.setOn(sfp);
// //                I2CA.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
// //                I2CA.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN); //power is two bytes
// //            }else{
// //                I2CbufferB.setOn(sfp);
// //                I2CB.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
// //                I2CB.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN);
// //            }         
// //            //poll for power
// //            powerInt = (power[0] << 8) + power[1]; //unsigned int
// //            SFPpowers[sfp-1] = power*RX_POWER_WEIGHT_4 + power*RX_POWER_WEIGHT_3 + power*RX_POWER_WEIGHT_2 + power*RX_POWER_WEIGHT1 + RX_POWER_WEIGHT_0;
// //            //check if this is needed or is internally calibrated. If internally calibrated simply use power*rx_power_weight1.
// //            //poll and check these first then decide whether to read these every time on init or use hard coded.
// //        }
// //        #ifdef DEBUG_OUTPUT_POWERS
// //        printf("POWERS ");
// //        for (auto pwr: SFPpowers){
// //            printf("%.2f", pwr);
// //        }
// //        printf("\n");
// //        #endif
// //        indexHighestPower = std::distance(SFPpowers.begin(), std::max_element(SFPpowers.begin(), SFPpowers.end())); 
// //        RX_CROSSPOINT.route(indexHighestPower+1); //for highest power at sfp 2 (position 1) route to position 1 + 1 = 2                            
//     }



//     private:



// };



int main()
{   
    printf("Initialising...\n");

    FSOcontroller controller = {&FSO_CONTROLLER_PINS[0]};
    controller.start();
}