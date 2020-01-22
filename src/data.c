#include "data.h"

inline char eeprom_read_byte(char address)
{
    EEADRL = address;
    EECON1bits.RD = 1;
    return EEDATL;
}

inline void eeprom_read_data(char address, unsigned char size, void *destination)
{
    char *dest = destination;
    while (size--)
    {
        EEADRL = address++;
        EECON1bits.RD = 1;
        *dest++ = EEDATL;
    }
}