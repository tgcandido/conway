#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g_config_handler.h"
#define DEFAULT_GRID_SIZE 10

typedef struct input_args_struct {
  char* config;
  int grid_size;
} input_args;

input_args* handle_commands(int, char**);
void print_help();
void play(int**, int);
int** alloc_grid(int);

int main(int argc, char** argv) {
  input_args* args = handle_commands(argc, argv);

  int** grid = alloc_grid(args->grid_size);

  if (!set_config(args->config, grid, args->grid_size)) {
    printf("non existent configuration");
    exit(EXIT_FAILURE);
  }

  play(grid, args->grid_size);

  return EXIT_SUCCESS;
}

input_args* handle_commands(int argc, char** argv) {
  if (argc > 3) {
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

int** alloc_grid(int size) {
  int** grid = (int**)malloc(size * sizeof(int*));
  for (int i = 0; i < size; ++i) {
    grid[i] = (int*)malloc(size * sizeof(int));
  }
  return grid;
}

void play(int** grid, int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      printf("%2d", grid[i][j]);
    }
    printf("\n");
  }
}
