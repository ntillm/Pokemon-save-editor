#include "save_utils.h"
#include "display_utils.h"

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
  
  FILE *file = fopen(argv[1], "rb+");
  
  if(file == NULL){
    perror("Error Opening File");
    return 1;
  }

  make_team_shiny(file);
  update_checksum(file);
  print_trainer_team(file,table);
  print_trainer_money(file);
  fclose(file);

  
  return 0; 
}
