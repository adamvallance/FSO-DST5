//derived from https://github.com/jrj12591/PCAL6524
#ifndef FSO_GPIO_EXPANDER_CONFIG_H
#define FSO_GPIO_EXPANDER_CONFIG_H
#include <cstdint>

/*=========================================================================
    CONFIGURATION Register adresses
    -----------------------------------------------------------------------*/
    const char PCAL6524_INPUT_PORT_0	=	0x00;    //INPUT PORT 0 Register  - Read Only
	const char PCAL6524_INPUT_PORT_1	=	0x01;    //INPUT PORT 1 Register  - Read Only
	const char PCAL6524_INPUT_PORT_2	=	0x02;    //INPUT PORT 2 Register  - Read Only
	const char PCAL6524_OUTPUT_PORT_0	=	0x04;    //OUTPUT PORT 0 Register  - Read & Write
	const char PCAL6524_OUTPUT_PORT_1	=	0x05;    //OUTPUT PORT 1 Register  - Read & Write
	const char PCAL6524_OUTPUT_PORT_2	=	0x06;    //OUTPUT PORT 2 Register  - Read & Write
	const char PCAL6524_POLARITY_INVERSION_PORT_0	=	0x08;    //Read & Write
	const char PCAL6524_POLARITY_INVERSION_PORT_1	=	0x09;    //Read & Write
	const char PCAL6524_POLARITY_INVERSION_PORT_2	=	0x0A;    //Read & Write
	const char PCAL6524_CONFIGURATION_PORT_0	=	0x0C;    //Read & Write
	const char PCAL6524_CONFIGURATION_PORT_1	=	0x0D;    //Read & Write
	const char PCAL6524_CONFIGURATION_PORT_2	=	0x0E;    //Read & Write
	const char PCAL6524_OUTPUT_STRENGH_OA	=	0x40;
	const char PCAL6524_OUTPUT_STRENGH_0B 	=	0x41;
	const char PCAL6524_OUTPUT_STRENGH_1A	=	0x42;
	const char PCAL6524_OUTPUT_STRENGH_1B 	=	0x43;
	const char PCAL6524_OUTPUT_STRENGH_2A	=	0x44;
	const char PCAL6524_OUTPUT_STRENGH_2B 	=	0x45;
	const char PCAL6524_INPUT_LATCH_PORT_0	=	0X48;
	const char PCAL6524_INPUT_LATCH_PORT_1	=	0X49;
	const char PCAL6524_INPUT_LATCH_PORT_2	=	0X4A;
	const char PCAL6524_RESISTOR_PULL_ENABLE_PORT_0	=	0x4C;
	const char PCAL6524_RESISTOR_PULL_ENABLE_PORT_1	=	0x4D;
	const char PCAL6524_RESISTOR_PULL_ENABLE_PORT_2	=	0x4E;
	const char PCAL6524_RESISTOR_PULL_SELECTION_PORT_0	=	0x50;
	const char PCAL6524_RESISTOR_PULL_SELECTION_PORT_1	=	0x51;
	const char PCAL6524_RESISTOR_PULL_SELECTION_PORT_2	=	0x52;
	const char PCAL6524_INTERRUPT_MASK_PORT_0		= 	0x54;
	const char PCAL6524_INTERRUPT_MASK_PORT_1		= 	0x55;
	const char PCAL6524_INTERRUPT_MASK_PORT_2		= 	0x56;
	const char PCAL6524_INTERRUPT_STATUS_PORT_0 		= 	0x58;
	const char PCAL6524_INTERRUPT_STATUS_PORT_1		= 	0x59;
	const char PCAL6524_INTERRUPT_STATUS_PORT_2 		= 	0x5A;
	const char PCAL6524_OUTPUT_PORT_CONFIG 			= 	0x5C;
	const char PCAL6524_INTERRUPT_EDGE_PORT_0A		=	0x60;
	const char PCAL6524_INTERRUPT_EDGE_PORT_0B		=	0x61;
	const char PCAL6524_INTERRUPT_EDGE_PORT_1A		=	0x62;
	const char PCAL6524_INTERRUPT_EDGE_PORT_1B		=	0x63;
	const char PCAL6524_INTERRUPT_EDGE_PORT_2A		=	0x64;
	const char PCAL6524_INTERRUPT_EDGE_PORT_2B		=	0x65;
	const char PCAL6524_INTERRUPT_CLEAR_PORT_0 		= 	0x68;
	const char PCAL6524_INTERRUPT_CLEAR_PORT_1 		= 	0x69;
	const char PCAL6524_INTERRUPT_CLEAR_PORT_2 		= 	0x6A;
	const char PCAL6524_INPUT_STATUS_PORT_0 			= 	0x6C;
	const char PCAL6524_INPUT_STATUS_PORT_1			=	0x6D;
	const char PCAL6524_INPUT_STATUS_PORT_2			=	0x6E;
	const char PCAL6524_PIN_OUTPUT_CONFIG_PORT_0		=	0x70;
	const char PCAL6524_PIN_OUTPUT_CONFIG_PORT_1 	=	0x71;
	const char PCAL6524_PIN_OUTPUT_CONFIG_PORT_2 	=	0x72;
	const char PCAL6524_SWITCH_DEBOUCE_ENABLE_PORT_0 = 	0x74;
	const char PCAL6524_SWITCH_DEBOUCE_ENABLE_PORT_1 = 	0x75;
	const char PCAL6524_SWITCH_DEBOUCE_COUNT			=	0x76;
/*=========================================================================*/

/*=========================================================================
    PIN Locations
    -----------------------------------------------------------------------*/
    //Port 0
	const uint16_t  P0_0 = 0x0001;
	const uint16_t  P0_1 = 0x0002;
	const uint16_t  P0_2 = 0x0004;
	const uint16_t  P0_3 = 0x0008;
	const uint16_t  P0_4 = 0x0010;
	const uint16_t  P0_5 = 0x0020;
	const uint16_t  P0_6 = 0x0040;
	const uint16_t  P0_7 = 0x0080;
	//Port 1
	const uint16_t  P1_0 = 0x0101;
	const uint16_t  P1_1 = 0x0102;
	const uint16_t  P1_2 = 0x0104;
	const uint16_t  P1_3 = 0x0108;
	const uint16_t  P1_4 = 0x0110;
	const uint16_t  P1_5 = 0x0120;
	const uint16_t  P1_6 = 0x0140;
	const uint16_t  P1_7 = 0x0180;
	//Port 2
	const uint16_t  P2_0 = 0x0201;
	const uint16_t  P2_1 = 0x0202;
	const uint16_t  P2_2 = 0x0204;
	const uint16_t  P2_3 = 0x0208;
	const uint16_t  P2_4 = 0x0210;
	const uint16_t  P2_5 = 0x0220;
	const uint16_t  P2_6 = 0x0240;
	const uint16_t  P2_7 = 0x0280;
// /*=========================================================================*/
// /*=========================================================================
// Pin types. //probably not needed as not setting individual pins
//     -----------------------------------------------------------------------*/	
// 	const char OUTPUT = 0x0;
// 	const char INPUT_PULLDOWN = 0x01;
//     const char INPUT_PULLUP = 0x02;
// /*=========================================================================*/

#endif// FSO_GPIO_EXPANDER_CONFIG_H
