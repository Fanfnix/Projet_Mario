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
            mvwaddstr(logo, y+1, 1, tmp);
        }
        wattroff(logo, A_BOLD);
        wrefresh(logo);
        fclose(file);
    }
}

void affichageControle(WINDOW * controle) {
    wborder(controle, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle, 2, 3, "> SAUTER : Z");
    mvwaddstr(controle, 4, 3, "> GAUCHE : Q");
    mvwaddstr(controle, 6, 3, "> DROITE : D");
    mvwaddstr(controle, 8, 3, "> PAUSE :  P");

    wrefresh(controle);
}

void affichageMenuPrincipal(WINDOW * menu, int choix) {
    const int taille_menu = 4;
    char liste_menu[4][255] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu);
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
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
    char tmp_str[255]; strcpy(tmp_str, str);

    char * elem = strtok(tmp_str, ",");
    int i = 0;
    while (elem != NULL) {
        if (i == 0) struct_score->id = atoi(elem);
        if (i == 1) struct_score->pseudo = elem;
        if (i == 2) struct_score->score = atoi(elem);
        elem = strtok(NULL, ",");
        i++;
    }

    return struct_score;
}


struct Score ** recupHiscores() {
    char chemin[] = "data/hi_scores.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");

    char contenu[255] = "";
    char tmp[3];
    while (contenu[strlen(contenu)-1] != '\\') {
        fgets(tmp, 2, file);
        strcat(contenu, tmp);
    }
    contenu[strlen(contenu)-1] = '\0';
    fclose(file);

    struct Score ** liste_score = malloc(10 * sizeof(struct Score *));
    for (int i = 0; i < 10; i++) liste_score[i] = NULL;

    char * tmp_score = strtok(contenu, ";");
    int i = 0;
    while (tmp_score != NULL) {
        liste_score[i] = recupScore(tmp_score);
        printf("TMP_SCORE : %s\n", tmp_score);
        tmp_score = strtok(NULL, ";");
        i++;
    }

    return liste_score;
}


void affichageHiscores(struct Score ** liste_score) {
    for (int j = 0; j < 10; j++) {
        if (liste_score[j] != NULL) {
            printf("ID = %d | PSEUDO = %s | SCORE = %d\n", liste_score[j]->id, liste_score[j]->pseudo, liste_score[j]->score);
        } else break;
    }
}