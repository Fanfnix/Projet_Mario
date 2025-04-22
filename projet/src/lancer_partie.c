#include "../include/header.h"

void lancerPartie(){
    
    // Initialisation aléatoire
    srand(time(NULL));
    int min_seed = 16807;
    int max_seed = 2147483646;
    int seed = ((rand() % (max_seed - min_seed + 1)) + min_seed) / VARIANCE * VARIANCE;  // Le "/ VARIANCE * VARIANCE" est pour s'assurer que la premiere generation sera à Y_MIN pour le raccordement
    int * table = creerTableSeed();

    // Creation des fenetre
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
        if (i < 3) genererChunk(niv, i, NULL, NULL);
        else genererChunk(niv, i, table, &seed);
    }

    nodelay(jeu, true);

    double begin, timediff, fps, supp;
    char txt_fps[255] = "\0";
    while (wgetch(jeu) != 'k') {
        begin = (double)clock() / CLOCKS_PER_SEC;
        // CODE >>>

        afficherMap_simp(mini_jeu, niv, height_gen, width_gen);
        wrefresh(mini_jeu);
        afficherMap(jeu, niv, height_carte, width_carte);

        // <<< CODE
        timediff = ((double)clock()) / CLOCKS_PER_SEC - begin;
        supp = 1.0f / 60.0f - timediff;
        if (supp > 0) usleep(1000000 * supp);
        fps = 1.0f / (timediff + supp);
        snprintf(txt_fps, 254, "FPS : %.1lf", fps);
        mvwaddstr(jeu, 1, 1, txt_fps);
        wrefresh(jeu);
    }

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