#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

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
  unsigned char buffer[11];
  fseek(file,0x29C4,SEEK_SET);
  
  for(int i = 0; i < 6; i++){
    size_t bytes_read = fread(buffer,1,11,file);
    if (buffer[0] == 0xFF) break;

    printf("Slot %d\n", i + 1);
    
    for(int j = 0; j < 11; j++){
      if(buffer[j] == 0x50) break;
      printf("%c",table[buffer[j]]);
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
