UNAME_S := $(shell uname -s)


CC := gcc
CFLAGS = -std=c11 -O3 -g -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Ilib/SDL/include
LDFLAGS = lib/SDL/build/libSDL2.a
SRC := $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ := $(SRC:.c=.o)
BIN := bin


.PHONY: all clean

all: dirs libs game

libs:
	cd lib/SDL && mkdir -p build && cd build && cmake ../../SDL && make .

dirs:
	mkdir -p $(BIN)

run: all
	$(BIN)/game

game: $(OBJ)
	$(CC) -o $(BIN)/game $^ $(LDFLAGS) -lm
	 

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm -rf $(BIN) $(OBJ) $(OBJ:.o=.d)