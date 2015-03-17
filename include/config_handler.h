#pragma once

#include <stdbool.h>
#include "board.h"
#include "lexical_analyzer.h"
#include "syntatic_analyzer.h"

uint32_t get_file_size(FILE*);
char* get_configs();
p_config_list_node load_configs();
bool config_exists(p_config_list_node, const char*);
p_config_pair get_config(p_config_list_node, const char*);