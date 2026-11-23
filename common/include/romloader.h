#ifndef ROAMLOADER_H
#define ROAMLOADER_H

#include <stddef.h>
#include <stdint.h>

uint8_t *loadrom(const char *path, size_t *out_size);

#endif
