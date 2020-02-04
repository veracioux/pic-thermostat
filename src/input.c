#include "input.h"

void init_adc()
{
	ADCON1bits.ADCS = 0b111; // Clock supplied from dedicated RC oscillator

	// Use built-in reference voltages
    ADNREF = 0;
	ADPREF1 = 0;
	ADPREF0 = 0;

	ADON = 1;
	ADFM = 1; // Right hand side justification of result
}

void read_temp()
{
	// CHS bits set the input channel for the ADC
	ADCON0bits.CHS = TEMPERATURE_IN_CHANNEL_SELECT;

	ADGO = 1;     // Initiate AD conversion
	while (ADGO); // Wait for AD conversion to end
	temperature = ((short) ADRESH << 8) + ADRESL;
}
