#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "g_config_handler.h"
#include "lexical_analyzer.h"
#include "syntatic_analyzer.h"

uint32_t get_file_size(FILE*);
char* get_configs();
void load_configs();
bool config_exists(const char*);
bool set_grid_positions(uint8_t**, int32_t);

p_config_list_node available_configs;
p_config_pair selected_config;

uint32_t get_file_size(FILE* file) {
  fseek(file, 0, SEEK_END);
  uint32_t size = ftell(file);
  fseek(file, 0, SEEK_SET);
  return size;
}

char* get_configs() {
  FILE* config_file = fopen("../cfg/g_config", "r");

  if (!config_file) {
    printf("error opening file");
    exit(EXIT_FAILURE);
  }

  uint32_t file_size = get_file_size(config_file);
  char* buffer = (char*)malloc(file_size);
  fread(buffer, 1, file_size, config_file);

  return buffer;
}

void load_configs() {
  const char* config_text = get_configs();
  available_configs = get_tk_list(config_text);
}

bool config_exists(const char* config) {
  p_config_list_node aux = available_configs;
  while (aux) {
    if (strcmp(aux->config->value, config) == 0) {
      selected_config = aux->config;
      return true;
    }
    aux = aux->next;
  }
  return false;
}

bool set_grid_positions(uint8_t** grid, int32_t size) {
  return analyze(selected_config, grid, size);
}

void free_cfg_resources() {
  free_cfg_list(available_configs);
}