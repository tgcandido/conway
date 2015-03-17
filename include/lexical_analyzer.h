#pragma once

#include <inttypes.h>

#define CONFIG_MAX_LENGHT 32

enum TK {
  TK_not_recognized,
  TK_id,
  TK_colon,
  TK_openBracket,
  TK_closeBracket,
  TK_openP,
  TK_closeP,
  TK_comma,
  TK_digit,
  TK_end_config,
  TK_end_file,
  TK_whatever
} typedef lex_TK;

struct tk_value_pair {
  lex_TK tk;
  char* value;
  struct tk_value_pair* next;
} typedef config_pair;
typedef config_pair* p_config_pair;
typedef p_config_pair* p2_config_pair;

struct cfg_list_node {
  p_config_pair config;
  struct cfg_list_node* next;
} typedef config_list_node;
typedef config_list_node* p_config_list_node;

void free_cfg_list(p_config_list_node);
p_config_pair get_tk(const char*, uint16_t*);
p_config_list_node get_tk_list(const char*);
