CFLAGS ?= -O2
WERROR ?= -Werror
CFLAGS += \
	$(WERROR) \
	-Wall \
	-Wcast-qual \
	-Wextra \
	-Wformat=2 \
	-Wpedantic \
	-Wpointer-arith \
	-Wshadow \
	-Wsign-compare \
	-Wsign-conversion \
	-Wstack-protector \
	-Wstrict-aliasing=2 \
	-Wwrite-strings \
	-fno-common

all: seq

test: all
	./run-tests

clean:
	rm -f seq
