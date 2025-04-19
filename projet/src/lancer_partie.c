#include "../include/header.h"

void lancerPartie(){
    
    // Initialisation aléatoire
    srand(time(NULL));
    int seed = (16807 + rand() % (2147483646 - 16807)) / VARIANCE * VARIANCE;
    int * table = creerTableSeed();

    WINDOW * tmp;
    WINDOW * jeu;
    WINDOW * mini_jeu;

    // Setup dimension fenêtre tmp
    int height_fenetre_tmp = 6;
    int width_fenetre_tmp = COLS;  // COLS renvoie la largeur de la console en mode "ncurses"
    int startx_fenetre_tmp = 0;
    int starty_fenetre_tmp = 0;

    // Setup dimension fenêtre de jeu
    int height_fenetre_jeu = 30;
    int width_fenetre_jeu = COLS;
    int startx_fenetre_jeu = 0;
    int starty_fenetre_jeu = starty_fenetre_tmp + height_fenetre_tmp;

    // Creer fenetre de jeu
    jeu = newwin(height_fenetre_jeu + 2, width_fenetre_jeu, starty_fenetre_jeu, startx_fenetre_jeu);
    if (!jeu) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
	wborder(jeu, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(jeu);

    // Creer fenetre tmp
    tmp = newwin(height_fenetre_tmp, width_fenetre_tmp, starty_fenetre_tmp, startx_fenetre_tmp);
    if (!tmp) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
    afficherTmp(tmp, 0, 0, 0, table, seed);

    // Setup dimension carte
    int height_carte = height_fenetre_jeu / TY;
    int width_carte = (width_fenetre_jeu - 2) / TX;

    // Setup création
    int nb_chunk = width_carte / DISTANCE + 2;
    int height_gen = height_carte;
    int width_gen = nb_chunk * DISTANCE;

    // Setup dimension fenêtre mini_jeu
    int height_fenetre_mini_jeu = height_gen;
    int width_fenetre_mini_jeu = COLS;
    int startx_fenetre_mini_jeu = 0;
    int starty_fenetre_mini_jeu = starty_fenetre_jeu + height_fenetre_jeu + 2;

    mini_jeu = newwin(height_fenetre_mini_jeu + 2, width_fenetre_mini_jeu, starty_fenetre_mini_jeu, startx_fenetre_mini_jeu);
    if (!mini_jeu) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
	wborder(mini_jeu, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(mini_jeu);

    // Création d'un niveau vide
    struct Map * niv = creerMap(height_gen, width_gen);

    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }

    // Ajout de la génération de base
    for (int i = 0; i < nb_chunk; i++) {
        int tmp_seed = 0;
        if (i < 3) genererChunk(niv, i, table, &tmp_seed);
        else genererChunk(niv, i, table, &seed);
    }

    afficherMap_simp(mini_jeu, niv, height_gen, width_gen);
    wrefresh(mini_jeu);
    afficherMap(jeu, niv, height_carte, width_carte);

    while (wgetch(jeu) != 'k');

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    wclear(jeu);
    wrefresh(jeu);
    delwin(jeu);
    
    wclear(tmp);
    wrefresh(tmp);
    delwin(tmp);
    
    wclear(mini_jeu);
    wrefresh(mini_jeu);
    delwin(mini_jeu);
}