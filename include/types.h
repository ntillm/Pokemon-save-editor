#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

struct pokemon {
  uint8_t species;
  uint8_t item;
  uint8_t moveset[4];
  uint16_t trainer_id;
  uint32_t xp;
  uint16_t hp_ev;
  uint16_t attack_ev;
  uint16_t defense_ev;
  uint16_t speed_ev;
  uint16_t special_ev;
  uint8_t attack_iv;
  uint8_t defense_iv;
  uint8_t speed_iv;
  uint8_t special_iv;
  uint8_t health_iv;
  uint8_t ppval[4]; 
  uint8_t egg_cycles;
  uint8_t pokerus;
  uint16_t caught_data;
  uint8_t level;
  uint8_t status;
  uint8_t unused;
  uint16_t current_hp;
  uint16_t max_hp;
  uint16_t attack_val;
  uint16_t defense_val;
  uint16_t speed_val;
  uint16_t special_attack_val;
  uint16_t special_def_val;
  unsigned char ot_name[11];
  unsigned char nickname[11];
};

#endif
