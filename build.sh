#!/bin/bash
gcc -D _POSIX_C_SOURCE=200809L -Wall -O2 -std=c11 -g -Iinclude ./src/conway.c ./src/player.c ./src/config_handler.c ./src/lexical_analyzer.c ./src/syntatic_analyzer.c -o conway

