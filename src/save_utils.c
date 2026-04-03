#include "save_utils.h"


void update_checksum(FILE *file){
  uint16_t checksum = 0;
  //size of checksum in bytes(distance between 0x2009 and 2B82)
  unsigned char buffer[2938];
  fseek(file,CHECKSUM_START_ADDR,SEEK_SET);
  fread(buffer,1,2938,file);
  for(int i=0; i < 2938; i++){
    checksum += buffer[i]; 
  }
  unsigned char bytes[2];
  bytes[0] = checksum & 0xFF; 
  bytes[1] = (checksum >> 8) & 0xFF;
  //printf("Calculated Checksum: %04X\n", bytes[0]);
  //move to checksum offset
  fseek(file,CHECKSUM_END_ADDR,SEEK_SET);
  //write to checksum offset
  fwrite(bytes,1,2,file);

}


void make_shiny(FILE *file,int slot_index){
  //how we determine which pokemon to make shiny
  int offset = PARTY_DATA_ADDR + (slot_index * PKMN_SIZE);
  fseek(file, offset + IV_OFFSET, SEEK_SET);
  //attack iv:15 speed,defense,special iv:10
  fputc(0xFA,file);
  fputc(0xAA,file);
}


void make_team_shiny(FILE *file){
  uint8_t team_count; 
  fseek(file,PARTY_COUNT_ADDR,SEEK_SET);
  if(fread(&team_count,1,1,file)!= 1) return;

  if(team_count == 0 || team_count > 6){ 
      printf("Invalid pokemon team count: %d\n",team_count);
      return;
  }
    for(int i = 0; i < team_count; i++) {
      make_shiny(file, i); 
    }
  printf("Successfully updated %d pokemon to shiny status!\n",team_count); 
} 

