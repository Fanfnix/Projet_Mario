#include "fct.h"

int main() {

    WINDOW * logo;
    WINDOW * menu;
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;

    initscr();

    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;

    height_fenetre_menu = HEIGHT_MENU + 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = (COLS - width_fenetre_menu) / 2;
    starty_fenetre_menu = (LINES - height_fenetre_menu) / 2;

    menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);

    logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    affichageRetromario(logo);

    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');

    while (wgetch(menu) == -1);

    endwin();

    return 0;
}