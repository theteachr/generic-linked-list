CC = gcc
CFLAGS = -g

main: src/main.c
	$(CC) $(CFLAGS) -o $@ $<
