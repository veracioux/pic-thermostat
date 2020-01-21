#include <xc.h>
#include "definitions.h"
#include "communication.h"

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, MCLRE = ON, CP = OFF, CPD = OFF, BOREN = OFF, CLKOUTEN = OFF
#pragma config IESO = OFF, FCMEN = OFF, WRT = OFF, VCAPEN = OFF, PLLEN = OFF, STVREN = OFF, LVP = OFF

// The currently active program
struct Program *activeProgram = 0;

// Used as a flag for hysteresis
char risingTemperature = 1;

struct Program programs[PROGRAM_LIMIT];

void init_pins()
{

}

void init_eeprom()
{
    // Access to program Flash memory is not planned
    EEPGD = 0;
    // Access to configuration is not planned
    CFGS = 0;

	/* TODO
		Read version code from the EEPROM.
		If it is lower than VERSION_CODE, read all the programs as appropriate
		and store the VERSION_CODE and the programs in EEPROM using the new scheme.
	*/
}

void init_interrupt()
{
    TMR0IF = 0; // Clear Interrupt Flag
    TMR0IE = 1; // Enable Timer0 interrupt
    TMR0CS = 0; // Select internal instruction cycle clock
    SET_TMR0_PARAMS()
    GIE = 1;    // Global Interrupt Enable
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

// The number of PROGRAM_TIME_UNIT_MICROS microseconds that have elapsed today
unsigned short programTimeUnitTicks = 0;
// Microseconds that have elapsed since the last increment of programTimeUnitTicks
unsigned long elapsedMicros = 0;
unsigned char currentDay = 0;

void __interrupt() update()
{
	if (TMR0IF)
	{
		elapsedMicros += TIME_UPDATE_MICROS;
		if (elapsedMicros >= PROGRAM_TIME_UNIT_MICROS)
		{
			++programTimeUnitTicks;
			elapsedMicros -= PROGRAM_TIME_UNIT_MICROS;
			if (programTimeUnitTicks >= 86400000000 / PROGRAM_TIME_UNIT_MICROS)
			{
				programTimeUnitTicks = 0;
                if (currentDay >= 6)
                    currentDay = 0;
                else
                    ++currentDay;
			}
		}
        // Find the program that is currently active
		for (int i = 0; i < PROGRAM_LIMIT; ++i)
		{
			//TODO Test the day
			if (programs[i].on <= programTimeUnitTicks && programTimeUnitTicks < programs[i].off)
				activeProgram = programs + i;
		}
        TMR0IF = 0;
	}
    //TODO Test if ADC has triggered an interrupt. If yes, send the current temperature to PC
}

void main(void)
{
	// Initializations
	init_pins(); // Should be first

	init_eeprom();
	init_adc();
	init_comms();

	init_interrupt(); // Should be last to prevent unexpected behavior

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
