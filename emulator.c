#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

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

};

unsigned char decode(unsigned char c, const unsigned char *table){
 if (table[c] != 0){
  return table[c];
  } else{
  return 0;
  }
}

void print_trainer_name(FILE *file, const unsigned char *table){
  unsigned char buffer[11]; 
  fseek(file,0x200B,SEEK_SET);
  size_t bytes_read = fread(buffer,1,11,file);
 


  for(int i = 0; i < bytes_read; i++){
    unsigned char byte = decode(buffer[i], table);
    if(!byte) {break;} 
    else {
      printf("%c", byte);
    }
  }
  printf("\n");
}

void print_trainer_id(FILE *file){
  unsigned char buffer[2];
  fseek(file,0x2009,SEEK_SET);
  size_t bytes_read = fread(buffer,1,2,file);

  uint16_t id = buffer[0] << 8 | buffer[1];

  printf("%u", id);
  printf("\n");
}

void print_trainer_badges(FILE *file){
  unsigned char buffer[1];
  fseek(file,0x23DD,SEEK_SET);
  size_t bytes_read = fread(buffer,1,1,file);

  const char *badge_names[] = {
    "Zephyr Badge", // Bit 0
    "Hive Badge",   // Bit 1
    "Plain Badge",  // Bit 2
    "Fog Badge",    // Bit 3
    "Storm Badge",  // Bit 4
    "Mineral Badge",// Bit 5
    "Glacier Badge",// Bit 6
    "Rising Badge"  // Bit 7
  };

  for (int i = 0; i < 7; i++){
    if(buffer[0] & 1 << i){
      printf("%s\n",badge_names[i]);
    }
  }
}

void print_trainer_money(FILE *file){
  unsigned char buffer[3];
  fseek(file,0x23DC,SEEK_SET);
  size_t bytes_read = fread(buffer,1,3,file);

  uint32_t money = buffer[0] << 16 | buffer[1] << 8 | buffer[2];

  printf("%u", money);
  printf("\n");
}

void print_trainer_team(FILE *file, const unsigned char *table){
 
  struct pokemon party[6];

  for(int i = 0; i < 6; i++){
    unsigned char buffer[48];
    fseek(file,0x286D + (i * 48),SEEK_SET);
    size_t bytes_read = fread(buffer,1,48,file);
  
    

    party[i].level = buffer[0x1F];
    party[i].max_hp = (buffer[0x24] << 8) | buffer[0x24 + 1];
    party[i].current_hp = (buffer[0x22] << 8) | buffer[0x22 + 1];
    party[i].species = buffer[0x00];
    party[i].xp = (buffer[0x08] << 16) | (buffer[0x08 + 1] << 8) | buffer[0x08 + 2];
    party[i].attack_iv = buffer[0x15] >> 4;
    party[i].defense_iv = buffer[0x15] & 0x0F;
    party[i].speed_iv = buffer[0x16] >> 4;
    party[i].special_iv = buffer[0x16] & 0x0F;
    party[i].health_iv = ((party[i].attack_iv & 0x01) << 3) | ((party[i].defense_iv & 0x01) << 2) | ((party[i].speed_iv & 0x01) << 1) | ((party[i].special_iv & 0x01));
    

    for(int j = 0; j < 4; j++) {
        party[i].moveset[j] = buffer[0x02 + j];
        party[i].ppval[j] = buffer[0x17 + j];
    }
  }

   fseek(file,0x29CF,SEEK_SET);
  
  for(int i = 0; i < 6; i++){
    size_t bytes_read = fread(party[i].nickname,1,11,file);
    if (party[i].nickname[0] == 0xFF) break;

    printf("Slot %d\n", i + 1);
    
    for(int j = 0; j < 11; j++){
      if(party[i].nickname[j] == 0x50) break;
      printf("%c",table[party[i].nickname[j]]);
    }
    // Inside your second loop, after decoding the name:
    printf("  Level: %u | HP: %u/%u XP: %u (Species ID: %02X)\n attack iv: %d | defense iv: %d | speed iv: %d | special iv: %d | health iv: %d\n", 
        party[i].level, 
        party[i].current_hp, 
        party[i].max_hp, 
        party[i].xp,
        party[i].species,
        party[i].attack_iv,
        party[i].defense_iv,
        party[i].speed_iv,
        party[i].special_iv,
        party[i].health_iv);
  
    for (int j = 0; j < 4; j++){
      if(party[i].moveset[j] == 0x00) break; 
      printf(" Moveset: %02X (PP:%d/??) ", party[i].moveset[j], party[i].ppval[j]);
      printf("\n");
    }
    printf("\n");
  }
}


int main(int argc, char *argv[]){
  unsigned char table[256] = {0};
  
  for(int i = 0; i < 26; i++){
    table[0x80 + i] = 'A' + i;
  }

  for(int i = 0; i < 26; i++){
    table[0xA0 + i] = 'a' + i;
  }
  
  table[0x50] = '\0';
  table[0x7F] = ' ';

  if (argc != 2){
    printf("Usage: %s <filename>\n", argv[0]);
    exit(-1);

  }

  //unsigned char buffer[MAX];
  
  FILE *file = fopen(argv[1], "rb");
  
  if(file == NULL){
    perror("Error Opening File");
    return 1;
  }
  
  print_trainer_name(file,table); 
  print_trainer_id(file);
  print_trainer_badges(file); 
  print_trainer_money(file);  
  print_trainer_team(file, table);

  fclose(file);

  
  return 0; 
}
