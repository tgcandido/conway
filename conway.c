#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g_config_handler.h"
#define GRID_SIZE 10
#define MID GRID_SIZE / 2

void handle_commands(int, char**);
void print_help();
void play();
void alloc_grid();

int** grid;

int main(int argc, char** argv) {
  alloc_grid();

  handle_commands(argc, argv);

  play();

  return EXIT_SUCCESS;
}

void handle_commands(int argc, char** argv) {
  if (argc != 2) {
    printf("invalid arguments, type -help\n");
    exit(EXIT_FAILURE);
  }

  char* command_string = argv[1];

  if (strcmp(command_string, "-help") == 0) {
    print_help();
    exit(EXIT_SUCCESS);
  } else {
    if (!set_config(command_string, grid, MID)) {
      printf("non existent configuration");
      exit(EXIT_FAILURE);
    }
  }
}

void print_help() {
  printf("\n\t read available commands on g_config. example : ./conway gli:\n");
}

void alloc_grid() {
  grid = (int**)malloc(GRID_SIZE * sizeof(int*));
  for (int i = 0; i < GRID_SIZE; ++i) {
    grid[i] = (int*)malloc(GRID_SIZE * sizeof(int));
  }
}

void play() {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      printf("%2d", grid[i][j]);
    }
    printf("\n");
  }
}
