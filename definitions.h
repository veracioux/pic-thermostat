#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>

// The maximum number of user programs
#define PROGRAM_LIMIT 10

// Oscillator frequency
#define _XTAL_FREQ 8000000

/* The duration of one instruction cycle in nanoseconds
 * Can be calculated as 4. / _XTAL_FREQ.
 */
#define INSTRUCTION_CYCLE_NS 500

// Time resolution with which the thermostat can be programmed by the user
#define TIME_SET_RESOLUTION_MIN 1

// Time interval between Timer0 interrupts
#define TIME_STEP_MS 30000

/*
 * Input/Output definitions TODO: currently just placeholders
 */
#define HEATER_OUT PORTCbits.RC0
#define HEATER_INDICATOR_OUT PORTCbits.RD0
#define TX_OUT PORTCbits.RC6

#define RX_IN PORTCbits.RC7

// If you change this, also change TEMPERATURE_IN_CHANNEL_SELECT accordingly
#define TEMPERATURE_IN PORTAbits.RA0

// Value of ADCON0.CHS bits
#define TEMPERATURE_IN_CHANNEL_SELECT 0


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