#include "../include/menu.h"


WINDOW * creerWindowLogo() {
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;
    WINDOW *logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    return logo;
}


WINDOW * creerWindowControle() {
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;
    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = COLS - width_fenetre_controle - 2;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;
    WINDOW *controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    return controle;
}


WINDOW * creerWindowMenu() {
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    height_fenetre_menu = LINES - 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = 2;
    starty_fenetre_menu = 1;
    WINDOW *menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);
    return menu;
}


WINDOW * creerWindowChoix() {
    int height_fenetre_choix, width_fenetre_choix, startx_fenetre_choix, starty_fenetre_choix;
    height_fenetre_choix = LINES - 2;
    width_fenetre_choix = COLS - WIDTH_MENU - 7;
    startx_fenetre_choix = WIDTH_MENU + 6;
    starty_fenetre_choix = 1;
    WINDOW *choix = newwin(height_fenetre_choix, width_fenetre_choix, starty_fenetre_choix, startx_fenetre_choix);
    return choix;
}


WINDOW * creerWindowEloise() {
    int height_fenetre_eloise, width_fenetre_eloise, startx_fenetre_eloise, starty_fenetre_eloise;
    height_fenetre_eloise = HEIGHT_ELOISE;
    width_fenetre_eloise = WIDTH_ELOISE;
    startx_fenetre_eloise = (COLS - width_fenetre_eloise) / 2;
    starty_fenetre_eloise = (LINES - height_fenetre_eloise) / 2;
    WINDOW *eloise = newwin(height_fenetre_eloise, width_fenetre_eloise, starty_fenetre_eloise, startx_fenetre_eloise);
    return eloise;
}


void affichageEloise(WINDOW * eloise) {
    wborder(eloise, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(eloise);
}


void affichageRetromario(WINDOW * logo) {
    char chemin[] = "../design/retromario/retromario1.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file != NULL) {
        wattron(logo, A_BOLD);
        for (int y = 0; y < HEIGHT_LOGO; y++) {
            char tmp[WIDTH_LOGO+1];
            fgets(tmp, WIDTH_LOGO+1, file);
            for (int i = 0; i < strlen(tmp); i++) {
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(logo, y+1, 1, tmp);
        }
        wattroff(logo, A_BOLD);
        wrefresh(logo);
        fclose(file);
    }
}

void affichageControle(WINDOW * controle) {
    wborder(controle, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle, 2, 3, "> SAUTER / ^ : Z");
    mvwaddstr(controle, 4, 3, "> GAUCHE / v : Q");
    mvwaddstr(controle, 6, 3, "> DROITE : D");
    mvwaddstr(controle, 8, 3, "> PAUSE :  P");

    wrefresh(controle);
}

void affichageGenerale(WINDOW * logo, WINDOW * controle, WINDOW * eloise) {
    affichageRetromario(logo);
    affichageControle(controle);
    affichageEloise(eloise);
}

void affichageMenuPrincipal(WINDOW * menu, int choix) {
    wclear(menu);
    const int taille_menu = 4;
    char liste_menu[4][100] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu);
    wattron(menu, A_BOLD);
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(menu, A_BOLD);
    char affiche[255];
    for (int i = 0; i < taille_menu; i++) {
        if (i == choix) {
            sprintf(affiche, "> %s <", liste_menu[i]);
            wattron(menu, A_BOLD);
        } else sprintf(affiche, "  %s  ", liste_menu[i]);
        mvwaddstr(menu, 4*(i+1), (WIDTH_MENU-(strlen(liste_menu[i])+4)+1)/2, affiche);
        if (i == choix) wattroff(menu, A_BOLD);
    }
    wrefresh(menu);
}

void actionMenuPrincipal(WINDOW * menu, int * id) {
    char pressed;
    affichageMenuPrincipal(menu, *id);
    while ((pressed = wgetch(menu)) != '\n') {
        if (pressed == 'z') (*id)--;
        else if (pressed == 's') (*id)++;
        if (*id < 0) *id = 3;
        if (*id > 3) *id = 0;
        affichageMenuPrincipal(menu, *id);
    }
}


struct Score * recupScore(char * str) {
    struct Score * struct_score = malloc(sizeof(struct Score));
    if (struct_score == NULL) return NULL;

    char * elem[3] = {NULL};
    elem[0] = strtok(str, ", \n");
    for (int i = 1; i < 3; i++) {
        elem[i] = strtok(NULL, ", \n");
    }
    struct_score->id = atoi(elem[0]);
    strncpy(struct_score->pseudo, elem[1], sizeof(struct_score->pseudo) - 1);
    struct_score->pseudo[sizeof(struct_score->pseudo) - 1] = '\0';
    struct_score->score = atoi(elem[2]);

    return struct_score;
}


struct Score ** recupHiscores() {
    struct Score ** liste_score = malloc(10 * sizeof(struct Score*));
    for (int i = 0; i < 10; i++) liste_score[i] = NULL;

    char chemin[] = "data/hi_scores.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file == NULL) {
        free(liste_score);
        return NULL;
    }
    char line[50];
    for (int i = 0; i < 10; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        liste_score[i] = recupScore(line);
    }
    fclose(file);
    return liste_score;
}


void affichageHiscores(WINDOW * win, struct Score ** liste_score, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win);
    wattron(win, A_BOLD);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win, 1, (COLS - WIDTH_MENU - 37) / 2, " _____ _____ _____ _____ _____ _____ ");
    mvwaddstr(win, 2, (COLS - WIDTH_MENU - 37) / 2, "|   __|     |     | __  |   __|   __|");
    mvwaddstr(win, 3, (COLS - WIDTH_MENU - 37) / 2, "|__   |   --|  |  |    -|   __|__   |");
    mvwaddstr(win, 4, (COLS - WIDTH_MENU - 37) / 2, "|_____|_____|_____|__|__|_____|_____|");
    wattroff(win, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) sprintf(text, "  >>> %d. %s - %d", i+1, liste_score[i]->pseudo, liste_score[i]->score);
        else sprintf(text, "  >>> null");
        WINDOW * score = derwin(win, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
        if (i == choisi) wattron(score, A_BOLD);
        mvwaddstr(score, 2, 2, text);
        if (i == choisi) wattroff(score, A_BOLD);
    }
    mvwaddstr(win, 50, 2, " 'x' to delete a score");
    wrefresh(win);
}


void actionHiscores(WINDOW * win, struct Score ** liste_score, int * id) {
    char pressed;
    affichageHiscores(win, liste_score, *id);
    while ((pressed = wgetch(win)) != 'k') {
        if (pressed == 'z') (*id)--;
        else if (pressed == 's') (*id)++;
        else if (pressed == 'x') continue;  // Supprimer le score
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageHiscores(win, liste_score, *id);
    }
    wclear(win);
    wrefresh(win);
}


void libererHiscores(struct Score ** liste_score) {
    if (liste_score == NULL) return;
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) {
            free(liste_score[i]);
            liste_score[i] = NULL;
        }
    }
    free(liste_score);
    liste_score = NULL;
}