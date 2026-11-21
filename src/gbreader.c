#include <stdio.h>

#include "validpath.h"

void puse() {
	printf("Use gbrd /path/to/file\n");
}

int main(int argc, char *argv[]) {

	if (argc <= 1) {

		puse();

		return 1;

	} else if (argc > 2) {
		
		printf("Too many arguments\n");
		puse();

		return 1;

	}else {

		//printf("Path %s is %s\n", argv[1], isValidPath(argv[1]) ? "Valid" : "Not Valid");
		
		if ( isValidPath(argv[1]) ){

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

				if (count == 0) {
					printf("OFFSET\t\tHEX\t\t\t\t\t\t        ASCII\n");
					printf("--------------------------------------------------------------------------------\n");
					printf("0x%08X\t", count);
				}
				
				printf("%02X ", (unsigned int) ch);

				if (ch >= 32 && ch <= 126) {

					asciiBuffer[asciiCounter++] = (unsigned char) ch;

				} else {
				
					asciiBuffer[asciiCounter++] = '.';

				}

				if (++count % 16 == 0) {
					asciiBuffer[16] = '\0';
					printf("\t%s\n",asciiBuffer);
					printf("0x%08X\t",count);
					asciiCounter = 0;
				}

			}

			fclose(fp);

			return 0;

		} else {
		
			return 1;

		}

	}

}
