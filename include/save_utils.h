#ifndef SAVE_UTILS_H
#define SAVE_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define PARTY_COUNT_ADDR 0x2865
#define PARTY_DATA_ADDR 0x286D
#define CHECKSUM_START_ADDR 0x2009
#define CHECKSUM_END_ADDR 0x2D0D
#define PKMN_SIZE 48
#define IV_OFFSET 0x15

void make_shiny(FILE *file, int slot_index);
void make_team_shiny(FILE *file);
void update_checksum(FILE *file);
void inject_pokemon_to_party(FILE *file, uint8_t species, uint8_t level);
void inject_pokemon_to_pc(FILE *file, uint8_t species, uint8_t level);

#endif
