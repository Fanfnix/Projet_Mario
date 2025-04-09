#include "../include/menu.h"


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
            mvwaddstr_perso(logo, y+1, 1, tmp);
        }
        wattroff(logo, A_BOLD);
        wrefresh_perso(logo);
        fclose(file);
    }
}

void affichageControle(WINDOW * controle) {
    wborder_perso(controle, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr_perso(controle, 2, 3, "> SAUTER / ^ : Z");
    mvwaddstr_perso(controle, 4, 3, "> GAUCHE / v : Q");
    mvwaddstr_perso(controle, 6, 3, "> DROITE : D");
    mvwaddstr_perso(controle, 8, 3, "> PAUSE :  P");

    wrefresh_perso(controle);
}

void affichageMenuPrincipal(WINDOW * menu, int choix) {
    const int taille_menu = 4;
    char liste_menu[4][255] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu);
    wborder_perso(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    char affiche[255];
    for (int i = 0; i < taille_menu; i++) {
        if (i == choix) {
            sprintf(affiche, "> %s <", liste_menu[i]);
            wattron(menu, A_BOLD);
        } else sprintf(affiche, "  %s  ", liste_menu[i]);
        mvwaddstr_perso(menu, 4*(i+1), (WIDTH_MENU-(strlen(liste_menu[i])+4)+1)/2, affiche);
        if (i == choix) wattroff(menu, A_BOLD);
    }
    wrefresh_perso(menu);
}

int actionMenuPrincipal(WINDOW * menu) {
    int id = 0;
    char pressed;
    do {
        if (pressed == 'z') id--;
        else if (pressed == 's') id++;
        else if (pressed == '\n') break;
        if (id < 0) id = 3;
        if (id > 3) id = 0;
        affichageMenuPrincipal(menu, id);
    } while ((pressed = wgetch(menu)) != 'k');
    return id;
}


struct Score * recupScore(char * str) {
    struct Score * struct_score = malloc(sizeof(struct Score));
    if (struct_score == NULL) return NULL;

    char * elem[3];
    elem[0] = strtok(str, ", \n");
    for (int i = 1; i < 3; i++) {
        elem[i] = strtok(NULL, ", \n");
    }
    struct_score->id = atoi(elem[0]);
    strcpy(struct_score->pseudo, elem[1]);
    struct_score->score = atoi(elem[2]);

    return struct_score;
}


struct Score ** recupHiscores() {
    struct Score ** liste_score = malloc(10 * sizeof(struct Score*));
    for (int i = 0; i < 10; i++) liste_score[i] = NULL;

    char chemin[] = "data/hi_scores.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    char * line;
    for (int i = 0; i < 10; i++) {
        line = fgets(line, 50, file);
        if (line == NULL) break;
        else {
            liste_score[i] = recupScore(line);
        }
    }

    fclose(file);

    return liste_score;
}


void affichageHiscores(WINDOW * win, struct Score ** liste_score) {
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) {
            sprintf(text, "ID = %d | PSEUDO = %s | SCORE = %d\n", liste_score[i]->id, liste_score[i]->pseudo, liste_score[i]->score);
            mvwaddstr_perso(win, 2+i, 2, text);
        } else break;
    }
}