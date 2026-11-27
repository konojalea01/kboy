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
    printf("PC : %04lX\tHEX : %02X\t", pc, rom[pc]); 
    switch (rom[pc]) {
      case 0x01:
	printf("LD BC, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0x05:
        printf("DEC B\n");
        pc++;
        break;
      case 0x06:
        printf("LD B, $%02X\n", rom[pc + 1]);
        pc++;
        pc++;
        break;
      case 0x0B:
	printf("DEC BC\n");
	pc++;
	break;
      case 0x0C:
	printf("INC C\n");
	pc++;
	break;
      case 0x0D:
	printf("DEC C\n");
	pc++;
	break;
      case 0x0E:
        printf("LD C, $%02X\n", rom[pc + 1]);
        pc++;
        pc++;
        break;
      case 0x0F:
	printf("RRCA\n");
	pc++;
	break;
      case 0x11:
	printf("LD DE, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0x12:
	printf("LD (DE), A\n");
	pc++;
	break;
      case 0x13:
	printf("INC DE\n");
	pc++;
	break;
      case 0x20:
	printf("JR NZ, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x21:
        printf("LD HL, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
        pc++;
        pc++;
        pc++;
        break;
      case 0x28:
	printf("JR Z, %02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x2A:
	printf("LD A, (HL+)\n");
	pc++;
	break;
      case 0x2C:
	printf("INC L\n");
	pc++;
	break;
      case 0x31:
	printf("LD SP, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0x32:
        printf("LD (HL-),A\n");
        pc++;
        break;
      case 0x35:
	printf("DEC (HL)\n");
	pc++;
	break;
      case 0x36:
	printf("LD (HL), $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x3E:
	printf("LD A, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x40:
	printf("LD B, B\n");
	pc++;
	break;
      case 0x41:
	printf("LD B, C\n");
	pc++;
	break;
      case 0x42:
	printf("LD B, D\n");
	pc++;
	break;
      case 0x43:
	printf("LD B, E\n");
	pc++;
	break;
      case 0x78:
	printf("LD A, B\n");
	pc++;
	break;
      case 0x7E:
	printf("LD A, (HL)\n");
	pc++;
	break;
      case 0x80:
	printf("ADD A, B\n");
	pc++;
	break;
      case 0xA4:
	printf("AND A, H\n");
	pc++;
	break;
      case 0xA7:
	printf("AND A, A\n");
	pc++;
	break;
      case 0xAF:
        printf("XOR A\n");
        pc++;
        break;
      case 0xB1:
	printf("OR A, C\n");
	pc++;
	break;
      case 0xC3:
        printf("JMP $%02X%02X\n",rom[pc + 2], rom[pc + 1]);
        pc = ((uint16_t)rom[pc + 2] << 8) | (uint16_t)rom[pc + 1];
        break;
      case 0xC9:
	printf("RET\n");
	pc++;
	break;
      case 0xCA:
	printf("JP Z, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0xCD:
	printf("CALL $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	//pc = ((uint16_t)rom[pc + 2] << 8) | (uint16_t)rom[pc + 1];
	break;
      case 0xE0:
	printf("LDH $%02X, A\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xE2:
	printf("LDH (C), A\n");
	pc++;
	break;
      case 0xE6:
	printf("AND A, %02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xEA:
	printf("LD ($%02X%02X), A\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0xF0:
	printf("LDH A, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xF3:
	printf("DI\n");
	pc++;
	break;
      case 0xFB:
	printf("EI\n");
	pc++;
	break;
      case 0xFE:
	printf("CP A, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xFF:
	printf("RST 38\n");
	pc++;
	break;
      default:
        printf("$%02X opcode not mapped\n", rom[pc]);
        end_flag = true;
        break;

    }

  }

  //Workarea end

  free(rom);

}
