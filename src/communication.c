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
} commStatus;

void processTransmitInterrupt()
{
    if (commFlags.ESTABLISHED)
    {
        if (commFlags.TX)
        {
            if (--commStatus.remaining == 0)
                commFlags.BUSY = commFlags.TX = 0;
            TXREG = *commStatus.ptrData++;
        }
    }
}

void processReceiveInterrupt()
{
    // Connection is established when a # character is received
    if (!commFlags.ESTABLISHED && !commFlags.BUSY && RCREG == CONNECTION_REQUEST)
        commFlags.ESTABLISHED = 1;
    else if (commFlags.ESTABLISHED)
    {
        // Initiate send/receive based on requests sent by the PC
        if (!commFlags.BUSY)
        {
            char tmp = RCREG;
            if (tmp == TEMP_TX_REQUEST)
                pc_send_temp(temperature);
            else if (tmp == PROGRAM_TX_REQUEST)
                pc_send_program(activeProgram);
            else if (tmp == PROGRAMS_TX_REQUEST)
                pc_send_programs(programs, programsSize);
            else if (tmp == PROGRAMS_RX_REQUEST)
                pc_read_programs(programs, programsSize);
        }
        // Send/receive the current buffer
        if (commFlags.RX)
        {
            if (--commStatus.remaining == 0)
                commFlags.BUSY = commFlags.RX = 0;
            *commStatus.ptrData++ = RCREG;
        }
    }
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

void pc_send_temp(unsigned short temp)
{
    pc_send_data(&temp, sizeof temp);
}