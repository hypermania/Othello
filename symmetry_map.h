#ifndef SYMMETRY_MAP_H
#define SYMMETRY_MAP_H

#include <x86intrin.h>
#include "offset.h"

// reflection symmetry mapping
extern uint32_t map_reverse_256[256];
extern uint32_t map_reverse_128[128];
extern uint32_t map_reverse_64[64];
extern uint32_t map_reverse_32[32];
extern uint32_t map_reverse_16[16];

extern uint32_t map_corner_33[19683];
extern uint32_t map_edge_xx[59049];

// initialize maps
void init_maps(void);


#endif
