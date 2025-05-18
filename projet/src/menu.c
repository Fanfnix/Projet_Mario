#include "../include/header.h"


WIN * creerFenetre(WINDOW * fenetre, int width, int height) {
    WIN * win = malloc(sizeof(WIN));
    if (win == NULL || fenetre == NULL) return NULL;
    win->fenetre = fenetre;
    win->width = width;
    win->height = height;
    return win;
}


WIN * creerWindowLogo() {
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;
    WINDOW * logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    WIN * fenetre = creerFenetre(logo, width_fenetre_logo, height_fenetre_logo);
    return fenetre;
}


WIN * creerWindowControle() {
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;
    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = COLS - width_fenetre_controle - 2;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;
    WINDOW * controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    WIN * fenetre = creerFenetre(controle, width_fenetre_controle, height_fenetre_controle);
    return fenetre;
}


WIN * creerWindowMenu() {
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    height_fenetre_menu = LINES - 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = 2;
    starty_fenetre_menu = 1;
    WINDOW * menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);
    keypad(menu, true);
    WIN * fenetre = creerFenetre(menu, width_fenetre_menu, height_fenetre_menu);
    return fenetre;
}


WIN * creerWindowChoix() {
    int height_fenetre_choix, width_fenetre_choix, startx_fenetre_choix, starty_fenetre_choix;
    height_fenetre_choix = LINES - 2;
    width_fenetre_choix = COLS - WIDTH_MENU - 7;
    startx_fenetre_choix = WIDTH_MENU + 6;
    starty_fenetre_choix = 1;
    WINDOW * choix = newwin(height_fenetre_choix, width_fenetre_choix, starty_fenetre_choix, startx_fenetre_choix);
    keypad(choix, true);
    WIN * fenetre = creerFenetre(choix, width_fenetre_choix, height_fenetre_choix);
    return fenetre;
}


WIN * creerWindowEloise() {
    int height_fenetre_eloise, width_fenetre_eloise, startx_fenetre_eloise, starty_fenetre_eloise;
    height_fenetre_eloise = HEIGHT_ELOISE;
    width_fenetre_eloise = WIDTH_ELOISE;
    startx_fenetre_eloise = (COLS - width_fenetre_eloise) / 2;
    starty_fenetre_eloise = (LINES - height_fenetre_eloise) / 2;
    WINDOW * eloise = newwin(height_fenetre_eloise, width_fenetre_eloise, starty_fenetre_eloise, startx_fenetre_eloise);
    WIN * fenetre = creerFenetre(eloise, width_fenetre_eloise, height_fenetre_eloise);
    return fenetre;
}

WIN * creerWindowAscii(WIN * win) {
    int height_fenetre_ascii, width_fenetre_ascii, startx_fenetre_ascii, starty_fenetre_ascii;
    height_fenetre_ascii = HEIGHT_ASCII + 2;
    width_fenetre_ascii = WIDTH_ASCII + 2;
    startx_fenetre_ascii = 50;
    starty_fenetre_ascii = 6;
    WINDOW * ascii = newwin(height_fenetre_ascii, width_fenetre_ascii, starty_fenetre_ascii, startx_fenetre_ascii);
    WIN * fenetre = creerFenetre(ascii, width_fenetre_ascii, height_fenetre_ascii);
    return fenetre;
}

WIN * creerWindowBlocpiece(WIN * win) {
    int height_fenetre_blocpiece, width_fenetre_blocpiece, startx_fenetre_blocpiece, starty_fenetre_blocpiece;
    height_fenetre_blocpiece = HEIGHT_BLOCPIECE + 2;
    width_fenetre_blocpiece = WIDTH_BLOCPIECE + 2;
    startx_fenetre_blocpiece = win->width - WIDTH_MENU / 2;
    starty_fenetre_blocpiece = 7;
    WINDOW * blocpiece = newwin(height_fenetre_blocpiece, width_fenetre_blocpiece, starty_fenetre_blocpiece, startx_fenetre_blocpiece);
    WIN * fenetre = creerFenetre(blocpiece, width_fenetre_blocpiece, height_fenetre_blocpiece);
    return fenetre;
}

void actionMenuPrincipal(WIN * menu, int * id, Mix_Chunk* selectSE, Mix_Chunk* confirmeSE) {
    int pressed;
    affichageMenuPrincipal(menu, *id);
    while ((pressed = wgetch(menu->fenetre)) != 10) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        if (*id < 0) *id = 3;
        if (*id > 3) *id = 0;
        affichageMenuPrincipal(menu, *id);
    }
    Mix_PlayChannel(-1, confirmeSE, 0);
}


void actionHiscores(WIN * win, WIN * ascii, WIN * blocpiece, struct Score ** liste_score, int * id, Mix_Chunk* selectSE, Mix_Chunk* degatSE) {
    int pressed;
    affichageHiscores(win, ascii, blocpiece, liste_score, *id);
    while ((pressed = wgetch(win->fenetre)) != 27) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == 8 || pressed == 263) {
            supprHiscores(liste_score, *id);  // Supprimer le score
            Mix_PlayChannel(-1, degatSE, 0);
        }
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageHiscores(win, ascii, blocpiece, liste_score, *id);
    }
    wclear(win->fenetre);
    wrefresh(win->fenetre);
}

int actionSauvegarde(WIN * win, WIN * ascii, WIN * blocpiece, struct Save ** liste_sauvegarde, int * id, Mix_Chunk* selectSE, Mix_Chunk* degatSE) {
    int pressed;
    affichageSauvegarde(win, ascii, blocpiece, liste_sauvegarde, *id);
    while ((pressed = wgetch(win->fenetre)) != 27) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == 8 || pressed == 263) {
            supprSauvegarde(liste_sauvegarde, *id);  // Supprimer la sauvegarde
            Mix_PlayChannel(-1, degatSE, 0);
        }
        else if (pressed == 10) {
            return 1;
        }
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageSauvegarde(win, ascii, blocpiece, liste_sauvegarde, *id);
    }
    wclear(win->fenetre);
    wrefresh(win->fenetre);
    return 0;
}


void nettoyerMenu(WIN * logo, WIN * menu, WIN * choix, WIN * controle, WIN * eloise, WIN * ascii, WIN * blocpiece) {
    wclear(logo->fenetre);
    wrefresh(logo->fenetre);

    wclear(menu->fenetre);
    wrefresh(menu->fenetre);

    wclear(choix->fenetre);
    wrefresh(choix->fenetre);

    wclear(controle->fenetre);
    wrefresh(controle->fenetre);

    wclear(eloise->fenetre);
    wrefresh(eloise->fenetre);

    wclear(ascii->fenetre);
    wrefresh(ascii->fenetre);

    wclear(blocpiece->fenetre);
    wrefresh(blocpiece->fenetre);
}


void supprWin(WIN * fenetre) {
    if (fenetre == NULL) return;
    if (fenetre->fenetre != NULL) {
        wclear(fenetre->fenetre);
        wrefresh(fenetre->fenetre);
        delwin(fenetre->fenetre);
    }
    free(fenetre);
    fenetre = NULL;
}