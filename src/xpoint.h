#ifndef FSO_XPOINT_H
#define FSO_XPOINT_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGpio.h"

class XPoints{

   FullExpandedGPIO* gpios;
   public:
       XPoints(FullExpandedGPIO*); 
       void routeRX(int);
       void routeTX(int);
       void routeAllTX();
       void reset();
       int getCurrentTXSFP();
    private:
        bool clearOtherTx = false;
        int currentRoutedTx = 1;
        char bytesToWrite[2];

};

#endif //FSO_XPOINT_H