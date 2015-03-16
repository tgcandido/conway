#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

void load_configs();
bool config_exists(const char*);
bool set_grid_positions(uint8_t**, int8_t);
void free_cfg_resources();