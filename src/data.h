#pragma once

#include "definitions.h"

#define FLAG_READ_ERROR 0

union
{
    struct
    {
        unsigned unused : 6;
        unsigned WRITE_ERR  : 1;
        unsigned READ_ERR  : 1;
    };
} dataFlags;

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

void eeprom_store_programs(struct Program *programs);
