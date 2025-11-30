#   make          - Build hw1shell executable
#   make clean    - Remove executables
#   make rebuild  - Clean and rebuild

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2 -pedantic
TARGET = hw1shell
SRC = hw1shell.c
HDR = hw1shell.h
OBJ = hw1shell.o

all: $(TARGET)

# Link object file to create executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source file to object file
$(OBJ): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -c -o $@ $(SRC)

# Remove built files
clean:
	rm -f $(TARGET) $(OBJ)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild
