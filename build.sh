#!/bin/bash
mkdir -p bin
gcc -Iinclude ./src/conway.c ./src/g_config_handler.c ./src/lexical_analyzer.c ./src/syntatic_analyzer.c -o ./bin/conway -std=c11 -g


