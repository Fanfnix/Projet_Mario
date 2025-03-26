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

$(SRCDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(SRCDIR)/fct.o: $(SRCDIR)/fct.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(SRCDIR)/genererChunk.o: $(SRCDIR)/genererChunk.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	rm -rf $(SRCDIR)/*.o

mrproper: clean
	rm -rf $(EXEC)
