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

    WINDOW * jeu;

    initscr();  // Met la console en mode "ncurses"

    // Setup dimension fenêtre de jeu
    int height_fenetre = 32;
    int width_fenetre = COLS;
    int startx_fenetre = 0;
    int starty_fenetre = (LINES - height_fenetre) / 2;

    // Creer fentre de jeu
    jeu = newwin(height_fenetre, width_fenetre, starty_fenetre, startx_fenetre);
	wborder(jeu, ' ', ' ', '-', '-', '+', '+', '+', '+');
	wrefresh(jeu);

    // Setup dimension carte
    int height_carte = height_fenetre / TY;
    int width_carte = width_fenetre / TX;  // COLS renvoie la largeur de la console en mode "ncurses"

    // Création d'un niveau vide
    struct Map * niv = creerMap(height_carte, width_carte);

    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }

    // Génération de la carte
    for (int x = 0; x < width_carte; x++) {
        iterationMap(niv, x, table, &seed, 1);  // 1. Mode de génération via perlin | 0. Mode de génération simple
    }

    afficherMap(jeu, niv);

    while (wgetch(jeu) == -1);  // Boucle jusqu'à qu'une touche soit pressé

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    endwin();  // Sort la console du mode "ncurses"

    return 0;
}