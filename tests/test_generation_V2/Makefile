CC=cc
CFLAGS=-W -Wall
INC=-I include
SRC=src/
EXEC=main

all: $(EXEC)

main: main.c main.o
	$(CC) $(INC) $(CFLAGS) -o $(SRC)$@ $(SRC)$^ -lncurses -lm

$(SRC)%.o: $(SRC)%.c
	$(CC) $(INC) $(CFLAGS) $(INC) -o $(SRC)$@ -c $(SRC)$< -lncurses -lm

clean:
	rm -rf *.o