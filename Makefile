CC=gcc
CFLAGS=-Wall

CFLAGS += -Iinclude/ $(shell pkg-config --cflags gtk+-3.0)
LFLAGS += $(shell pkg-config --libs gtk+-3.0)

SRC := $(shell find . -name *.c)
OBJ := $(SRC:%.c=%.o)

BIN := client server
compile: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o bin/$@.bin $(shell find src/$@ -name *.o) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONEY: clean
clean:
	@find . -name *.o | xargs -L 1 rm -f
	@rm -rf bin/*.bin

