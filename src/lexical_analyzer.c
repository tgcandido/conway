#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>
#include "lexical_analyzer.h"

void free_cfg_list(p_config_list_node cfg_list) {
  p_config_list_node temp = NULL, aux = NULL;
  p_config_pair temp_pair = NULL, aux_pair = NULL;
  aux = cfg_list;
  while (aux) {
    temp = aux;
    aux = aux->next;
    aux_pair = temp->config;
    while (aux_pair) {
      temp_pair = aux_pair;
      aux_pair = aux_pair->next;
      free(temp_pair);
    }
  }
}

p_config_pair get_tk(const char* config, uint16_t* p) {
  char* buffer = (char*)malloc(sizeof(char) * CONFIG_MAX_LENGHT);
  p_config_pair ret_tk = (p_config_pair)malloc(sizeof(config_pair));

  uint8_t local_pos = 0;

  if (isalpha(config[*p])) {
    buffer[local_pos] = config[*p];
    while (isalpha(config[++(*p)])) {
      buffer[++local_pos] = config[*p];
    }
    ret_tk->tk = TK_id;
  } else if (config[*p] == ':') {
    (*p)++;
    buffer[local_pos] = ':';
    ret_tk->tk = TK_colon;
  } else if (config[*p] == '{') {
    (*p)++;
    buffer[local_pos] = '{';
    ret_tk->tk = TK_openCB;
  } else if (config[*p] == '}') {
    (*p)++;
    buffer[local_pos] = '}';
    ret_tk->tk = TK_closeCB;
  } else if (config[*p] == '[') {
    (*p)++;
    buffer[local_pos] = '[';
    ret_tk->tk = TK_openBracket;
  } else if (config[*p] == ']') {
    (*p)++;
    buffer[local_pos] = ']';
    ret_tk->tk = TK_closeBracket;
  } else if (config[*p] == ',') {
    (*p)++;
    buffer[local_pos] = ',';
    ret_tk->tk = TK_comma;
  } else if (config[*p] == ';') {
    (*p)++;
    buffer[local_pos] = ';';
    ret_tk->tk = TK_end_config;
  } else if (isdigit(config[*p]) || config[*p] == '-') {
    buffer[local_pos] = config[*p];
    while (isdigit(config[++(*p)])) {
      buffer[++local_pos] = config[*p];
    }
    ret_tk->tk = TK_digit;
  } else if (config[*p] == 0) {
    (*p)++;
    buffer[local_pos] = ' ';
    ret_tk->tk = TK_end_file;
  } else if (config[*p] == ' ' || config[*p] == '\t' || config[*p] == '\r' ||
             config[*p] == '\n') {
    (*p)++;
    buffer[local_pos] = ' ';
    ret_tk->tk = TK_whatever;
  }

  if (ret_tk->tk == TK_not_recognized) {
    puts("fatal error parsing the configuration\n");
    exit(1);
  }

  buffer[++local_pos] = 0;
  ret_tk->value = (char*)malloc(sizeof(buffer));
  ret_tk->next = NULL;
  strcpy(ret_tk->value, buffer);

  free(buffer);
  return ret_tk;
}

p_config_list_node get_tk_list(const char* config) {
  uint16_t position = 0;
  p_config_list_node list_head = NULL, current_list_node = NULL;
  p_config_pair head_tk = NULL, prev_tk = NULL;
  p_config_pair current_tk = get_tk(config, &position);

  while (current_tk->tk != TK_end_file) {
    if (current_tk->tk != TK_whatever) {
      if (!head_tk) {
        head_tk = current_tk;
        prev_tk = head_tk;
      } else {
        prev_tk->next = current_tk;
        prev_tk = current_tk;
      }
      if (current_tk->tk == TK_end_config) {
        if (!list_head) {
          list_head = (p_config_list_node)malloc(sizeof(config_list_node));
          list_head->config = head_tk;
          list_head->next = NULL;
          current_list_node = list_head;
        } else {
          current_list_node->next =
              (p_config_list_node)malloc(sizeof(config_list_node));
          current_list_node = current_list_node->next;
          current_list_node->config = head_tk;
          current_list_node->next = NULL;
        }
        head_tk = NULL;
      }
    }
    current_tk = get_tk(config, &position);
  }
  return list_head;
}