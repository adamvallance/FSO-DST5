#include "I2CBuffer.h"

I2CBuffer::I2CBuffer(PinName resetPin, I2C* i2cIn): 
    //initialise member digital outputs which are static based on the input list of pin names
    reset(resetPin, 0),
    i2c(i2cIn)
{   
        
    ;
}
