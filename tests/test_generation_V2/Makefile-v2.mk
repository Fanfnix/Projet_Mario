CC = cc
CFLAGS = -Wall -Iinclude/
LDFLAGS =
LIBS = -lm
SRCDIR = src
EXEC = main

CFLAGS += $(shell pkg-config --cflags ncurses)
LIBS += $(shell pkg-config --libs ncurses)

all: $(EXEC)

main: $(SRCDIR)/fct.o $(SRCDIR)/genererChunk.o $(SRCDIR)/main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	rm -rf $(SRCDIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
