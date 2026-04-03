#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <stdio.h>
#include <stdint.h>
#include "types.h"

void print_trainer_name(FILE *file, const unsigned char *table);
void print_trainer_team(FILE *file, const unsigned char *table);
void print_trainer_money(FILE *file);
void print_trainer_badges(FILE *file);

#endif
