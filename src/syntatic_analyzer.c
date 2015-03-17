#include <stdio.h>
#include <stdlib.h>
#include "syntatic_analyzer.h"

/*
grammar
C -> id : [L];
L -> P R
P -> (d,d) >> add to grid
R -> , L | e
*/

bool analyze_and_set_positions(p_config_pair current_pair, p_game_board board) {
  return C(current_pair,board);
}

bool set_position(p_game_board conways_board, int32_t line_offset, int32_t column_offset) {
  const int32_t row_pos = conways_board->size / 2 + line_offset;
  const int32_t column_pos = conways_board->size / 2 + column_offset;

  if (row_pos > conways_board->size - 1 || column_pos > conways_board->size - 1){
    printf("\toffset out of bounds {%d,%d}\n", line_offset, column_offset);
    return false;
  }
  conways_board->grid[row_pos][column_pos] = 1;
  return true;
}

void next_pair(p2_config_pair current_pair) {
  *current_pair = (*current_pair)->next;
}

bool C(p_config_pair current_pair, p_game_board board) {
  if (current_pair->tk == TK_id) {
    next_pair(&current_pair);
    if (current_pair->tk == TK_colon) {
      next_pair(&current_pair);
      if (current_pair->tk == TK_openBracket) {
        next_pair(&current_pair);
        if (L(&current_pair, board))
          if (current_pair->tk == TK_closeBracket) {
            next_pair(&current_pair);
            if (current_pair->tk == TK_end_config) {
              next_pair(&current_pair);
              return true;
            }
          }
      }
    }
  }
  return false;
}

bool L(p2_config_pair current_pair, p_game_board board) {
  if (P(current_pair,board) && R(current_pair,board)) return true;
  return false;
}

bool P(p2_config_pair current_pair, p_game_board board) {
  int line_offset, column_offset;
  if ((*current_pair)->tk == TK_openP) {
    next_pair(current_pair);
    if ((*current_pair)->tk== TK_digit) {
      line_offset = atoi((*current_pair)->value);
      next_pair(current_pair);
      if ((*current_pair)->tk== TK_comma) {
        next_pair(current_pair);
        if ((*current_pair)->tk== TK_digit) {
          column_offset = atoi((*current_pair)->value);
          next_pair(current_pair);
          if ((*current_pair)->tk== TK_closeP) {
            next_pair(current_pair);
            return set_position(board, line_offset, column_offset);
          }
        }
      }
    }
  }
  return false;
}

bool R(p2_config_pair current_pair, p_game_board board) {
  if ((*current_pair)->tk == TK_comma) {
    next_pair(current_pair);
    if (L(current_pair, board))
      return true;
  }
  return true;
}