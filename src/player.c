#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include "player.h"

typedef struct cell_struct {
  uint16_t line;
  uint16_t column;
} game_cell;
typedef game_cell* p_game_cell;

void sleep_ms(int32_t);
bool out_of_bounds(uint8_t, uint8_t, uint8_t);
uint8_t get_neighbors(uint8_t**, int8_t, p_game_cell);
void print_game(uint8_t**, int8_t);
bool has_living_cells(uint8_t**, int8_t);
void play(uint8_t**, int8_t);

void sleep_ms(int32_t ms) {
  struct timespec ts_struct;
  ts_struct.tv_sec = 0;
  ts_struct.tv_nsec = ms * 1000000;
  nanosleep(&ts_struct, NULL);
}

bool out_of_bounds(uint8_t line, uint8_t column, uint8_t max) {
  return line >= max || line < 0 || column >= max || column < 0;
}

uint8_t get_neighbors(uint8_t** grid, int8_t size, p_game_cell cell) {
  uint8_t ret_val = 0;
  if (!out_of_bounds(cell->line + 1, cell->column, size) &&
      grid[cell->line + 1][cell->column]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line + 1, cell->column + 1, size) &&
      grid[cell->line + 1][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line + 1, cell->column - 1, size) &&
      grid[cell->line + 1][cell->column - 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line, cell->column + 1, size) &&
      grid[cell->line][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line, cell->column - 1, size) &&
      grid[cell->line][cell->column - 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column + 1, size) &&
      grid[cell->line - 1][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column, size) &&
      grid[cell->line - 1][cell->column]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column - 1, size) &&
      grid[cell->line - 1][cell->column - 1]) {
    ++ret_val;
  }
  return ret_val;
}

void print_game(uint8_t** grid, int8_t size) {
  for (int32_t i = 0; i < size; ++i) {
    for (int32_t j = 0; j < size; ++j) {
      if (grid[i][j]) {
        printf("#  ");
      } else
        printf("-  ");
    }
    printf("\n");
  }
}

bool has_living_cells(uint8_t** grid, int8_t size) {
  for (int8_t line = 0; line < size; ++line) {
    for (int8_t column = 0; column < size; ++column) {
      if (grid[line][column]) return true;
    }
  }
  return false;
}

void play(uint8_t** grid, int8_t size) {
  uint8_t aux_grid[size][size];
  p_game_cell cell = (p_game_cell)malloc(sizeof(game_cell));

  while (has_living_cells(grid, size)) {
    memset(aux_grid, 0, size * size * sizeof(uint8_t));
    for (int8_t line = 0; line < size; ++line) {
      for (int8_t column = 0; column < size; ++column) {
        cell->line = line;
        cell->column = column;
        uint8_t neighbors_count = get_neighbors(grid, size, cell);
        if ((grid[line][column] &&
             (neighbors_count == 2 || neighbors_count == 3)) ||
            (grid[line][column] == 0 && neighbors_count == 3)) {
          aux_grid[line][column] = 1;
        } else
          aux_grid[line][column] = 0;
      }
    }

    for (int8_t line = 0; line < size; ++line) {
      for (int8_t column = 0; column < size; ++column) {
        grid[line][column] = aux_grid[line][column];
      }
    }

    system("clear");
    print_game(grid, size);
    sleep_ms(125);
  }
  return;
}
