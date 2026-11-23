#include "romloader.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

uint8_t *loadrom(const char *path, size_t *out_size) {

  if (!path || !out_size) {
    fprintf(stderr,"Error: Null pointer passed into loadrom.\n");
    return NULL;
  }

  struct stat st;

  if (stat(path, &st) != 0){

    perror("stat");
    return NULL;

  }

  if (st.st_size <= 0){

    fprintf(stderr, "Error: '%s' is empty or has an invalid size\n", path);
    return NULL;

  }

  size_t size = (size_t)st.st_size;
  uint8_t *buffer = malloc(size);

  if (!buffer) {
    
    perror("malloc error");
    return NULL;

  }

  FILE *fp = fopen(path, "rb");
  if (!fp) {
    perror("fopen");
    free(buffer);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, size, fp);

  if (fclose(fp) != 0){

    perror("fclose");
    free(buffer);
    return NULL;

  }

  if (bytes_read != size) {
    
    fprintf(stderr, "Error: Incomplete reading (%zu of %zu bytes).\n", bytes_read, size);
    free(buffer);
    return NULL;
  }

  *out_size = size;

  return buffer;

}
