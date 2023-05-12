#include "sfp.h"

SFP::SFP(FullExpandedGPIO* gpios, I2CBuffers* i2cbufs, int SFPindex): 
    //initialise member digital outputs which are static based on the input list of pin names
    gpios(gpios),
    i2cbufs(i2cbufs),
    SFPindex(SFPindex)
    
{   
    enable();
}

void SFP::disable(){
    gpios->write(SFP_TX_DISABLE[SFPindex], 1);
}

void SFP::enable(){
    gpios->write(SFP_TX_DISABLE[SFPindex], 0); //clear disable

}

float SFP::getPower(){
// char power[2];
    unsigned short int powerInt; //16 bit unsigned
    char powerRec[2];
    float outputPower = 0;
    i2cbufs->selectSFP(SFPindex);
    if (SFPindex == 0){
        return 0.0;//don't care for master sfp
    }
    else if (SFPindex <5){
        I2CB.write(SFP_I2C_ADDRESS, &SFP_RX_POWER_REG_ADDRESS, 1);
        I2CB.read(SFP_I2C_ADDRESS, powerRec, 2);
    }else{
        I2CA.write(SFP_I2C_ADDRESS, &SFP_RX_POWER_REG_ADDRESS, 1);
        I2CA.read(SFP_I2C_ADDRESS, powerRec, 2);
    }
    powerInt = (powerRec[0] << 8) + powerRec[1]; //unsigned int

    
    //for now
    return powerInt * 1.0;
    //return powerInt*RX_POWER_WEIGHT_4 + powerInt*RX_POWER_WEIGHT_3 + powerInt*RX_POWER_WEIGHT_2 + powerInt*RX_POWER_WEIGHT1 + RX_POWER_WEIGHT_0;
        //poll for power
        //check if this is needed or is internally calibrated. If internally calibrated simply use power*rx_power_weight1.
        //poll and check these first then decide whether to read these every time on init or use hard coded.
}