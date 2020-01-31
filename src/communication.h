#pragma once

#include <xc.h>
#include "definitions.h"
#include "input.h"
#include "data.h"

/*
 * Request codes sent by the PC to initiate a data transfer
 */
#define REQUEST_CONNECTION '#'

#define REQUEST_RX_TEMP '$'
#define REQUEST_RX_TIME 'T'
#define REQUEST_RX_CURRENT_PROGRAM '&'
#define REQUEST_RX_PROGRAMS '>'

#define REQUEST_TX_TIME 't'
#define REQUEST_TX_PROGRAM 'p'
#define REQUEST_TX_PROGRAMS '<'

unsigned char commTimeout = 0;

union
{
    unsigned char value;
    struct
    {
        unsigned RX                  : 1; // Set when program data is pending to be received
        unsigned TX                  : 1; // Set when data is pending to be sent
        unsigned ESTABLISHED         : 1; // Set when a CONNECTION_REQUEST character is received, cleared if an error occurs during transmission
        unsigned BUSY                : 1; // Set if any RX/TX operations are active
    };
} commFlags;

void init_comms();

void processTransmitInterrupt();

void processReceiveInterrupt();

void abortReceive();

void pc_send_data(void *data, unsigned char size);

void pc_read_data(void *data, unsigned char size);

void pc_send_program(struct Program *program);

void pc_read_program(struct Program *program);

void pc_send_programs(struct Program *programs, unsigned char nPrograms);

void pc_read_programs(struct Program *programs, unsigned char nPrograms);

void pc_send_temp(unsigned short *temp);

void pc_send_time(struct Time *time);

void pc_read_time(struct Time *time);
