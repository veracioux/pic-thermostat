#include "input.h"

void processInputInterrupt()
{
    temperature = (((short) ADRESH) << 8) + ADRESL;
}

void init_adc()
{
	ADCON1bits.ADCS = 0; // Fosc/2
    
    // CHS bits set the input channel for the ADC
	ADCON0bits.CHS = TEMPERATURE_IN_CHANNEL_SELECT;

	// Use built-in reference voltages
    ADNREF = 0;
	ADPREF1 = 0;
	ADPREF0 = 0;

	ADON = 1;
	ADFM = 1; // Right hand side justification of result
}

void read_temp()
{
	ADGO = 1;     // Initiate AD conversion
}
