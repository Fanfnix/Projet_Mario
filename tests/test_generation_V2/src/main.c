#include "../include/header.h"


/* Test de la génération procédurale du relief du sol */

int main() {

    // Initialisation aléatoire
    srand(time(NULL));
    int seed = (16807 + rand() % (2147483646 - 16807)) / VARIANCE * VARIANCE;
    int * table = creerTableSeed();

    WINDOW * jeu;
    WINDOW * tmp;

    #if __linux__

    initscr();  // Met la console en mode "ncurses"
    curs_set(0);  // Cache le curseur dans la console
    noecho();
    nodelay(stdscr, true);

    #endif

    // Setup dimension fenêtre tmp
    int height_fenetre_tmp = 6;
    int width_fenetre_tmp = 150;  // COLS renvoie la largeur de la console en mode "ncurses"
    int startx_fenetre_tmp = 0;
    int starty_fenetre_tmp = 0;

    // Setup dimension fenêtre de jeu
    int height_fenetre_jeu = 30;
    int width_fenetre_jeu = 150;
    int startx_fenetre_jeu = 0;
    int starty_fenetre_jeu = starty_fenetre_tmp + height_fenetre_tmp;

    // Creer fenetre de jeu
    jeu = newwin_perso(height_fenetre_jeu + 2, width_fenetre_jeu, starty_fenetre_jeu, startx_fenetre_jeu);
    if (!jeu) {
        #if __linux__
        endwin();  // Sort la console du mode "ncurses"
        #endif
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }
	wborder_perso(jeu, '|', '|', '-', '-', '+', '+', '+', '+');
    #if __linux__
	wrefresh_perso(jeu);
    #endif

    // Creer fenetre tmp
    tmp = newwin_perso(height_fenetre_tmp, width_fenetre_tmp, starty_fenetre_tmp, startx_fenetre_tmp);
    if (!tmp) {
        #if __linux__
        endwin();  // Sort la console du mode "ncurses"
        #endif
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }
    afficherTmp(tmp, 0, 0, 0, table, seed);

    // Setup dimension carte
    int height_carte = height_fenetre_jeu / TY;
    int width_carte = (width_fenetre_jeu - 2) / TX;

    // Setup création
    int nb_chunk = width_carte / DISTANCE + 2;
    int height_gen = height_carte;
    int width_gen = nb_chunk * DISTANCE;

    // Création d'un niveau vide
    struct Map * niv = creerMap(height_gen, width_gen);

    // Vérification de la création du niveau
    if (!niv) {
        #if __linux__
        endwin();  // Sort la console du mode "ncurses"
        #endif
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }

    // Ajout de la génération de base
    for (int i = 0; i < nb_chunk; i++) {
        int tmp_seed = 0;
        if (i < 3) genererChunk(niv, i, table, &tmp_seed);
        else genererChunk(niv, i, table, &seed);
    }

    // afficherMap_simp(jeu, niv, height_carte, width_carte);
    afficherMap(jeu, niv, height_carte, width_carte);

    #if __linux__
    while (wgetch(jeu) != 'k');
    #elif _WIN32
    if (kbhit()) while (getch() != 'k');
    #endif

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    #if __linux__
    endwin();  // Sort la console du mode "ncurses"
    #endif

    return 0;
}