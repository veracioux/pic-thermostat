#include <xc.h>
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, MCLRE = ON, CP = OFF, CPD = OFF, BOREN = OFF, CLKOUTEN = OFF
#pragma config IESO = OFF, FCMEN = OFF, WRT = OFF, VCAPEN = OFF, PLLEN = OFF, STVREN = OFF, LVP = OFF
#define _XTAL_FREQ 8000000

#define PROGRAM_LIMIT 10

// Input/Output definitions
#define HEATER_OUT LATDbits.LATD0

struct Program
{
    //TODO How to know if this program is active?
    int on, off;
    int min, max;
};

// The current regulated temperature range
int min, max;

// These variables are functionally booleans
char active, risingTemperature = 1;

struct Program programs[PROGRAM_LIMIT];

void init_eeprom()
{
    
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
    return 0; //TODO
}

void __interrupt() update()
{
    struct Program active;
    for (int i = 0; i < PROGRAM_LIMIT; ++i)
    {
        // TODO find currently active program
    }
    min = active.min;
    max = active.max;
}

void main(void)
{
    // Initializations
    init_eeprom();
    init_adc();
    init_comms();
    init_interrupt(); // This one should be last to prevent unexpected behavior
    
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
            HEATER_OUT = temp < max;
        else
            HEATER_OUT = temp > min;
    }
}