#include "FullExpandedGPIO.h"
#include <cstdint>

FullExpandedGPIO::FullExpandedGPIO(I2C* i2c):
    i2c(i2c)
    {
       
}


// void FullExpandedGPIO::write(GPIOexpanderPin pin, uint8_t state){
//     gpioExpanders[pin.gpioExIndex]->write(pin.gpioExPinNumber, state);
// }

// uint8_t FullExpandedGPIO::read(GPIOexpanderPin pin){
//     return gpioExpanders[pin.gpioExIndex]->read(pin.gpioExPinNumber);
// }


// void FullExpandedGPIO::reset(){
//     for (int expander = 0; expander <4; expander++){
//         gpioExpanders[expander]->reset();
//     }
// }