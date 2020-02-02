#include "communication.h"

void init_comms()
{
    commFlags.value = 0;
    SYNC = 0;
    SET_BAUD_PARAMS()
    TX9 = 0;
    RX9 = 0;
    SPEN = 1;
    TXEN = 1;
    CREN = 1;
}

struct
{
    // Remaining number of bytes to send/receive
    unsigned char remaining;
    // Pointer to the next byte
    char *ptrData;
    // Flag that indicates the stage
    char stage;
} commStatus;

void processTransmitInterrupt()
{
    if (commFlags.ESTABLISHED)
    {
        if (commFlags.TX)
        {
            if (--commStatus.remaining == 0)
                commFlags.BUSY = commFlags.TX = TXIE = 0;
            TXREG = *commStatus.ptrData++;
        }
    }
}

void processReceiveInterrupt()
{
    char tmp = RCREG;
    // Connection is established when a # character is received
    if (!commFlags.ESTABLISHED && !commFlags.BUSY && tmp == REQUEST_CONNECTION)
        commFlags.ESTABLISHED = 1;
    else if (commFlags.ESTABLISHED)
    {
        // Initiate send/receive based on requests sent by the PC
        if (!commFlags.BUSY)
        {
            // TODO Change order so that REQUEST_TX come before, especially those that come before
            if (tmp == REQUEST_TX_PROGRAMS)
                ; //TODO rethink
            else if (tmp == REQUEST_TX_PROGRAM)
                ; // TODO rethink
            else if (tmp == REQUEST_TX_TIME)
                pc_read_time(&currentTime);
            else if (tmp == REQUEST_RX_TEMP)
                pc_send_temp(&temperature);
            else if (tmp == REQUEST_RX_TIME)
                pc_send_time(&currentTime);
            else if (tmp == REQUEST_RX_CURRENT_PROGRAM)
                pc_send_program(activeProgram);
            else if (tmp == REQUEST_RX_PROGRAMS)
                ; //TODO rethink
            
        }
        // Receive the current buffer
        else if (commFlags.RX)
        {
            commTimeout = 0;
            if (--commStatus.remaining == 0)
                commFlags.BUSY = commFlags.RX = 0;
            *commStatus.ptrData++ = tmp;
        }
    }
}

void abortReceive()
{
    commFlags.RX = commFlags.BUSY = 0;
    commTimeout = 0;
}

void pc_send_data(void *data, unsigned char size)
{
    if (commFlags.BUSY)
        return;
    GIE = 0;
    commFlags.BUSY = 1;
    commFlags.TX = 1;
    commStatus.remaining = size;
    commStatus.ptrData = data;
    TXIE = 1;
    GIE = 1;
}

void pc_read_data(void *data, unsigned char size)
{
    if (commFlags.BUSY)
        return;
    GIE = 0;
    commFlags.BUSY = 1;
    commFlags.RX = 1;
    commStatus.remaining = size;
    commStatus.ptrData = data;
    GIE = 1;
}

void pc_send_program(struct Program *program)
{
    pc_send_data(program, sizeof(struct Program));
}

void pc_read_program(struct Program *program)
{
    pc_read_data(program, sizeof(struct Program));
}

void pc_send_programs(struct Program *programs, unsigned char nPrograms)
{
    pc_send_data(programs, nPrograms * sizeof(struct Program));
}

void pc_read_programs(struct Program *programs, unsigned char nPrograms)
{
    pc_read_data(programs, nPrograms * sizeof(struct Program));
}

void pc_send_temp(unsigned short *temp)
{
    pc_send_data(temp, sizeof(short));
}

void pc_send_time(struct Time *time)
{
    pc_send_data(time, sizeof(struct Time));
}

void pc_read_time(struct Time *time)
{
    pc_read_data(time, sizeof(struct Time));
}
