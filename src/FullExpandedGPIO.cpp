#include "FullExpandedGPIO.h"
#include <cstdint>

FullExpandedGPIO::FullExpandedGPIO(){
;               
}

void FullExpandedGPIO::registerInterrupt(int gpioExIndex, callbackClass *cb){
    gpioExpanders[gpioExIndex]->registerInterrupt(cb);
}

void FullExpandedGPIO::write(GPIOexpanderPin pin, char state){

    gpioExpanders[pin.gpioExIndex]->write(pin.gpioExPinNumber, state);
    //gpioExpanders[0]->write(pin.gpioExPinNumber, state);

}

char FullExpandedGPIO::read(GPIOexpanderPin pin){
    return gpioExpanders[pin.gpioExIndex]->read(pin.gpioExPinNumber);

}


void FullExpandedGPIO::reset(){
    for (int expander = 0; expander <4; expander++){
        gpioExpanders[expander]->reset();
    }
}