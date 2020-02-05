/*
 * Holds all functions used for EEPROM R/W operations.
 * Additionally, this header holds data about all stored
 * programs and parameters of the currently active program
 */
#ifndef DATA_H
#define DATA_H

#include "definitions.h"

struct Program programs[PROGRAM_LIMIT];
unsigned char versionCode = 0, programsSize = 1;

// The currently active program
struct Program *activeProgram = 0;


/*
 * The current time on the microcontroller.
 */
struct Time currentTime;

union
{
    unsigned char value;
    struct
    {
        unsigned ONGOING_WRITE : 1;
        unsigned WRITE_ERR     : 1;
        unsigned READ_ERR      : 1;
    };
} dataFlags;

void processDataInterrupt();

void updateActiveProgram();

inline char eeprom_read_byte(char address);

/*
 * Read a chunk of the specified size starting at 'address'
 * and store it in the memory space pointed to by destination.
 *
 * Note: The caller of the function must ensure that all
 * parameters are valid and in-range.
 */
inline void eeprom_read_data(char address, unsigned char size, void *destination);

void eeprom_read_programs(struct Program *programs, unsigned char *size);

void eeprom_write_byte(char address, char data);

void eeprom_store_programs(struct Program *programs, unsigned char nPrograms);

#endif
