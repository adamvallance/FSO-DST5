#include "xpoint.h"

#define VERBOSE_DEBUG

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
}

void XPoints::routeRX(int inputSFP){
    I2CB.write(XPOINT_RX_I2C_ADDRESS, &XPOINT_ROUTE_RX[inputSFP-1][0], 2);
}

void XPoints::routeTX(int outputSFP){
    if (clearOtherTx){ //if following a flash of all on, turn them off
        for (int sfp = 1; sfp < 8; sfp ++){
            if (sfp == currentRoutedTx){
                break;
            }
            I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_CLEAR_TX[sfp-1][0], 2);
        }
        #ifdef VERBOSE_DEBUG
            printf("Other TX except for %d reset \n", outputSFP);
        #endif
        clearOtherTx = false;
    }else if (outputSFP != currentRoutedTx){ //turn off already on 
        I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_CLEAR_TX[])
        #ifdef VERBOSE_DEBUG
            printf("Previous TX reset (%d) \n", currentRoutedTx);
        #endif
    }else{ //if correct sfp already on skip 
        #ifdef VERBOSE_DEBUG
            printf("SFP %d already on\n", outputSFP);
        #endif
        return;
    }
    //write to pass input port 0 to the selected output port register
    I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_ROUTE_TX[outputSFP-1][0], 2);
    #ifdef VERBOSE_DEBUG
        printf("Turning on TX %d \n", outputSFP);
    #endif
    currentRoutedTx = outputSFP;
}

void XPoints::routeAllTX(){
    clearOtherTx = true;
    for (int sfp = 1; sfp<8; sfp++){
        //pass input port 0 to all output port registers of tx to transmit on all sfps
        I2CA.write(XPOINT_TX_I2C_ADDRESS, &XPOINT_ROUTE_TX[sfp-1][0], 2);
    }
    currentRoutedTx = -1; //for all
}

int XPoints::getCurrentTXSFP(){
    return currentRoutedTx;
}