#include "../include/header.h"

int main() {

    WINDOW * logo;
    WINDOW * menu;
    WINDOW * controle;
    WINDOW * eloise;
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;
    int height_fenetre_eloise, width_fenetre_eloise, startx_fenetre_eloise, starty_fenetre_eloise;

    struct Score **liste_score;

    #if __linux__
    initscr();
    curs_set(0);
    noecho();
    #endif

    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;

    logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    affichageRetromario(logo);

    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = COLS - width_fenetre_controle - 2;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;

    controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    affichageControle(controle);

    height_fenetre_menu = LINES - 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = 2;
    starty_fenetre_menu = 1;

    menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);

    height_fenetre_eloise = 30;
    width_fenetre_eloise = 130;
    startx_fenetre_eloise = 45;
    starty_fenetre_eloise = 11;

    eloise = newwin(height_fenetre_eloise, width_fenetre_eloise, starty_fenetre_eloise, startx_fenetre_eloise);
    wborder(eloise, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(eloise);

    liste_score = recupHiscores();
    
    int choix_principal;
    choix_principal = actionMenuPrincipal(menu);
    switch (choix_principal) {
        case 0: break;
        case 1: affichageHiscores(stdscr, liste_score); break;
        case 2: break;
        case 3: break;
    }

    mvwaddstr(stdscr, LINES-2, 2, "Press k to leave");
    while(getch() != 'k');

    endwin();
        
    return 0;
}