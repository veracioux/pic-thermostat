#pragma once

#include "definitions.h"

#define FLAG_READ_ERROR 0

union
{
    unsigned char value;
    struct
    {
        unsigned ONGOING_WRITE : 1;
        unsigned WRITE_ERR     : 1;
        unsigned READ_ERR      : 1;
    };
} dataFlags_bits;
#define dataFlags dataFlags_bits.value

void processDataInterrupt();

inline char eeprom_read_byte(char address);

/*
 * Read a chunk of the specified size starting at 'address'
 * and store it in the memory space pointed to by destination.
 *
 * Note: The caller of the function must ensure that all
 * parameters are valid and in-range.
 */
inline void eeprom_read_data(char address, unsigned char size, void *destination);

void eeprom_read_programs(struct Program *programs);

void eeprom_write_byte(char address, char data);

void eeprom_store_programs(struct Program *programs);