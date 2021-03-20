CFLAGS ?= -O2
WERROR ?= -Werror
CFLAGS += \
	$(WERROR) \
	-Wall \
	-Wcast-qual \
	-Wextra \
	-Wextra-semi-stmt \
	-Wformat=2 \
	-Wpedantic \
	-Wpointer-arith \
	-Wshadow \
	-Wsign-compare \
	-Wsign-conversion \
	-Wstack-protector \
	-Wstrict-aliasing=2 \
	-Wunreachable-code-break \
	-Wwrite-strings \
	-fno-common

all: seq

clean:
	rm -f seq
