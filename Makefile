CC=gcc
override CFLAGS+= -Wall $(shell pkg-config --cflags gtk+-3.0)
override OS_ESPECIFIC_CFLAGS+=
override LFLAGS+= $(shell pkg-config --libs gtk+-3.0)
override OS_ESPECIFIC_LFLAGS+=

# Windows especific commands
ifdef SystemRoot
	EXT=.exe
	RM=del /q $(1) 2>NUL
	fixpath=$(subst /,\,$(1))
override OS_ESPECIFIC_CFLAGS+=
override OS_ESPECIFIC_LFLAGS+=-lws2_32
else
# Linux especific commands
ifeq ($(shell uname), Linux)
	EXT=
	RM=rm -rf $(1)
	fixpath=$(1)
endif
endif

COMMON_FOLDERS:=network gtk debug subnetting
SRC_FOLDERS:=client server $(COMMON_FOLDERS)

override CFLAGS+=$(foreach folder,$(COMMON_FOLDERS), -I./src/$(folder))

SRC:=$(foreach folder,$(SRC_FOLDERS),$(wildcard src/$(folder)/*.c))

OBJ:=$(SRC:%.c=%.o)
COMMON_OBJ:=\
	$(foreach folder,$(COMMON_FOLDERS),\
		$(filter src/$(folder)/%.o,$(OBJ)))

BIN:=$(foreach file,client server,bin/$(file)$(EXT))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(call fixpath,$@) \
	$(call fixpath,\
		$(filter $(subst $(EXT),,\
			$(subst bin/,src/,$@))/%.o,$(OBJ))) \
	$(call fixpath,$(COMMON_OBJ)) \
	$(LFLAGS) $(OS_ESPECIFIC_LFLAGS)

%.o: %.c
	$(CC) \
	$(CFLAGS) $(OS_ESPECIFIC_CFLAGS) \
	-c $< -o $@

.PHONY: clean
clean:
	$(call RM,$(call fixpath,$(OBJ)))
	$(call RM,$(call fixpath,$(filter-out %.md,$(wildcard bin/*))))


