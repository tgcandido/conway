#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conway.h"

int main(int32_t argc, char** argv) {
  input_args* args = handle_commands(argc, argv);

  p_game_board conways_board = (p_game_board)malloc(sizeof(game_board));
  conways_board->size = args->grid_size;
  conways_board->grid = alloc_grid(args->grid_size);
  p_config_list_node configs = load_configs();

  if (config_exists(configs, args->config)) {
    p_config_pair selected_config = get_config(configs, args->config);
    if (analyze_and_set_positions(selected_config, conways_board)) {
      play(conways_board);
      puts("\t\tGAME OVER!!!!\n");
      free_game_resources(configs, conways_board);
      return EXIT_SUCCESS;
    }
  }

  puts(
      "\tthere's something wrong with the command or the cfg specification.\n");
  free_game_resources(configs, conways_board);
  return EXIT_FAILURE;
}

input_args* handle_commands(uint32_t argc, char** argv) {
  if (argc != 2 && argc != 3) {
    printf("\tinvalid arguments, type --help\n");
    exit(EXIT_FAILURE);
  }

  char* command_string = argv[1];

  if (strcmp(command_string, "--help") == 0) {
    print_help();
    exit(EXIT_SUCCESS);
  } else {
    input_args* args = (input_args*)malloc(sizeof(input_args));
    args->config = command_string;

    if (argc > 2) args->grid_size = atoi(argv[2]);

    if (argc <= 2 || args->grid_size > 50) args->grid_size = DEFAULT_GRID_SIZE;

    return args;
  }
}

void print_help() {
  puts(
      "\t enter the command name followed by the size of the grid - "
      "example: ./conway gli 15 \n");
  puts("\t read available commands on ./cfg/g_config\n");
  puts(
      "\t as conway's game of life is unpredictable, the game can go on "
      "forever. press ctrl+c to exit\n");
}

uint8_t** alloc_grid(int8_t size) {
  uint8_t** grid = (uint8_t**)malloc(size * sizeof(uint8_t*));
  for (int8_t i = 0; i < size; ++i) {
    grid[i] = (uint8_t*)malloc(size * sizeof(uint8_t));
    memset(grid[i], 0, size * sizeof(uint8_t));
  }
  return grid;
}

void free_game_resources(p_config_list_node configs,
                         p_game_board conways_board) {
  for (int8_t i = 0; i < conways_board->size; ++i) {
    uint8_t* row = conways_board->grid[i];
    free(row);
  }
  free_cfg_list(configs);
}
