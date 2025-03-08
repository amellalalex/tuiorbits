SRC=main.c log.c

all:
	$(CC) -std=c99 -Iinclude -I. $(SRC) -lncurses -o tuiorbit
