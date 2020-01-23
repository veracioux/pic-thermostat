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

void eeprom_read_programs(struct Program *programs)
{
    unsigned char addr = eepromStartAddress;
    // Read the number of programs
    unsigned char n = eeprom_read_byte(addr++);
    if (n > PROGRAM_LIMIT)
    {
        dataFlags.READ_ERR = 1;
        return;
    }
    while (n--)
        eeprom_read_data(addr++, sizeof(struct Program), programs++);
}