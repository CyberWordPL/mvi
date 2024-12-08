override MAKEFLAGS += -rR

BINFILE = mvi

CC := gcc
CFLAGS := \
	-Wall \
	-Wextra \
	-pedantic
CPPFLAGS := \
	-MMD \
	-MP

CFILES = $(shell cd src && find . -name "*.c")
OBJFILES = $(addprefix obj/,$(CFILES:.c=.o))
DEPS = $(addprefix obj/,$(CFILES:.c=.d))


$(BINFILE): $(OBJFILES)
	$(CC) -o $(BINFILE) $(OBJFILES)

-include $(DEPS)

.PHONY: obj/%.o
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
