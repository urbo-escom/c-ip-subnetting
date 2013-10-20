CC=gcc
CFLAGS=-Wall
OS_ESPECIFIC_CFLAGS=
LFLAGS=
OS_ESPECIFIC_LFLAGS=

debug=@echo debug-on-command:

# Windows especific commands
ifdef SystemRoot
	EXT=.exe
	RM=del /q $(1) 2>NUL
	fixpath=$(subst /,\,$(1))
else
# Linux especific commands
ifeq ($(shell uname), Linux)
	EXT=
	RM=rm -rf $(1)
	fixpath=$(1)
endif
endif

COMMON_FOLDERS:=network gtk
SRC_FOLDERS:=client server $(COMMON_FOLDERS)

SRC:=$(foreach folder,$(SRC_FOLDERS),$(wildcard src/$(folder)/*.c))

OBJ:=$(SRC:%.c=%.o)
COMMON_OBJ:=$(foreach folder,$(COMMON_FOLDERS),$(wildcard src/$(folder)/*.o))

BIN:=$(foreach file,client server,bin/$(file)$(EXT))

all: $(BIN)

$(BIN): $(OBJ)
	$(debug) $(CC) -o $(call fixpath,$@) \
	$(call fixpath,\
		$(filter $(subst $(EXT),,\
			$(subst bin/,src/,$@))/%.o,$(OBJ))) \
	$(call fixpath,$(COMMON_OBJ)) \
	$(LFLAGS) $(OS_ESPECIFIC_LFLAGS)

%.o: %.c
	$(debug) $(CC) \
	$(CFLAGS) $(OS_ESPECIFIC_CFLAGS) \
	-c $< -o $@

.PHONEY: clean
clean:
	$(debug) $(call RM,$(call fixpath,$(OBJ)))
	$(debug) $(call RM,$(call fixpath,$(filter-out %.md,$(wildcard bin/*))))


