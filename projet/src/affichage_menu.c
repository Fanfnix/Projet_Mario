#include "../include/header.h"

void affichageDessinmenu(WIN * eloise){
    char chemin[] = "./design/dessinmenu/dessinmenu1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_ELOISE; y++){
            char tmp[WIDTH_ELOISE+1];
            fgets(tmp, WIDTH_ELOISE+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(eloise->fenetre, y+1, 1, tmp);
        }
        wrefresh(eloise->fenetre);
        fclose(file);
    }
}

void affichageAscii(WIN * ascii){
    char chemin[] = "./design/ascii/ascii1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_ASCII; y++){
            char tmp[WIDTH_ASCII+1];
            fgets(tmp, WIDTH_ASCII+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(ascii->fenetre, y+1, 1, tmp);
        }
        wrefresh(ascii->fenetre);
        fclose(file);
    }
}

void affichageBlocpiece(WIN * blocpiece){
    char chemin[] = "./design/blocpiece/blocpiece1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_BLOCPIECE; y++){
            char tmp[WIDTH_BLOCPIECE+1];
            fgets(tmp, WIDTH_BLOCPIECE+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(blocpiece->fenetre, y+1, 1, tmp);
        }
        wrefresh(blocpiece->fenetre);
        fclose(file);
    }
}

void affichageRetromario(WIN * logo) {
    char chemin[] = "./design/retromario/retromario1.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file != NULL) {
        wattron(logo->fenetre, A_BOLD);
        for (int y = 0; y < HEIGHT_LOGO; y++) {
            char tmp[WIDTH_LOGO+1];
            fgets(tmp, WIDTH_LOGO+1, file);
            for (int i = 0; i < strlen(tmp); i++) {
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(logo->fenetre, y+1, 1, tmp);
        }
        wattroff(logo->fenetre, A_BOLD);
        wrefresh(logo->fenetre);
        fclose(file);
    }
}

void affichageControle(WIN * controle) {
    wborder(controle->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle->fenetre, 2, 3, "> SAUTER : [SPACE]");
    mvwaddstr(controle->fenetre, 4, 3, "> GAUCHE : <");
    mvwaddstr(controle->fenetre, 6, 3, "> DROITE : >");
    mvwaddstr(controle->fenetre, 8, 3, "> PAUSE :  [ESC]");

    wrefresh(controle->fenetre);
}

void affichageGenerale(WIN * logo, WIN * controle, WIN * eloise) {
    affichageRetromario(logo);
    affichageControle(controle);
    affichageDessinmenu(eloise);

}

void affichageMenuPrincipal(WIN * menu, int choix) {
    wclear(menu->fenetre);
    const int taille_menu = 4;
    char liste_menu[4][100] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu->fenetre);
    wattron(menu->fenetre, A_BOLD);
    wborder(menu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(menu->fenetre, A_BOLD);
    char affiche[255];
    for (int i = 0; i < taille_menu; i++) {
        if (i == choix) {
            sprintf(affiche, "> %s <", liste_menu[i]);
            wattron(menu->fenetre, A_BOLD);
        } else sprintf(affiche, "  %s  ", liste_menu[i]);
        mvwaddstr(menu->fenetre, 4*(i+1), (WIDTH_MENU-(strlen(liste_menu[i])+4)+1)/2, affiche);
        if (i == choix) wattroff(menu->fenetre, A_BOLD);
    }
    wrefresh(menu->fenetre);
}