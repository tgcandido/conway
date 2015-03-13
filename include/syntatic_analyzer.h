#pragma once

#include "lexical_analyzer.h"

int analyze(p_config_pair, uint8_t**, int32_t);
int C();
int L();
int P();
int R();
void next_pair();
void set_position(int32_t, int32_t);