#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "romloader.h"
#include "validpath.h"

#define FLAGNUMBER 1
#define MAXFLAGLEN 3

int main(int argc, char *argv[]){

  if (argc < 2){
    fprintf(stderr, "Usage: %s <rom_file> [-v]\n", argv[0]);
    return 1;
  }

  const char flags[FLAGNUMBER][MAXFLAGLEN] = {"-v"};

  bool verbose_flag = false;

  bool end_flag = false;

  if (argc > 2) {
    for (int i = 2 ; i < argc ; i++){
      
      for (int j = 0 ; j < FLAGNUMBER ; j++) {

        if (strcmp(argv[i],flags[j]) == 0){
          
          if (strcmp(argv[i],flags[0]) == 0) {
            verbose_flag = true;
          }

        }

      }

    }

  }

  if(!isValidPath(argv[1])){
    fprintf(stderr, "Error: invalid path or file: %s\n", argv[1]);
    return 1;
  }

  size_t rom_size = 0;

  uint8_t *rom = loadrom(argv[1], &rom_size);

  if (!rom) {
    fprintf(stderr, "Error: ROM not loaded correctly.\n");
    return 1;
  }

  if (verbose_flag) {
    printf("A GameBoy ROM cartridge with a whoping %zu KB in size!. \n",rom_size/1024);
  }
  
  //Workarea start
  
  //printf("%02X", rom[0]);
  
  long int pc = 0;
  
  while(!end_flag) {

    switch (rom[pc]) {
      case 0x05:
        printf("DEC B\n");
        pc++;
        break;
      case 0x06:
        printf("LD B,%02X\n", rom[pc + 1]);
        pc++;
        pc++;
        break;
      case 0x0E:
        printf("LD C,%02X\n", rom[pc + 1]);
        pc++;
        pc++;
        break;
      case 0x21:
        printf("LD HL,%02X%02X\n", rom[pc+2], rom[pc+1]);
        pc++;
        pc++;
        pc++;
        break;
      case 0x32:
        printf("LD (HL-),A\n");
        pc++;
        break;
      case 0xAF:
        printf("XOR \n");
        pc++;
        break;
      case 0xC3:
        printf("JMP %02X%02X\n",rom[pc + 2], rom[pc + 1]);
        pc = ((uint16_t)rom[pc + 2] << 8) | (uint16_t)rom[pc + 1];
        break;
      default:
        printf("%02X opcode not mapped\n", rom[pc]);
        end_flag = true;
        break;

    }

  }

  //Workarea end

  free(rom);

}
