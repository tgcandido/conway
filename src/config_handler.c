#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_handler.h"

uint32_t get_file_size(FILE* file) {
  fseek(file, 0, SEEK_END);
  uint32_t size = ftell(file);
  fseek(file, 0, SEEK_SET);
  return size;
}

char* get_configs() {
  FILE* config_file = fopen("cfg/g_config", "rb");
  if (!config_file) {
    puts("\terror opening file\n");
    exit(EXIT_FAILURE);
  }

  const uint32_t file_size = get_file_size(config_file);
  char* buffer = (char*)malloc(file_size);
  fread(buffer, 1, file_size, config_file);

  buffer[file_size] = '\0';

  return buffer;
}

p_config_list_node load_configs() {
  const char* config_text = get_configs();
  return get_tk_list(config_text);
}

bool config_exists(p_config_list_node available_configs, const char* config) {
  p_config_list_node aux = available_configs;
  while (aux) {
    if (strcmp(aux->config->value, config) == 0) {
      return true;
    }
    aux = aux->next;
  }
  return false;
}

p_config_pair get_config(p_config_list_node available_configs,
                         const char* config) {
  p_config_list_node aux = available_configs;
  while (aux) {
    if (strcmp(aux->config->value, config) == 0) {
      return aux->config;
    }
    aux = aux->next;
  }
  return NULL;
}
