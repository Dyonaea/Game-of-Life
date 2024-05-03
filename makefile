UNAME_S = $(shell uname -s)

CC = gcc
LDFLAGS = lib/SDL/src/sdl2.a
SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs lib game


libs:
	cd lib/SDL && cmake . && make


dirs:
	mkdir -p ./$(BIN)


run: all
	$(BIN)/game


game: $(OBJ)
	$(CC) -o $(BIN)/game $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
