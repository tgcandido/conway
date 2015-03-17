conway's game of life
============

C implementation of conway's game of life

command line
============
./conway [config] [board_size]

- [config] is the configuration name on g_config
- [board_size] is optional, default value is 10

example: `./conway gli 15`

adding configurations
============ 
- the accepted grammar is `name:[pair_list];`
- each pair is defined by `(a,b)`, where `a` and `b` are integers, and the values represent a living cell in the position `[size/2 + a][size/2 + b]` of the board. 
- the pairs are separated by `,`

example: `gli:[(0,0),(0,-1),(0,1),(-1,1),(-2,0)];` 

dependencies
============
developed with:
- sublime text 3 with clang-format-3.5 (google style)

tested on:
- ubuntu 14.10 with gcc 4.9.1 
- windows 8.1 with gcc 4.8.1 (MinGw)

build
============
- linux: `./build.sh`
- windows: `build.bat`
