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
#define REQUEST_RX_N_PROGRAMS 'N'
#define REQUEST_RX_ISNULL '?'

#define REQUEST_TX_TIME 't'
#define REQUEST_TX_PROGRAM 'p'
#define REQUEST_TX_PROGRAMS '<'
#define REQUEST_TX_N_PROGRAMS 'n'

unsigned char commTimeout = 0;

union
{
    unsigned char value;
    struct
    {
        unsigned RX                  : 1; // Set when program data is pending to be received
        unsigned TX                  : 1; // Set when data is pending to be sent
        unsigned ESTABLISHED         : 1; // Set when a REQUEST_CONNECTION character is received, cleared if an error occurs during transmission
        unsigned BUSY                : 1; // Set if any RX/TX operations are active
    };
} commFlags;

/**
 * Initialize registers associated with serial communication.
 * 
 * Interrupt control registers are not initialized here.
 */
void init_comms();

/**
 * Transmit any pending data to the PC.
 * 
 * Call this function whenever the output buffer TXREG is empty.
 */
void processTransmitInterrupt();

/**
 * Process any pending receive operations.
 * 
 * Call this function whenever new data has been received from the PC.
 */
void processReceiveInterrupt();

/**
 * Register that a receive operation has been interrupted.
 */
void abortReceive();

/**
 * Queue a generic data block to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param data - Pointer to the source of the data
 * @param size - Size in bytes of the data block
 * 
 * @Note The caller must ensure that the size is correct.
 */
void pc_send_data(void *data, unsigned char size);

/**
 * Queue a generic block of data to be received from the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param data - Pointer to the destination block
 * @param size - Size in bytes of the data block
 * 
 * @Note The caller must ensure that the size is correct.
 */
void pc_read_data(void *data, unsigned char size);

/**
 * Queue a program to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param program - Pointer to the program to be sent
 */
void pc_send_program(struct Program *program);

/**
 * Queue a program to be received from to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param program - Pointer to the destination
 */
void pc_read_program(struct Program *program);

/**
 * Queue an array of programs to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param programs - Pointer to the beginning of the source array
 * @param nPrograms - Number of programs in the array
 * 
 * @Note The caller must ensure that the size is correct.
 */
void pc_send_programs(struct Program *programs, unsigned char nPrograms);

/**
 * Queue an array of programs to be received from the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param programs - Pointer to the beginning of the destination array
 * @param nPrograms - Number of programs in the array
 * 
 * @Note The caller must ensure that the size is correct.
 */
void pc_read_programs(struct Program *programs, unsigned char nPrograms);

/**
 * Queue temperature data to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param temp - Pointer to the source data
 */
void pc_send_temp(unsigned short *temp);

/**
 * Queue time data to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param time - Pointer to the source data
 */
void pc_send_time(struct Time *time);

/**
 * Queue time data to be sent to the PC.
 * 
 * Nothing is done if another RX/TX operation is in progress.
 * 
 * @param time - Pointer to the destination
 */
void pc_read_time(struct Time *time);