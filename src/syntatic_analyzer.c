#include "syntatic_analyzer.h"
#include <stdio.h>
#include <stdlib.h>

/*
grammar
C -> id : [L];
L -> P R
P -> {d,d} >> add to grid
R -> , L | e
*/

p_config_pair current_pair;
uint8_t** grid;
int8_t size;

int analyze(p_config_pair cp, uint8_t** g, int8_t s) {
  current_pair = cp;
  grid = g;
  size = s;
  return C();
}

void set_position(int32_t line_offset, int32_t column_offset) {
  int row_pos = size / 2 + line_offset;
  int column_pos = size / 2 + column_offset;

  if (row_pos > size - 1 || column_pos > size - 1)
    printf("offset out of bounds {%d,%d}\n", line_offset, column_offset);
  else
    grid[row_pos][column_pos] = 1;
}

void next_pair() {
  current_pair = current_pair->next;
}

int C() {
  if (current_pair->tk == TK_id) {
    next_pair();
    if (current_pair->tk == TK_colon) {
      next_pair();
      if (current_pair->tk == TK_openBracket) {
        next_pair();
        if (L())
          if (current_pair->tk == TK_closeBracket) {
            next_pair();
            if (current_pair->tk == TK_end_config) {
              next_pair();
              return 1;
            }
          }
      }
    }
  }
  return 0;
}

int L() {
  if (P() && R()) return 1;
  return 0;
}

int P() {
  int line_offset, column_offset;
  if (current_pair->tk == TK_openCB) {
    next_pair();
    if (current_pair->tk == TK_digit) {
      line_offset = atoi(current_pair->value);
      next_pair();
      if (current_pair->tk == TK_comma) {
        next_pair();
        if (current_pair->tk == TK_digit) {
          column_offset = atoi(current_pair->value);
          next_pair();
          if (current_pair->tk == TK_closeCB) {
            next_pair();
            set_position(line_offset, column_offset);
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

int R() {
  if (current_pair->tk == TK_comma) {
    next_pair();
    if (L())
      return 1;
  }
  return 1;
}