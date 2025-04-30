#include "../include/header.h"

int main() {

    WIN * logo;
    WIN * menu;
    WIN * choix;
    WIN * controle;
    WIN * eloise;

    struct Score ** liste_score;
    Save ** sauvegarde;

    initscr();
    curs_set(0);
    noecho();
    set_escdelay(25);

    logo = creerWindowLogo();
    controle = creerWindowControle();
    eloise = creerWindowEloise();
    menu = creerWindowMenu();
    choix = creerWindowChoix();

    affichageGenerale(logo, controle, eloise);

    liste_score = recupHiscores();
    sauvegarde = recupCheckpoint();

    int id = 0;
    int id_choix = 0;
    int run = 1;
    do {
        actionMenuPrincipal(menu, &id);
        switch (id) {
            case 0: nettoyerMenu(logo, menu, choix, controle, eloise); lancerPartie(); break;
            case 1: actionHiscores(choix, liste_score, &id_choix); break;
            case 2: actionSauvegarde(choix, sauvegarde, &id_choix); break;
            case 3: run = 0; break;
        }
        affichageGenerale(logo, controle, eloise);
    } while (run);

    endwin();

    libererHiscores(liste_score);
    libererSauvegarde(sauvegarde);
        
    return 0;
}