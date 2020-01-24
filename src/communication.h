#pragma once

#include <xc.h>
#include "definitions.h"
#include "input.h"
#include "data.h"

/*
 * Request codes sent by the PC to initiate a data transfer
 */
// Verify the connection between the PIC and the PC
#define CONNECTION_REQUEST '#'
#define TIME_TX_REQUEST 'T'
#define TIME_RX_REQUEST 't'
#define TEMP_TX_REQUEST '$'
#define TIME_TX_REQUEST 'T'
#define TIME_RX_REQUEST 't'
#define PROGRAM_TX_REQUEST '&'
#define PROGRAMS_RX_REQUEST '<'
#define PROGRAMS_TX_REQUEST '>'

union
{
    unsigned char value;
    struct
    {
        unsigned RX                  : 1; // Set when program data is pending to be received
        unsigned TX                  : 1; // Set when data is pending to be sent
        unsigned ESTABLISHED         : 1; // Set when a CONNECTION_REQUEST character is received, cleared if an error occurs during transmission
        unsigned BUSY                : 1; // Set if any RX/TX operations are 
    };
} commFlags;

void init_comms();

void processTransmitInterrupt();

void processReceiveInterrupt();

void pc_send_data(void *data, unsigned char size);

void pc_read_data(void *data, unsigned char size);

void pc_send_program(struct Program *program);

void pc_read_program(struct Program *program);

void pc_send_programs(struct Program *programs, unsigned char nPrograms);

void pc_read_programs(struct Program *programs, unsigned char nPrograms);

void pc_send_temp(unsigned short *temp);

void pc_send_time(unsigned short *time);