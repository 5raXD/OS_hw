CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -pedantic
TARGET = hw1shell
SRC = hw1shell.c
HDR = hw1shell.h
OBJ = hw1shell.os
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
$(OBJ): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c -o $@ $(SRC)
clean:
	rm -f $(TARGET) $(OBJ)
rebuild: clean all
.PHONY: all clean rebuild
