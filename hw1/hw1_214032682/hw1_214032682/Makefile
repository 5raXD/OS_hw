CC = gcc
CFLAGS = -Wall -g
TARGET = hw1shell
SRCS = hw1shell.c
OBJS = $(SRCS:.c=.o)
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
.PHONY: all clean
# i wanted to use this or equvelent but after reading more about makefiles i realized that this ver is not good
# hw1shell: hw1shell.c
# 	gcc -g hw1shell.c -o hw1shell
# clean:
# 	\rm hw1shell
# all: hw1shel