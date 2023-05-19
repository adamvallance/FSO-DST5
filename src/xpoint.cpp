#include "xpoint.h"


XPoints::XPoints(FullExpandedGPIO* gpios): 
   //initialise member digital outputs which are static based on the input list of pin names
   gpios(gpios)
{   
   reset();
}

void XPoints::reset(){
   gpios->write(GPIO_XPOINT_TX_RES_N, 0);
   gpios->write(GPIO_XPOINT_RX_RES_N, 0);
   ThisThread::sleep_for(1ms); //could be shorter but leave for now
   gpios->write(GPIO_XPOINT_TX_RES_N, 1);
   gpios->write(GPIO_XPOINT_RX_RES_N, 1);
    #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
        printf("XPoint switches reset\n");
    #endif

}

int XPoints::routeRX(int inputSFP){
    if (inputSFP != currentRoutedRx){
        I2CB.write(XPOINT_RX_I2C_ADDRESS, &XPOINT_ROUTE_RX[inputSFP-1][0], 2);
        #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
            printf("Routing SFP %d RX into Output/Master SFP\n", inputSFP);
        #endif
        currentRoutedRx = inputSFP;
        return 1;//1 for switch
    }else{
        return 0; //0 for no switch
    }
}

void XPoints::routeTX(int outputSFP){
    if (currentRoutedTx == -1){ //if following a flash of all on, turn them off
        for (int sfp = 1; sfp < 8; sfp ++){

            if (sfp == outputSFP){
                continue;
            }
            I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_CLEAR_TX[sfp-1][0], 2);
        }
        #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
            printf("Other SFP TX except for %d turned off \n", outputSFP);
        #endif
        currentRoutedTx = outputSFP;
        return;

    }

    else if (outputSFP != currentRoutedTx){ //turn off already on 
        I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_CLEAR_TX[currentRoutedTx-1][0], 2);
        #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
            printf("Turning off SFP (%d) TX\n", currentRoutedTx);
        #endif
        //write to pass input port 0 to the selected output port register
        I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_ROUTE_TX[outputSFP-1][0], 2);
        #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
            printf("Turning on SFP %d TX \n", outputSFP);
        #endif
    currentRoutedTx = outputSFP;
    }else{ //if correct sfp already on skip 
        #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
            printf("SFP %d TX already on\n", outputSFP);
        #endif
        return;
    }

}

void XPoints::routeAllTX(){
    for (int sfp = 1; sfp<8; sfp++){
        //pass input port 0 to all output port registers of tx to transmit on all sfps
        I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_ROUTE_TX[sfp-1][0], 2);
    }
    #ifdef VERBOSE_XPOINT_SWITCH_DEBUG
        printf("Turning on all SFP TX \n");
    #endif
    currentRoutedTx = -1; //for all
}

int XPoints::getCurrentTXSFP(){
    return currentRoutedTx;
}