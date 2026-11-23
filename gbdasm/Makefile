CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude -I../common/include

SRCS    = src/gbdasm.c ../common/src/validpath.c ../common/src/romloader.c
OBJS    = $(SRCS:.c=.o)
TARGET  = build/gbdasm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
