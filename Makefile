CC=gcc
CFLAGS=-Wall

CFLAGS += -Iinclude/

SRC := $(shell find . -name *.c)
OBJ := $(SRC:%.c=%.o)

BIN := client server
compile: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o bin/$@ $(shell find src/$@ -name *.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@find . -name *.o | xargs -L 1 rm -f
	@rm -rf bin/*

