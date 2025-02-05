#include "fct.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

/* Test de la génération procédurale du relief du sol */

int main() {

    // Initialisation aléatoire
    srand(time(NULL));
    int seed = rand() % 2147483646;
    int * table = creerTableSeed(&seed);

    initscr();  // Met la console en mode "ncurses"

    // Setup dimension carte
    int L = 16;
    int l = COLS;  // COLS renvoie la largeur de la console en mode "ncurses"

    // Création d'un niveau vide
    struct Map * niv = creerMap(L, l);

    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }

    // Génération de la carte
    for (int x = 0; x < l; x++) {
        iterationMap(niv, x, table, &seed, 1);  // 1. Mode de génération via perlin | 0. Mode de génération simple
    }

    afficherMap(niv);

    while (getch() == -1);  // Boucle jusqu'à qu'une touche soit pressé

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    endwin();  // Sort la console du mode "ncurses"

    return 0;
}