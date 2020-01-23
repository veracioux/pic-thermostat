#pragma once

#include <xc.h>
#include "definitions.h"

union
{
    unsigned char value;
    struct
    {
        unsigned RX          : 1;
        unsigned TX          : 1;
        unsigned ESTABLISHED : 1;
        unsigned BUSY        : 1;
    };
} commFlags;

void init_comms();

void processTransmitInterrupt();

void processReceiveInterrupt();

void pc_send_data(void *data, unsigned char size);

void pc_read_data(void *data, unsigned char size);

void pc_send_program(struct Program *program);

void pc_read_program(struct Program *program);

void pc_read_programs(struct Program *programs, unsigned char nPrograms);

void pc_send_programs(struct Program *programs, unsigned char nPrograms);

void pc_send_temp(unsigned short temp);