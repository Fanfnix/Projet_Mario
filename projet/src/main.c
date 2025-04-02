#include "../include/header.h"

int main() {

    WINDOW * logo;
    WINDOW * menu;
    WINDOW * controle;
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;

    initscr();

    curs_set(0);
    noecho();

    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;

    logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    affichageRetromario(logo);

    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = 8;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;

    controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    affichageControle(controle);

    height_fenetre_menu = HEIGHT_MENU + 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = (COLS - width_fenetre_menu) / 2;
    starty_fenetre_menu = (LINES - height_fenetre_menu) / 2;

    menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);
    actionMenu(menu);

    endwin();

    return 0;
}