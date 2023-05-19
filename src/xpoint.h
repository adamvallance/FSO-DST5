#ifndef FSO_XPOINT_H
#define FSO_XPOINT_H
#include "mbed.h"
#include "config.h"
#include "FullExpandedGPIO.h"

class XPoints{

   FullExpandedGPIO* gpios;
   public:
       XPoints(FullExpandedGPIO*); 
       int routeRX(int);
       void routeTX(int);
       void routeAllTX();
       void reset();
       int getCurrentTXSFP();
    private:
        int currentRoutedTx = 1;
        char bytesToWrite[2];
        int currentRoutedRx = 1;

};

#endif //FSO_XPOINT_H