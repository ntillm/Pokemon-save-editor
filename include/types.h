#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

struct pokemon {
  unsigned char nickname[11];
  uint16_t current_hp;
  uint16_t max_hp;
  uint8_t level;
  uint8_t species;
  uint8_t status;
  uint32_t xp;
  uint8_t moveset[4];
  uint8_t ppval[4]; 
  uint8_t attack_iv;
  uint8_t speed_iv;
  uint8_t defense_iv;
  uint8_t health_iv;
  uint8_t special_iv;
  uint16_t trainer_id;
  unsigned char ot_name[11];
};

#endif
