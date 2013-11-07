CC=gcc
override CFLAGS+= -Wall $(shell pkg-config --cflags gtk+-3.0)
override OS_ESPECIFIC_CFLAGS+=
override LFLAGS+= $(shell pkg-config --libs gtk+-3.0)
override OS_ESPECIFIC_LFLAGS+=

# Windows especific commands
ifdef SystemRoot
	EXT=.exe
	RM=del /q $(1) 2>NUL
	fixpath=$(strip $(subst /,\,$(1)))
override OS_ESPECIFIC_CFLAGS+=
override OS_ESPECIFIC_LFLAGS+=-lws2_32
else
# Linux especific commands
ifeq ($(shell uname), Linux)
	EXT=
	RM=rm -rf $(1)
	fixpath=$(strip $(1))
endif
endif

SRC_FOLDERS:=client server network debug subnetting exchange calc

# Inlude libraries
override CFLAGS+=$(foreach folder,$(SRC_FOLDERS), -I./src/$(folder))

HDR:=$(foreach folder,$(SRC_FOLDERS),$(wildcard src/$(folder)/*.h))
SRC:=$(foreach folder,$(SRC_FOLDERS),$(wildcard src/$(folder)/*.c))

OBJ:=$(SRC:%.c=%.o)

ALL_CFLAGS:=$(CFLAGS) $(OS_ESPECIFIC_CFLAGS)
ALL_LFLAGS:=$(LFLAGS) $(OS_ESPECIFIC_LFLAGS)

BIN:=$(foreach file,client server,bin/$(file)$(EXT))

.PHONY: all test clean
all: $(BIN) test

bin/client$(EXT): $(HDR) $(OBJ)
	$(CC) -o $@ \
		src/network/*.o src/client/*.o \
		$(ALL_LFLAGS)

bin/server$(EXT): $(HDR) $(OBJ)
	$(CC) -o $@ \
		src/network/*.o src/subnetting/*.o \
		src/server/*.o src/calc/*.o \
		$(ALL_LFLAGS)

TEST_SRC:=$(wildcard test/*.c)
TEST_BIN:=$(TEST_SRC:%.c=%$(EXT))
test: $(TEST_BIN)

test/%$(EXT): test/%.c $(OBJ)
	$(call fixpath,$(CC) $(ALL_CFLAGS) -o $@ \
		$< $(filter-out %main.o,$(OBJ)) $(ALL_LFLAGS))

%.o: %.c
	$(call fixpath,$(CC) $(ALL_CFLAGS) -c $< -o $@)

clean:
	$(call RM,$(call fixpath,$(OBJ)))
	$(call RM,$(call fixpath,$(filter-out %.md,$(wildcard bin/*))))
	$(call RM,$(call fixpath,$(filter-out %.c,$(wildcard test/*))))


