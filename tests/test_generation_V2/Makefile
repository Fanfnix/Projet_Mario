CC = cc
CFLAGS = -Wall -Iinclude/
LDFLAGS =
LIBS = -lm
SRCDIR = src
EXEC = genere
OS = $(shell uname -s)

CFLAGS += $(shell pkg-config --cflags ncurses)
LIBS += $(shell pkg-config --libs ncurses)

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst %.c, %.o, $(SRCFILES))

all: $(EXEC)

genere: $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	rm -rf $(SRCDIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
