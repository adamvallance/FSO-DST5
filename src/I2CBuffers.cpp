#include "I2CBuffers.h"

I2CBuffers::I2CBuffers(FullExpandedGPIO* gpios): 
    //initialise member digital outputs which are static based on the input list of pin names
    gpios(gpios)
    
{   
    reset();
}
 
 void I2CBuffers::selectSFP(int sfp){ 
     //see config file for explanation
     if (sfp > 0 && sfp <5){
        I2CB.write(I2C_BUFFER_SELECT_SFP[sfp][0], &I2C_BUFFER_SELECT_SFP[sfp][1], 1);

     }else{
        I2CA.write(I2C_BUFFER_SELECT_SFP[sfp][0], &I2C_BUFFER_SELECT_SFP[sfp][1], 1);
     }

 }

void I2CBuffers::reset(){
    //can either do through I2C or the gpio expanders, here doing I2C
    I2CB.write(I2C_BUFFER_ADDRESSES[0], &I2C_BUFFER_RESET, 1);
    I2CA.write(I2C_BUFFER_ADDRESSES[0], &I2C_BUFFER_RESET, 1);
}

