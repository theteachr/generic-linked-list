CC = gcc
CFLAGS = -g -fsanitize=address

main: src/main.c
	$(CC) $(CFLAGS) -o $@ $<
