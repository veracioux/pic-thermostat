#pragma once

#include <xc.h>
#include "definitions.h"

union
{
    unsigned char value;
    struct
    {
        unsigned unused      : 5;
        unsigned ESTABLISHED : 1;
        unsigned DIRECTION   : 1; // 1 = From PC to PIC 
                                  // 0 = From PIC to PC
        unsigned BUSY        : 1; // Are any TX/RX operations taking place?
    };
} commFlags_bits;
#define commFlags commFlags_bits.value

void init_comms();

void processCommInterrupt();

inline void send_byte(char byte);

void pc_read_programs(struct Program *programs);

void pc_send_programs(struct Program *programs);

void pc_send_current_program(struct Program *program);

void pc_send_temp(unsigned short temp);
