#ifndef INPUT_H
#define INPUT_H

#include "definitions.h"

unsigned short temperature = 0;

void init_adc();

//TODO Determine correct return type
void read_temp();

#endif
