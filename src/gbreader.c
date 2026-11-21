#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "validpath.h"

void puse() {
	printf("Use gbrd /path/to/file\n");
  printf("-h to print only hexadecimal\n");
}

int main(int argc, char *argv[]) {

  bool just_hex = false;

	if (argc <= 1) {

		puse();

		return 1;

	} else if (argc > 3) {
		
		printf("Too many arguments\n");
		puse();

		return 1;

	}else {

		//printf("Path %s is %s\n", argv[1], isValidPath(argv[1]) ? "Valid" : "Not Valid");

		if ( isValidPath(argv[1]) ){

      if(argc > 2 && argv[2][0] == '-') {
        
        if ( strcmp(argv[2],"-h") == 0 || strcmp(argv[2],"-hex") == 0 ){
          just_hex = true;
        } else {
          puse();
        }

      }

			FILE *fp = fopen(argv[1], "rb");

			int ch;
			int count = 0;
			int asciiCounter = 0;
			char asciiBuffer[17];

			if (fp == NULL) {
				printf("Unable to open file %s", argv[1]);
				return 1;
			}

			while ( ( ch = fgetc(fp) ) != EOF ) {

				if (count == 0 && !just_hex) {
					printf("OFFSET\t\tHEX\t\t\t\t\t\t        ASCII\n");
					printf("--------------------------------------------------------------------------------\n");
					printf("0x%08X\t", count);
				}
				
        printf("%02X ", (unsigned int) ch);

				if (ch >= 32 && ch <= 126 && !just_hex) {

					asciiBuffer[asciiCounter++] = (unsigned char) ch;

				} else if (!just_hex) {
				
					asciiBuffer[asciiCounter++] = '.';

				}

				if (++count % 16 == 0) {
          if (!just_hex){
  					asciiBuffer[16] = '\0';
	  				printf("\t%s\n",asciiBuffer);
		  			printf("0x%08X\t",count);
			  		asciiCounter = 0;
          } else {
            printf("\n");
          }
				}

			}

			fclose(fp);

			return 0;

		} else {
		
			return 1;

		}

	}

}
