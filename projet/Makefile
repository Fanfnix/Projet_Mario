CC = gcc
CFLAGS = -g -Wall -Iinclude/
LDFLAGS = -g
LIBS = -lm
SRCDIR = src
EXEC = result.out

CFLAGS += $(shell pkg-config --cflags ncurses sdl2 SDL2_mixer)
LIBS += $(shell pkg-config --libs ncurses sdl2 SDL2_mixer)

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))

all: $(EXEC)

$(EXEC): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(LDFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	rm -rf $(SRCDIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
