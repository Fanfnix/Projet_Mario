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

void actionMenuPrincipal(WINDOW * menu) {
    int id = 0;
    char pressed;
    do {
        if (pressed == 'z') id--;
        else if (pressed == 's') id++;
        else if (pressed == '\n') {
            if (id == 0) continue;  // Lancer partie
            else if (id == 1) continue;  // Afficher hi-scores
            else if (id == 2) continue;  // Afficher sauvegardes
            else if (id == 3) break;
        }
        if (id < 0) id = 3;
        if (id > 3) id = 0;
        affichageMenuPrincipal(menu, id);
    } while ((pressed = wgetch(menu)) != 'k');
}