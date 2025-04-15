#include "../include/header.h"

int main() {

    WINDOW * logo;
    WINDOW * menu;
    WINDOW * choix;
    WINDOW * controle;
    WINDOW * eloise;

    struct Score **liste_score;

    initscr();
    curs_set(0);
    noecho();
    nodelay(menu, true);

    logo = creerWindowLogo();
    controle = creerWindowControle();
    eloise = creerWindowEloise();
    menu = creerWindowMenu();
    choix = creerWindowChoix();

    affichageGenerale(logo, controle, eloise);

    liste_score = recupHiscores();
    
    int id = 0;
    int id_choix = 0;
    do {
        actionMenuPrincipal(menu, &id);
        switch (id) {
            case 0: break;
            case 1: actionHiscores(choix, liste_score, &id_choix);
            case 2: break;
            case 3: break;
        }
        affichageGenerale(logo, controle, eloise);
    } while (id != 3);

    endwin();

    libererHiscores(liste_score);
        
    return 0;
}