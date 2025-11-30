CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/shell.c src/parser.c src/builtin.c src/jobs.c src/exec.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = hw1shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)