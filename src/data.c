#include "data.h"

struct
{
    unsigned char remaining;
    unsigned char address;
    char *ptrData;
} dataStatus;

void processDataInterrupt()
{
    if (!dataFlags.ONGOING_WRITE)
        return;
    eeprom_write_byte(dataStatus.address++, *dataStatus.ptrData++);
    if (--dataStatus.remaining == 0)
        dataFlags.ONGOING_WRITE = 0;
}

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

void eeprom_read_programs(struct Program *programs, unsigned char *size)
{
    unsigned char addr = eepromStartAddress;
    // Read the number of programs
    unsigned char n = eeprom_read_byte(addr++);
    if (n > PROGRAM_LIMIT)
    {
        dataFlags.READ_ERR = 1;
        return;
    }
    *size = n;
    while (n--)
        eeprom_read_data(addr++, sizeof(struct Program), programs++);
}

void eeprom_write_byte(char address, char data)
{
    EEADRL = address;
    EEDATL = data;
    WREN = 1;
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    GIE = 1;
    WREN = 0;
}

void eeprom_store_programs(struct Program *programs, unsigned char nPrograms)
{
    if (dataFlags.ONGOING_WRITE)
        return;
    dataFlags.ONGOING_WRITE = 1;
    
    // Write the size of the programs
    eeprom_write_byte(eepromStartAddress, nPrograms);
    
    // Set up data for write on interrupt
    dataStatus.address = eepromStartAddress + 1;
    dataStatus.remaining = nPrograms * sizeof(struct Program);
    dataStatus.ptrData = (char*) programs;
}