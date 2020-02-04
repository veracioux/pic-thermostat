#pragma once

#include "definitions.h"

unsigned short temperature = 0x3031;

void init_adc();

//TODO Determine correct return type
void read_temp();