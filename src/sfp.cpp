#include "sfp.h"

SFP::SFP(FullExpandedGPIO* gpios, int SFPindex): 
    //initialise member digital outputs which are static based on the input list of pin names
    gpios(gpios),
    SFPindex(SFPindex)
    
{   
    gpios->write(SFP_TX_DISABLE[SFPindex], 0); //clear disable
}

float SFP::getPower(){
//
}