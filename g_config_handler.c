#include "g_config_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct offset_position_struct {
  int row_offset;
  int column_offset;
} offset_position;

long int get_file_size(FILE*);
void set_grid_position(int**, int, offset_position*);
int get_number(char*, int*);

bool set_config(char* config_name, int** grid, int size) {
  FILE* config_file = fopen("g_config", "r");

  if (!config_file) {
    printf("error opening file");
    exit(EXIT_FAILURE);
  }

  long int file_size = get_file_size(config_file);
  char* buffer = (char*)malloc(file_size);
  offset_position* offset_pos =
      (offset_position*)malloc(sizeof(offset_position));
  int offset;
  int mid_point = size / 2;
  bool row_copied = false;

  fread(buffer, 1, file_size, config_file);

  char* config = strtok(buffer, ";");
  while (config) {
    if (strstr(config, config_name)) {
      int i = 0;
      while (config[i]) {
        if (isdigit(config[i]) || config[i] == '-') {
          offset = get_number(config, &i);
          if (!row_copied) {
            offset_pos->row_offset = offset;
            row_copied = true;
          } else {
            offset_pos->column_offset = offset;
            set_grid_position(grid, mid_point, offset_pos);
            row_copied = false;
          }
        }
        ++i;
      }
      free(buffer);
      return true;
    }
    config = strtok(NULL, ";");
  }
  free(buffer);
  return false;
}

long int get_file_size(FILE* file) {
  fseek(file, 0, SEEK_END);
  long int size = ftell(file);
  fseek(file, 0, SEEK_SET);
  return size;
}

void set_grid_position(int** grid, int mid_point, offset_position* off_pos) {
  int row_pos = mid_point + off_pos->row_offset;
  int column_pos = mid_point + off_pos->column_offset;

  if (row_pos > mid_point * 2 - 1 || column_pos > mid_point * 2 - 1)
    printf("offset out of bounds {%d,%d}\n", off_pos->row_offset,
           off_pos->column_offset);
  else
    grid[row_pos][column_pos] = 1;
}

int get_number(char* config, int* i) {
  char buffer[8];
  int p = 0;
  while (config[*i] != ',' && config[*i] != '}') {
    buffer[p] = config[*i];
    (*i)++;
    p++;
  }
  buffer[p] = 0;
  return atoi(buffer);
}
