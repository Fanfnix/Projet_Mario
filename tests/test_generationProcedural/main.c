#include "fct.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int main() {
    srand(time(NULL));
    int seed = rand() % 2147483646;
    int * table = creerTableSeed(&seed);

    initscr();

    int L = 16;
    int l = COLS;
    struct Map * niv = creerMap(L, l);
    if (!niv) {
        endwin();
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }

    for (int x = 0; x < l; x++) {
        iterationMap(niv, x, table, &seed, 1); // 1. Mode de génération classique | 0. Mode de génération simple
    }
    afficherMap(niv);

    while (getch() == -1);

    libMemMap(niv);
    free(table);
    table = NULL;

    endwin();
    return 0;
}