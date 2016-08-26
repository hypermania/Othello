#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

//#include "board.h"
//#include "state.h"
#include "pattern.h"
#include "config.h"
#include "fit_weight.h"

#include "bitboard.h"
#include "bitstate.h"

static const char white_str[] = "white";
static const char black_str[] = "black";

// return 0 at success
// return -1 if ptr == NULL
//int print_board(Board board);
int print_bitboard(BitBoard board);
//int print_state(State state);
int print_bitstate(BitState *state);
int print_config(Config config);
int print_pattern(Pattern pattern);
void print_options(BitMask *moves, int movec);
void print_move_made(BitMask move, int index);
int get_human_response(int movec);
// change (in place) a string (of max size n) read from a file to a Pos sequence
Pos *file_to_seq(char *buff, int n);
Pos *randomized_file_to_seq(char *buff, int n);

Example *read_examples_from_file(const char *filename, int *count_examples);
Config read_configs_from_file(const char *filename, int *count_boards);
void *read_dat_from_file(const char *filename, int obj_size, int *count_obj);
void save_dat_to_file(const char *file_name, void *dat, int file_size);

int get_file_size(const char *filename, size_t obj_size);

#endif
