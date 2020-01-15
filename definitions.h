#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>

#define PROGRAM_LIMIT 10
#define TIME_SET_RESOLUTION_MIN 1
#define TIME_STEP_MS 30000

// Input/Output definitions TODO: currently just placeholders
#define HEATER_OUT PORTCbits.RC0
#define TX_OUT PORTCbits.RC6

#define RX_IN PORTCbits.RC7
#define TEMPERATURE_IN PORTAbits.RA0

/*
 *  Version of the Program struct format.
 *
 *	If we decide to upgrade the system or change how we store program data
 *	and the EEPROM already has data stored with a previous
 *	version, we can read the version code of that version
 *	and make the transition without losing data.
*/
#define VERSION_CODE 0

struct Program
{
	// For now, we store day in a char, and use a negative value to indicate that the program is inactive
	char day;
	unsigned int on, off;
	unsigned int min, max;
};

#endif
