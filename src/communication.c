#include "communication.h"


void init_comms()
{
    SYNC = 0;
    SET_BAUD_PARAMS()
    TX9 = 0;
    RX9 = 0;
    SPEN = 1;
    CREN = 1;
}

void processCommInterrupt()
{
    
}

inline void send_byte(char byte)
{
    TXREG = byte;
}

void pc_read_programs(struct Program *programs)
{
    
}

void pc_send_programs(struct Program *programs)
{
    
}

void pc_send_current_program(struct Program *program)
{
    
}

void pc_send_temp(unsigned short temp)
{
    
}