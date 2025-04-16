#include "../include/header.h"

int main() {

    WINDOW * logo;
    WINDOW * menu;
    WINDOW * choix;
    WINDOW * controle;
    WINDOW * eloise;

    struct Score **liste_score;
    Save **sauvegarde;

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
    sauvegarde = recupCheckpoint();
    
    system("../musique/monbeaumenu.wav");

    int id = 0;
    int id_choix = 0;
    do {
        actionMenuPrincipal(menu, &id);
        switch (id) {
            case 0: break;
            case 1: actionHiscores(choix, liste_score, &id_choix); break;
            case 2: actionSauvegarde(choix, sauvegarde, &id_choix); break;
            case 3: break;
        }
        affichageGenerale(logo, controle, eloise);
    } while (id != 3);

    endwin();

    libererHiscores(liste_score);
    libererSauvegarde(sauvegarde);
        
    return 0;
}