.SECONDEXPANSION:
TARGETS := release debug 
.PHONY: $(TARGETS) all

export TERM ?= xterm-256color

all: release/bigshell debug/bigshell

compile_commands.json:
	bear -- $(MAKE) -B all

EXE := bigshell
SRCS := $(shell find src -type f -name '*.c')
OBJS := $(SRCS:src/%.c=%.o)

CFLAGS = -std=c99 -Wall -Werror=vla
release: CFLAGS += -O3 
debug: CFLAGS += -g -O0


release/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DNDEBUG -c $< -o $@

debug/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

release/bigshell: $(patsubst src/%.c,release/%.o,$(SRCS)) | release/
	$(CC) $(LDFLAGS) $^ -o $@

debug/bigshell: $(patsubst src/%.c,debug/%.o,$(SRCS)) | debug/
	$(CC) $(LDFLAGS) $^ -o $@

release/:
	mkdir -p release/

debug/:
	mkdir -p debug/

clean:
	rm -vr $(TARGETS)

%/:
	mkdir -vp $@
