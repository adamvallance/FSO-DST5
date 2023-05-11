#include "FSOcontroller.h"

//global error led
DigitalOut ERROR_LED(PIN_FRDM_LED_RED, 1);

FSOcontroller::FSOcontroller(PinName* pins, FullExpandedGPIO* expandedGPIO): // I2C* I2CA
    nominalRunningLED(pins[0], 0), //active low 
    fanPWM(pins[1]), 
    expandedGPIO(expandedGPIO)
    {
        ;
}

void FSOcontroller::start(){
    fanPWM.period(FAN_PWM_PERIOD);
    fanPWM.write(FAN_PWM_DUTY);
    exec();
}

void FSOcontroller::exec(){
    printf("Initialisation complete. Beginning power tracking.\n");
    while(true){
        //pollForPower();
        nominalRunningLED = !nominalRunningLED;
        ThisThread::sleep_for(POWER_POLL_SLEEP);
        //expandedGPIO.write(GPIO_DEBUG_LED, tempRunning.read()); //toggle GPIO expander LED
    }
}


void FSOcontroller::pollForPower(){
    //        char power[2];
//        unsigned short int powerInt; //16 bit unsigned
//        for (int sfp = 1; sfp<8; sfp++){
//            if (sfp<5){
//                I2CbufferA.setOn(sfp);
//                I2CA.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
//                I2CA.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN); //power is two bytes
//            }else{
//                I2CbufferB.setOn(sfp);
//                I2CB.write(I2C_SFP_ADDRESS, SFP_RX_POWER_ADDRESS);
//                I2CB.read(I2C_SFP_ADDRESS, power, SFP_POWER_BYTE_LEN);
//            }         
//            //poll for power
//            powerInt = (power[0] << 8) + power[1]; //unsigned int
//            SFPpowers[sfp-1] = power*RX_POWER_WEIGHT_4 + power*RX_POWER_WEIGHT_3 + power*RX_POWER_WEIGHT_2 + power*RX_POWER_WEIGHT1 + RX_POWER_WEIGHT_0;
//            //check if this is needed or is internally calibrated. If internally calibrated simply use power*rx_power_weight1.
//            //poll and check these first then decide whether to read these every time on init or use hard coded.
//        }
//        #ifdef DEBUG_OUTPUT_POWERS
//        printf("POWERS ");
//        for (auto pwr: SFPpowers){
//            printf("%.2f", pwr);
//        }
//        printf("\n");
//        #endif
//        indexHighestPower = std::distance(SFPpowers.begin(), std::max_element(SFPpowers.begin(), SFPpowers.end())); 
//        RX_CROSSPOINT.route(indexHighestPower+1); //for highest power at sfp 2 (position 1) route to position 1 + 1 = 2                            
}