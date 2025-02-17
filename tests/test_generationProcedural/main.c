#include "fct.h"


/* Test de la génération procédurale du relief du sol */

int main() {

    // Initialisation aléatoire
    srand(time(NULL));
    int seed = rand() % 2147483646;
    int * table = creerTableSeed(&seed);

    struct Elem drapeau;
    strcpy(drapeau.nom, "drapeau");
    drapeau.nb_frame = 7;
    drapeau.height = 5;
    drapeau.width = 1;

    WINDOW * jeu;
    WINDOW * tmp;

    initscr();  // Met la console en mode "ncurses"
    curs_set(0);  // Cache le curseur dans la console
    noecho();
    nodelay(stdscr, true);

    // Setup dimension fenêtre tmp
    int height_fenetre_tmp = 6;
    int width_fenetre_tmp = COLS;
    int startx_fenetre_tmp = 0;
    int starty_fenetre_tmp = 0;

    // Setup dimension fenêtre de jeu
    int height_fenetre_jeu = 30;
    int width_fenetre_jeu = COLS;  // COLS renvoie la largeur de la console en mode "ncurses"
    int startx_fenetre_jeu = 0;
    int starty_fenetre_jeu = starty_fenetre_tmp + height_fenetre_tmp;

    // Creer fenetre de jeu
    jeu = newwin(height_fenetre_jeu + 2, width_fenetre_jeu, starty_fenetre_jeu, startx_fenetre_jeu);
	wborder(jeu, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(jeu);

    // Creer fenetre tmp
    tmp = newwin(height_fenetre_tmp, width_fenetre_tmp, starty_fenetre_tmp, startx_fenetre_tmp);
    afficherTmp(tmp, 0, 0, 0, table, seed);

    // Setup dimension carte
    int height_carte = height_fenetre_jeu / TY;
    int width_carte = (width_fenetre_jeu - 2) / TX;

    // Création d'un niveau vide
    struct Map * niv = creerMap(height_carte, width_carte);

    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return EXIT_FAILURE;
    }

    // Génération de la carte
    int X, Y;
    for (int x = 0; x < width_carte; x++) {
        X = x;
        Y = iterationMap(niv, X, 0, table, &seed, 1);  // 1. Mode de génération via perlin | 0. Mode de génération simple
    }

    afficherMap(jeu, niv);

    int dMax = 0;

    int pressed;
    while ((pressed = wgetch(jeu)) != 'k') {  // Boucle jusqu'à que "k" soit pressé
        if (pressed == 'd') {
            X++;
            dMax++;
            Y = avancerMap(niv, X, dMax, table, &seed, 1);
            afficherMap(jeu, niv);
            afficherTmp(tmp, X, Y, dMax, table, seed);
            affichageElem(jeu, drapeau, dMax);
        }
        if (X % 150 == 0) {
            drapeau.x = X;
            drapeau.y = niv->height - Y;
        }
    }

    // Libération de la mémoire : niveau et table aléatoire
    libMemMap(niv);
    free(table);
    table = NULL;

    endwin();  // Sort la console du mode "ncurses"

    return 0;
}