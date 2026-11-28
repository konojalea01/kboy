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
      case 0x00:
	printf("NOP\n");
	pc++;
	break;
      case 0x01:
	printf("LD BC, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0x03:
	printf("INC BC\n");
	pc++;
	break;
      case 0x04:
	printf("INC B\n");
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
      case 0x07:
	printf("RLCA\n");
	pc++;
	break;
      case 0x08:
	printf("LD ($%02X%02X), SP\n", rom[pc + 2], rom[pc + 1]);
	pc++;
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
      case 0x14:
	printf("INC D\n");
	pc++;
	break;
      case 0x15:
	printf("DEC D\n");
	pc++;
	break;
      case 0x16:
	printf("LD D, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x18:
	printf("JR $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x19:
	printf("ADD HL, DE\n");
	pc++;
	break;
      case 0x1A:
	printf("LD A, (DE)\n");
	pc++;
	break;
      case 0x1C:
	printf("INC E\n");
	pc++;
	break;
      case 0x1D:
	printf("DEC E\n");
	pc++;
	break;
      case 0x1E:
	printf("LD E, $%02X\n", rom[pc + 1]);
	pc++;
	break;
      case 0x1F:
	printf("RRA\n");
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
      case 0x22:
	printf("LD (HL+), A\n");
	pc++;
	break;
      case 0x23:
	printf("INC HL\n");
	pc++;
	break;
      case 0x25:
	printf("DEC H\n");
	pc++;
	break;
      case 0x26:
	printf("LD H, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x27:
	printf("DAA\n");
	pc++;
	break;
      case 0x28:
	printf("JR Z, %02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0x29:
	printf("ADD HL, HL\n");
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
      case 0x33:
	printf("INC SP\n");
	pc++;
	break;
      case 0x34:
	printf("INC (HL)\n");
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
      case 0x3C:
	printf("INC A\n");
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
      case 0x44:
	printf("LD B, H\n");
	pc++;
	break;
      case 0x45:
	printf("LD B, L\n");
	pc++;
	break;
      case 0x46:
	printf("LD B, (HL)\n");
	pc++;
	break;
      case 0x49:
	printf("LD C, C\n");
	pc++;
	break;
      case 0x52:
	printf("LD D, D\n");
	pc++;
	break;
      case 0x53:
	printf("LD D, E\n");
	pc++;
	break;
      case 0x54:
	printf("LD D, H\n");
	pc++;
	break;
      case 0x56:
	printf("LD D, (HL)\n");
	pc++;
	break;
      case 0x5E:
	printf("LD E, (HL)\n");
	pc++;
	break;
      case 0x5F:
	printf("LD E, A\n");
	pc++;
	break;
      case 0x63:
	printf("LD H, E\n");
	pc++;
	break;
      case 0x66:
	printf("LD H, (HL)\n");
	pc++;
	break;
      case 0x67:
	printf("LD H, A\n");
	pc++;
	break;
      case 0x69:
	printf("LD L, C\n");
	pc++;
	break;
      case 0x6E:
	printf("LD L, (HL)\n");
	pc++;
	break;
      case 0x73:
	printf("LD (HL), E\n");
	pc++;
	break;
      case 0x77:
	printf("LD (HL), A\n");
	pc++;
	break;
      case 0x78:
	printf("LD A, B\n");
	pc++;
	break;
      case 0x79:
	printf("LD A, C\n");
	pc++;
	break;
      case 0x7A:
	printf("LD A, D\n");
	pc++;
	break;
      case 0x7B:
	printf("LD A, E\n");
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
      case 0x83:
	printf("ADD A, E\n");
	pc++;
	break;
      case 0x86:
	printf("ADD A, (HL)\n");
	pc++;
	break;
      case 0x87:
	printf("ADD A, A\n");
	pc++;
	break;
      case 0x88:
	printf("ADC A, B\n");
	pc++;
	break;
      case 0x89:
	printf("ADC A, C\n");
	pc++;
	break;
      case 0x8A:
	printf("ADC A, D\n");
	pc++;
	break;
      case 0x8C:
	printf("ADC A, H\n");
	pc++;
	break;
      case 0x8E:
	printf("ADC A, (HL)\n");
	pc++;
	break;
      case 0x93:
	printf("SUB A, E\n");
	pc++;
	break;
      case 0x99:
	printf("SBC A, C\n");
	pc++;
	break;
      case 0x9F:
	printf("SBC A, A\n");
	pc++;
	break;
      case 0xA0:
	printf("AND A, B\n");
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
      case 0xAE:
	printf("XOR A, (HL)\n");
	pc++;
	break;
      case 0xAF:
        printf("XOR A\n");
        pc++;
        break;
      case 0xB0:
	printf("OR A, B\n");
	pc++;
	break;
      case 0xB1:
	printf("OR A, C\n");
	pc++;
	break;
      case 0xB3:
	printf("OR A, E\n");
	pc++;
	break;
      case 0xB9:
	printf("CP A, C\n");
	pc++;
	break;
      case 0xBA:
	printf("CP A, D\n");
	pc++;
	break;
      case 0xBB:
	printf("CP A, E\n");
	pc++;
	break;
      case 0xBF:
	printf("CP A, A\n");
	pc++;
	break;
      case 0xC0:
	printf("RET NZ\n");
	pc++;
	break;
      case 0xC1:
	printf("POP BC\n");
	pc++;
	break;
      case 0xC3:
        printf("JMP $%02X%02X\n",rom[pc + 2], rom[pc + 1]);
        // pc = ((uint16_t)rom[pc + 2] << 8) | (uint16_t)rom[pc + 1];
	pc++;
	pc++;
	pc++;
        break;
      case 0xC5:
	printf("PUSH BC\n");
	pc++;
	break;
      case 0xC7:
	printf("RST $00\n");
	pc++;
	break;
      case 0xC8:
	printf("RET Z\n");
	pc++;
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
      case 0xCC:
	printf("CALL Z, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
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
      case 0xCE:
	printf("ADC A, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xD0:
	printf("RET NC\n");
	pc++;
	break;
      case 0xD1:
	printf("POP DE\n");
	pc++;
	break;
      case 0xD2:
	printf("JP NC, $%02X%02X\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0xD5:
	printf("PUSH DE\n");
	pc++;
	break;
      case 0xD9:
	printf("RETI\n");
	pc++;
	break;
      case 0xDD:
	printf(" - \n");
	pc++;
	break;
      case 0xE0:
	printf("LDH $%02X, A\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xE1:
	printf("POP HL\n");
	pc++;
	break;
      case 0xE2:
	printf("LDH (C), A\n");
	pc++;
	break;
      case 0xE5:
	printf("PUSH HL\n");
	pc++;
	break;
      case 0xE6:
	printf("AND A, %02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xE9:
	printf("JP HL\n");
	pc++;
	break;
      case 0xEA:
	printf("LD ($%02X%02X), A\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0xEF:
	printf("RST $28\n");
	pc++;
	break;
      case 0xF0:
	printf("LDH A, $%02X\n", rom[pc + 1]);
	pc++;
	pc++;
	break;
      case 0xF1:
	printf("POP AF\n");
	pc++;
	break;
      case 0xF3:
	printf("DI\n");
	pc++;
	break;
      case 0xF5:
	printf("PUSH AF\n");
	pc++;
	break;
      case 0xF7:
	printf("RST $30\n");
	pc++;
	break;
      case 0xFA:
	printf("LD A, ($%02X%02X)\n", rom[pc + 2], rom[pc + 1]);
	pc++;
	pc++;
	pc++;
	break;
      case 0xFB:
	printf("EI\n");
	pc++;
	break;
      case 0xFC:
	printf(" - \n");
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
