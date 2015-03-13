#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g_config_handler.h"
#define DEFAULT_GRID_SIZE 10

typedef struct input_args_struct {
  char* config;
  int32_t grid_size;
} input_args;

input_args* handle_commands(uint32_t, char**);
void print_help();
void play(uint8_t**, int32_t);
uint8_t** alloc_grid(int32_t);

int main(uint32_t argc, char** argv) {
  input_args* args = handle_commands(argc, argv);
  uint8_t** grid = alloc_grid(args->grid_size);

  load_configs();

  if (config_exists(args->config) &&
      set_grid_positions(grid, args->grid_size)) {
    play(grid, args->grid_size);
    free_cfg_resources();
    return EXIT_SUCCESS;
  } else {
    puts(
        "there's something wrong with the command or the cfg specification. "
        "check that and "
        "try again\n");
    return EXIT_FAILURE;
  }
}

input_args* handle_commands(uint32_t argc, char** argv) {
  if (argc != 2 && argc != 3) {
    printf("invalid arguments, type -help\n");
    exit(EXIT_FAILURE);
  }

  char* command_string = argv[1];

  if (strcmp(command_string, "-help") == 0) {
    print_help();
    exit(EXIT_SUCCESS);
  } else {
    input_args* args = (input_args*)malloc(sizeof(input_args));
    args->config = command_string;

    if (argc > 2)
      args->grid_size = atoi(argv[2]);
    else
      args->grid_size = DEFAULT_GRID_SIZE;
    return args;
  }
  return NULL;
}

void print_help() {
  printf(
      "\n\t enter the command name followed by the size of the grid. default "
      "size is 10\n");
  printf("\n\t read available commands on g_config file\n");
  printf("\n\t example: ./conway gli 15 \n");
}

uint8_t** alloc_grid(int32_t size) {
  uint8_t** grid = (uint8_t**)malloc(size * sizeof(uint8_t*));
  for (int32_t i = 0; i < size; ++i) {
    grid[i] = (uint8_t*)malloc(size * sizeof(uint8_t));
  }
  return grid;
}

void play(uint8_t** grid, int32_t size) {
  for (int32_t i = 0; i < size; ++i) {
    for (int32_t j = 0; j < size; ++j) {
      printf("%2d", grid[i][j]);
    }
    printf("\n");
  }
}
