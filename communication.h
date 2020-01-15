#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#include <xc.h>
#include "definitions.h"

void eeprom_read_programs(struct Program *programs);

void eeprom_store_programs(struct Program *programs);

void pc_read_programs(struct Program *programs);

void pc_send_programs(struct Program *programs);

void pc_send_current_program(struct Program *program);

void pc_send_temp(int temp);

#endif
