#pragma once

#include <stdbool.h>
#include "board.h"
#include "player.h"

typedef struct cell_struct {
  uint16_t line;
  uint16_t column;
} game_cell;
typedef game_cell* p_game_cell;

void sleep_ms(int32_t);
bool out_of_bounds(uint8_t, uint8_t, uint8_t);
uint8_t get_neighbors(p_game_board, p_game_cell);
void print_game(p_game_board);
bool has_living_cells(p_game_board);
void play(p_game_board);
