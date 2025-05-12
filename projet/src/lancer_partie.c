#include "../include/header.h"

void lancerPartie() {

    int max_fps = 30;
    
    // Initialisation aléatoire
    srand(time(NULL));
    int min_seed = 16807;
    int max_seed = 2147483646;
    int seed = ((rand() % (max_seed - min_seed + 1)) + min_seed) / VARIANCE * VARIANCE;  // Le "/ VARIANCE * VARIANCE" est pour s'assurer que la premiere generation sera à Y_MIN pour le raccordement
    int * table = creerTableSeed();

    // Creation des fenetre
    WIN * tmp;
    WIN * jeu;
    WIN * mini_jeu;

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
    WINDOW * jeu_fenetre = newwin(height_fenetre_jeu + 2, width_fenetre_jeu, starty_fenetre_jeu, startx_fenetre_jeu);
    jeu = creerFenetre(jeu_fenetre, width_fenetre_jeu, height_fenetre_jeu);
    if (!jeu) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
	wborder(jeu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(jeu->fenetre);

    // Creer fenetre tmp
    WINDOW * tmp_fenetre = newwin(height_fenetre_tmp, width_fenetre_tmp, starty_fenetre_tmp, startx_fenetre_tmp);
    tmp = creerFenetre(tmp_fenetre, width_fenetre_tmp, height_fenetre_tmp);
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
    int nb_chunks = width_carte / DISTANCE + 2;

    // Setup dimension fenêtre mini_jeu
    int height_fenetre_mini_jeu = height_carte;
    int width_fenetre_mini_jeu = COLS;
    int startx_fenetre_mini_jeu = 0;
    int starty_fenetre_mini_jeu = starty_fenetre_jeu + height_fenetre_jeu + 2;

    WINDOW * mini_jeu_fenetre = newwin(height_fenetre_mini_jeu + 2, width_fenetre_mini_jeu, starty_fenetre_mini_jeu, startx_fenetre_mini_jeu);
    mini_jeu = creerFenetre(mini_jeu_fenetre, width_fenetre_mini_jeu, height_fenetre_mini_jeu);
    if (!mini_jeu) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }
	wborder(mini_jeu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(mini_jeu->fenetre);

    // Création d'un niveau vide
    struct Map * niv = creerMap(height_carte, nb_chunks);
    creerMario(1.0, 3);
    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return;
    }

    // Ajout de la génération de base
    struct Chunk * newChunk;
    for (int i = 0; i < nb_chunks; i++) {
        if (i < 3) newChunk = genererChunk(niv, i, NULL, NULL);
        else newChunk = genererChunk(niv, i, table, &seed);

        if (newChunk == NULL) {
            endwin();
            printf("ERR [main] : newChunk == NULL\n");
            return;
        }

        struct Chunk * tmp_first = niv->p_chunk;
        if (niv->p_chunk == NULL) {
            niv->p_chunk = newChunk;
            endwin();
            printf("== DEBUT GENERATION ==\n");
            printf("INFO [main][tmp_first == NULL] : tmp_first = %p / niv->p_chunk = %p\n", tmp_first, niv->p_chunk);
        }
        else {
            while (tmp_first->suivant != NULL) tmp_first = tmp_first->suivant;
            endwin();
            printf("INFO [main][tmp_first != NULL] : tmp_first = %p / tmp_first->suivant = %p\n", tmp_first, tmp_first->suivant);
            if (newChunk != NULL) tmp_first->suivant = newChunk;
        }
    }
    initMario(perso, niv, jeu);
    nodelay(jeu->fenetre, true);

    clock_t begin, end;
    float fps, timediff, supp;
    int nb_frames = 0;
    int tot_sec = 0;
    char txt_fps[255] = "\0";

    int pressed;

    while ((pressed = wgetch(jeu->fenetre)) != 107) {
        begin = clock();
        // CODE >>>

        switch (pressed) {
            case 100: avancerMapChunk(niv, table, &seed); break;
        }

   
        // afficherMap_simp(mini_jeu, niv);
        afficherMap(jeu, niv);
        affichageMario(jeu, perso);

        // <<< CODE
        end = clock();
        timediff = (float)(end - begin) / CLOCKS_PER_SEC;
        supp = (1.0f / max_fps) - timediff;
        if (supp > 0.0f) usleep(1000000 * supp);
        fps = 1.0f / (timediff + supp);
        nb_frames++;
        if (nb_frames >= max_fps+1) {
            nb_frames = 0;
            tot_sec++;
        }
        txt_fps[0] = '\0';
        snprintf(txt_fps, 254, "FPS : %.1lf | NB_FRAMES : %d | TOT_SEC : %d", fps, nb_frames, tot_sec);
        mvwaddstr(jeu->fenetre, 1, 1, txt_fps);
        wrefresh(jeu->fenetre);
    }

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    wclear(jeu->fenetre);
    wrefresh(jeu->fenetre);
    delwin(jeu->fenetre);
    
    wclear(tmp->fenetre);
    wrefresh(tmp->fenetre);
    delwin(tmp->fenetre);
    
    wclear(mini_jeu->fenetre);
    wrefresh(mini_jeu->fenetre);
    delwin(mini_jeu->fenetre);
}