#include <xc.h>
#include "definitions.h"
#include "communication.h"

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, MCLRE = ON, CP = OFF, CPD = OFF, BOREN = OFF, CLKOUTEN = OFF
#pragma config IESO = OFF, FCMEN = OFF, WRT = OFF, VCAPEN = OFF, PLLEN = OFF, STVREN = OFF, LVP = OFF
#define _XTAL_FREQ 8000000

// The currently active program
struct Program *activeProgram = 0;

// Used as a flag for hysteresis
char risingTemperature = 1;
// Counts the number of interrupt routine calls, used to measure the current time
unsigned int interruptTicks = 0;

struct Program programs[PROGRAM_LIMIT];

void init_pins()
{

}

void init_eeprom()
{
	/* TODO
		Read version code from the EEPROM.
		If it is lower than VERSION_CODE, read all the programs as appropriate
		and store the VERSION_CODE and the programs in EEPROM using the new scheme.
	*/
}

void init_interrupt()
{
	// Set interrupt interval
}

void init_adc()
{

}

void init_comms()
{

}

//TODO Determine correct return type
char read_temp()
{
	//TODO
	return 0;
}

// The current time in seconds
int currentTime = 0;
unsigned char currentDay;

void __interrupt() update()
{
	// Used to calculate the current time
	++interruptTicks;
	for (int i = 0; i < PROGRAM_LIMIT; ++i)
	{
		//TODO Test the day
		if (programs[i].on <= currentTime && currentTime < programs[i].off)
			activeProgram = programs + i;
	}
}

void main(void)
{
	// Initializations
	init_pins();
	init_eeprom();
	init_adc();
	init_comms();
	// This one should be last to prevent unexpected behavior
	init_interrupt();

	char previous = HEATER_OUT;
	while (1)
	{
		char temp = read_temp();

		if (previous != HEATER_OUT)
		{
			risingTemperature = !risingTemperature;
			previous = HEATER_OUT;
		}
		// Turn heater relay on/off
		if (risingTemperature)
			HEATER_OUT = temp < activeProgram->max;
		else
			HEATER_OUT = temp > activeProgram->min;
	}
}
