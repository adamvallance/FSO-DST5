#include "GPIOexpander.h"
#include <system_error>

GPIOexpander::GPIOexpander(PinName* pins,  int I2CaddressIn, int gpioExIndexIn):
    RESET_N(pins[0], 1),
    INT_N(pins[1]) 
    {   

        gpioExIndex = gpioExIndexIn;
        I2Caddress = I2CaddressIn;
        reset();
        setPinDefaults(gpioExIndex); //set registers to configure as described in config.h
    

    }

void GPIOexpander::registerInterrupt(callbackClass * cb){
    INT_N.fall(callback(cb, &callbackClass::interrupt)); 
}

void GPIOexpander::reset(){
    RESET_N = 0; 
    ThisThread::sleep_for(POWER_POLL_SLEEP);
    RESET_N = 1; //remove out of reset mode
    setPinDefaults(gpioExIndex);
}


void GPIOexpander::writeRegister(uint8_t reg, uint8_t value){
//                     //debug
//     const char testVal = 0xFF;
//     I2CB.write(0x23, &testVal, 1);

// ;
    const char bytesToWrite[2] = {reg, value};
    I2CB.write(I2Caddress, &bytesToWrite[0], 2);
    ERROR_LED = !ERROR_LED;

}
void GPIOexpander::writePortRegisters(uint8_t reg, char data){
    I2CB.write(I2Caddress, &data, 3);
    ERROR_LED = !ERROR_LED;

}

uint8_t GPIOexpander::readRegister(uint8_t reg){
    char readData;
    I2CB.write(I2Caddress, (char*) reg, 1); 
    I2CB.read(I2Caddress, &readData, 1);
    return (uint8_t) readData;
}

void GPIOexpander::setPinDefaults(int gpioExIndex){
    if (gpioExIndex < 0 or gpioExIndex > 4){
        printf("Error, gpio expander selection of range");
        return;//error
    }
    writePortRegisters(PCAL6524_CONFIGURATION_PORT_0, PCAL6524_CONFIGURATION[gpioExIndex][0]);
    writePortRegisters(PCAL6524_RESISTOR_PULL_ENABLE_PORT_0, PCAL6524_RESISTOR_PULL_ENABLE[gpioExIndex][0]); //1 PU or PD, 0 NO PU/PD
    writePortRegisters(PCAL6524_RESISTOR_PULL_SELECTION_PORT_0, PCAL6524_RESISTOR_PULL_SELECTION[gpioExIndex][0]);//1 PU, 0 PD
    writePortRegisters(PCAL6524_INTERRUPT_MASK_PORT_0, PCAL6524_INTERRUPT_MASK[gpioExIndex][0]); //1 no interrupt 0 interrupts

    // //uses gpioExIndex to set default pins through registers as defined in config.h
    // writeRegister(PCAL6524_CONFIGURATION_PORT_0, PCAL6524_CONFIGURATION[gpioExIndex][0]); //1 input, 0 output
    // writeRegister(PCAL6524_CONFIGURATION_PORT_1, PCAL6524_CONFIGURATION[gpioExIndex][1]);
    // writeRegister(PCAL6524_CONFIGURATION_PORT_2, PCAL6524_CONFIGURATION[gpioExIndex][2]);
    // writeRegister(PCAL6524_RESISTOR_PULL_ENABLE_PORT_0, PCAL6524_RESISTOR_PULL_ENABLE[gpioExIndex][0]); //1 PU or PD, 0 NO PU/PD
    // writeRegister(PCAL6524_RESISTOR_PULL_ENABLE_PORT_1, PCAL6524_RESISTOR_PULL_ENABLE[gpioExIndex][1]);
    // writeRegister(PCAL6524_RESISTOR_PULL_ENABLE_PORT_2, PCAL6524_RESISTOR_PULL_ENABLE[gpioExIndex][2]);
    // writeRegister(PCAL6524_RESISTOR_PULL_SELECTION_PORT_0, PCAL6524_RESISTOR_PULL_SELECTION[gpioExIndex][0]);//1 PU, 0 PD
    // writeRegister(PCAL6524_RESISTOR_PULL_SELECTION_PORT_1, PCAL6524_RESISTOR_PULL_SELECTION[gpioExIndex][1]);
    // writeRegister(PCAL6524_RESISTOR_PULL_SELECTION_PORT_2,  PCAL6524_RESISTOR_PULL_SELECTION[gpioExIndex][2]); //
    // writeRegister(PCAL6524_INTERRUPT_MASK_PORT_0, PCAL6524_INTERRUPT_MASK[gpioExIndex][0]); //1 no interrupt 0 interrupts
    // writeRegister(PCAL6524_INTERRUPT_MASK_PORT_1, PCAL6524_INTERRUPT_MASK[gpioExIndex][1]);
    // writeRegister(PCAL6524_INTERRUPT_MASK_PORT_2, PCAL6524_INTERRUPT_MASK[gpioExIndex][2]);


}

void GPIOexpander::write(uint16_t pin, uint8_t state){

	uint8_t output_reg_value;
	uint8_t PCAL6524_OUTPUT;
	
	//Determine wich bank of pins the requested pin is in
	if (pin == P0_0 || pin == P0_1|| pin == P0_2 || pin == P0_3 || pin == P0_4 || pin == P0_5 || pin == P0_6 || pin == P0_7)
	{
		PCAL6524_OUTPUT = PCAL6524_OUTPUT_PORT_0;
	}
	else if (pin == P1_0 || pin == P1_1 || pin == P1_2 || pin == P1_3 || pin == P1_4 || pin == P1_5 || pin == P1_6 || pin == P1_7)
	{
		PCAL6524_OUTPUT = PCAL6524_OUTPUT_PORT_1;
	}
	else if (pin == P2_0 || pin == P2_1 || pin == P2_2 || pin == P2_3 || pin == P2_4 || pin == P2_5 || pin == P2_6 || pin == P2_7)
	{
		PCAL6524_OUTPUT = PCAL6524_OUTPUT_PORT_2;
	}


	// Read the current Value of out the ouput register
    //output_reg_value = readRegister(PCAL6524_OUTPUT);
    //debug !!!
    output_reg_value = 0x00;
	//Deterime if Pin is being asked to go hi or to go low and set only that pins value;
	if (state == 1)
	{
		output_reg_value = output_reg_value | (uint8_t)pin;
		writeRegister(PCAL6524_OUTPUT, output_reg_value);
		return;
	}
	else if (state == 0){
		output_reg_value = output_reg_value & ~((uint8_t)pin);
		writeRegister(PCAL6524_OUTPUT, output_reg_value);
		return;
	}
	return;	
}


uint8_t GPIOexpander::read(uint16_t pin)
{
	uint8_t input_reg_data;
	uint8_t PCAL6524_INPUT;
	//Determine wich bank of pins the requested pin is in
if (pin == P0_0 || pin == P0_1 || pin == P0_2 || pin == P0_3 || pin == P0_4 || pin == P0_5 || pin == P0_6 || pin == P0_7)
	{
		PCAL6524_INPUT = PCAL6524_INPUT_PORT_0;
	}
	else if (pin == P1_0 || pin == P1_1 || pin == P1_2 || pin == P1_3 || pin == P1_4 || pin == P1_5 || pin == P1_6 || pin == P1_7)
	{
		PCAL6524_INPUT = PCAL6524_INPUT_PORT_1;
	}
	else if (pin == P2_0 || pin == P2_1 || pin == P2_2 || pin == P2_3 || pin == P2_4 || pin == P2_5 || pin == P2_6 || pin == P2_7)
	{
		PCAL6524_INPUT = PCAL6524_INPUT_PORT_2;
	}
	//read the input register data
	input_reg_data = readRegister(PCAL6524_INPUT);
	//Isolate the reqested pin value from all other values
	input_reg_data = input_reg_data & (uint8_t)pin;
	
	//Bit Shift the resulting data over so the pin's requested value becomes the LSB
	switch ((uint8_t)pin)
	{
		case (0x01):  //For Pins Px_0
		{
			return input_reg_data;
		}
		case (0x02)://For Pins Px_1
		{
			return input_reg_data>>1;
		}
		case (0x04)://For Pins Px_2
		{
			return input_reg_data>>2;
		}
		case (0x08)://For Pins Px_3
		{
			return input_reg_data>>3;
		}
		case (0x10)://For Pins Px_4
		{
			return input_reg_data>>4;
		}
		case (0x20)://For Pins Px_5
		{
			return input_reg_data>>5;
		}
		case (0x40)://For Pins Px_6
		{
			return input_reg_data>>6;
		}
		case (0x80)://For Pins Px_7
		{
			return input_reg_data>>7;
		}
        default:
        {
            return -1;
        } 
	}
};
 

 ////commented out for now. Just set as defaults once. 
// void GPIOexpander::setPinMode(uint16_t pin, uint8_t mode){
// 	uint8_t config_data;
// 	uint8_t pullup_config_data;
// 	uint8_t pullup_value_data;	
// 	uint8_t PCAL6524_CONFIGURATION;
// 	uint8_t PCAL6524_RESISTOR_PULL_ENABLE;
// 	uint8_t PCAL6524_RESISTOR_PULL_SELECTION;
// 	//Determine wich bank of pins the requested pin is in
// 	if (pin == P0_0 || pin == P0_1 || pin == P0_2 || pin == P0_3 || pin == P0_4 || pin == P0_5 || pin == P0_6 ||pin == P0_7) //If pin is in the First bank
// 	{
// 		PCAL6524_CONFIGURATION = PCAL6524_CONFIGURATION_PORT_0;
// 		PCAL6524_RESISTOR_PULL_ENABLE = PCAL6524_RESISTOR_PULL_ENABLE_PORT_0;
// 		PCAL6524_RESISTOR_PULL_SELECTION = PCAL6524_RESISTOR_PULL_SELECTION_PORT_0;
// 	}
// 	else if (pin == P1_0 || pin == P1_1 || pin == P1_2 || pin == P1_3 ||pin == P1_4 || pin == P1_5 || pin == P1_6 || pin == P1_7) //If pin is in the Second bank
// 	{
// 		PCAL6524_CONFIGURATION = PCAL6524_CONFIGURATION_PORT_1;
// 		PCAL6524_RESISTOR_PULL_ENABLE = PCAL6524_RESISTOR_PULL_ENABLE_PORT_1;
// 		PCAL6524_RESISTOR_PULL_SELECTION = PCAL6524_RESISTOR_PULL_SELECTION_PORT_1;
// 	}
// 	else if (pin == P2_0 || pin == P2_1 || pin == P2_2 || pin == P2_3 || pin == P2_4 || pin == P2_5 || pin == P2_6 || pin == P2_7) //If pin is in the Third bank
// 	{
// 		PCAL6524_CONFIGURATION = PCAL6524_CONFIGURATION_PORT_2;
// 		PCAL6524_RESISTOR_PULL_ENABLE = PCAL6524_RESISTOR_PULL_ENABLE_PORT_2;
// 		PCAL6524_RESISTOR_PULL_SELECTION = PCAL6524_RESISTOR_PULL_SELECTION_PORT_2;
// 	}
// 	//read the current Input/output configuration settings for the given bank of pins
// 	config_data = readRegister(PCAL6524_CONFIGURATION);
// 	//read the current pullup enable configuration settings for the given bank of pins
// 	pullup_config_data = readRegister(PCAL6524_RESISTOR_PULL_ENABLE);
// 	//read the current pullup enable configuration settings for the given bank of pins
// 	pullup_value_data = readRegister(PCAL6524_RESISTOR_PULL_SELECTION);
// 	/*This section is used to determine what mode of operation is selected
// 		Input
// 		Output
// 		Input With PullUp Resistor Active
// 		Input with PullDown Resistor Active	
// 	*/

// 	if (mode == OUTPUT)
// 	{
// 		//Combine the current configuration with the request pin to ensure that only that pin has chaned
// 		config_data = config_data ^ (uint8_t)pin; //bitwise xor
//         //Combine the current configuration with the request pin to ensure that only that pin has chaned
// 		//Write the new configuration back to the Resistor
// 		writeRegister(PCAL6524_CONFIGURATION,config_data);  //Write the new configuration back to the Resistor
// 		return;
// 	}
// 	else if (mode == INPUT_PULLUP)
// 	{
// 		//Combine the current configuration with the request pin to ensure that only that pin has chaned
// 		config_data = config_data | (uint8_t)pin;
// 		//Write the new configuration back to the Resistor
// 		writeRegister(PCAL6524_CONFIGURATION,config_data);//Write the new configuration back to the Resistor
// 		//This is used to configure the pullup/down resistor are actived and configured correctly
// 		pullup_config_data = pullup_config_data | (uint8_t)pin;
// 		writeRegister(PCAL6524_RESISTOR_PULL_ENABLE,pullup_config_data);
// 		pullup_value_data = pullup_value_data | (uint8_t)pin;
// 		writeRegister(PCAL6524_RESISTOR_PULL_SELECTION,pullup_value_data);
// 		return;
// 	}
// 	else if (mode == INPUT_PULLDOWN)
// 	{
// 		//Combine the current configuration with the request pin to ensure that only that pin has chaned
// 		config_data = config_data | pin;
// 		//Write the new configuration back to the Resistor
// 		writeRegister(PCAL6524_CONFIGURATION,config_data);//Write the new configuration back to the Resistor
// 		//This is used to configure the pullup/down resistor are actived and configured correctly
// 		pullup_config_data = pullup_config_data | (uint8_t)pin;
// 		writeRegister(PCAL6524_RESISTOR_PULL_ENABLE,pullup_config_data);
// 		pullup_value_data = pullup_value_data ^ (uint8_t)pin;
// 		writeRegister(PCAL6524_RESISTOR_PULL_SELECTION,pullup_config_data);
// 		return;
// 	}
// 	return;
// }
