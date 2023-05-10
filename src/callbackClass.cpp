#include "callbackClass.h"

//global error led
extern DigitalOut ERROR_LED;
extern I2C I2CA = {PIN_I2CA_SDA, PIN_I2CA_SCL};
extern I2C I2CB = {PIN_I2CB_SDA, PIN_I2CB_SCL};