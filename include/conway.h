#pragma once

#include "board.h"
#include "config_handler.h"
#include "player.h"

#define DEFAULT_GRID_SIZE 10

typedef struct input_args_struct {
  char* config;
  int8_t grid_size;
} input_args;

input_args* handle_commands(uint32_t, char**);
void print_help();
uint8_t** alloc_grid(int8_t);
void free_game_resources(p_config_list_node, p_game_board);
