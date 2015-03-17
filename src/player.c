#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <time.h>
#endif

void sleep_ms(int32_t ms) {
#ifdef __linux__
  struct timespec ts_struct;
  ts_struct.tv_sec = 0;
  ts_struct.tv_nsec = ms * 1000000;
  nanosleep(&ts_struct, NULL);
#elif _WIN32
  Sleep(ms);
#endif
}

bool out_of_bounds(uint8_t line, uint8_t column, uint8_t max) {
  return line >= max || line < 0 || column >= max || column < 0;
}

uint8_t get_neighbors(p_game_board conways_board, p_game_cell cell) {
  uint8_t ret_val = 0;
  int8_t size = conways_board->size;
  if (!out_of_bounds(cell->line + 1, cell->column, size) &&
      conways_board->grid[cell->line + 1][cell->column]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line + 1, cell->column + 1, size) &&
      conways_board->grid[cell->line + 1][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line + 1, cell->column - 1, size) &&
      conways_board->grid[cell->line + 1][cell->column - 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line, cell->column + 1, size) &&
      conways_board->grid[cell->line][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line, cell->column - 1, size) &&
      conways_board->grid[cell->line][cell->column - 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column + 1, size) &&
      conways_board->grid[cell->line - 1][cell->column + 1]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column, size) &&
      conways_board->grid[cell->line - 1][cell->column]) {
    ++ret_val;
  }
  if (!out_of_bounds(cell->line - 1, cell->column - 1, size) &&
      conways_board->grid[cell->line - 1][cell->column - 1]) {
    ++ret_val;
  }
  return ret_val;
}

void print_game(p_game_board conways_board) {
  for (int32_t i = 0; i < conways_board->size; ++i) {
    for (int32_t j = 0; j < conways_board->size; ++j) {
      if (conways_board->grid[i][j]) {
        printf("#  ");
      } else
        printf("-  ");
    }
    printf("\n");
  }
}

bool has_living_cells(p_game_board conways_board) {
  for (int8_t line = 0; line < conways_board->size; ++line) {
    for (int8_t column = 0; column < conways_board->size; ++column) {
      if (conways_board->grid[line][column]) return true;
    }
  }
  return false;
}

void play(p_game_board conways_board) {
  uint8_t aux_grid[conways_board->size][conways_board->size];
  p_game_cell cell = (p_game_cell)malloc(sizeof(game_cell));

  while (has_living_cells(conways_board)) {
    memset(aux_grid, 0,
           conways_board->size * conways_board->size * sizeof(uint8_t));
    for (int8_t line = 0; line < conways_board->size; ++line) {
      for (int8_t column = 0; column < conways_board->size; ++column) {
        cell->line = line;
        cell->column = column;
        uint8_t neighbors_count = get_neighbors(conways_board, cell);
        if ((conways_board->grid[line][column] &&
             (neighbors_count == 2 || neighbors_count == 3)) ||
            (conways_board->grid[line][column] == 0 && neighbors_count == 3)) {
          aux_grid[line][column] = 1;
        } else
          aux_grid[line][column] = 0;
      }
    }

    for (int8_t line = 0; line < conways_board->size; ++line) {
      for (int8_t column = 0; column < conways_board->size; ++column) {
        conways_board->grid[line][column] = aux_grid[line][column];
      }
    }

#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif

    print_game(conways_board);
    sleep_ms(150);
  }
  return;
}
