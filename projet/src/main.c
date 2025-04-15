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
    affichageRetromario(logo);

    controle = creerWindowControle();
    affichageControle(controle);

    menu = creerWindowMenu();
    choix = creerWindowChoix();
    eloise = creerWindowEloise();

    liste_score = recupHiscores();
    
    int id = 0;
    int id_choix = 0;
    do {
        actionMenuPrincipal(menu, &id);
        switch (id) {
            case 0: break;
            case 1: actionHiscores(choix, liste_score, &id_choix); refresh(); break;
            case 2: break;
            case 3: break;
        }
    } while (id != 3);

    endwin();

    libererHiscores(liste_score);
        
    return 0;
}