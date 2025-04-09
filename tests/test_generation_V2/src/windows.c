#include "../include/header.h"
#if _WIN32
#include <conio.h>
#include <windows.h>

void gotoxy(int xpos, int ypos)
{
        COORD scrn;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);

        scrn.X = xpos;
        scrn.Y = ypos;
        SetConsoleCursorPosition(hOuput, scrn);
}

#endif

WINDOW *newwin_perso(int height, int width, int yo, int xo) {
    #if __linux__
    return newwin(height, width, yo, xo);
    #elif _WIN32
    WINDOW * new = malloc(sizeof(WINDOW));
    if (new != NULL) {
        new->precedent = NULL;
        new->yo = yo;
        new->xo = xo;
        new->width = width;
        new->height = height;
        return new;
    } else printf("ERR : newwin failed\n");
    return NULL;
    #endif
}

WINDOW *derwin_perso(WINDOW *win, int height, int width, int yo, int xo) {
    #if __linux__
    return derwin(win, height, width, yo, xo);
    #elif _WIN32
    WINDOW * der = malloc(sizeof(WINDOW));
    if (win != NULL) {
        der->precedent = win;
        der->yo = yo;
        der->xo = xo;
        der->width = width;
        der->height = height;
        return der;
    } else printf("ERR : derwin failed\n");
    return NULL;
    #endif
}

void mvwaddstr_perso(WINDOW *win, int y, int x, char str[]) {
    #if __linux__
    mvwaddstr(win, y, x, str);
    #elif _WIN32
    WINDOW * tmp = win;
    while(tmp != NULL) {
        y += tmp->yo;
        x += tmp->xo;
        tmp = tmp->precedent;
    }
    gotoxy(x,y);
    for(int i = 0; i < strlen(str); i++) putch(str[i]);
    #endif
}

void mvwaddch_perso(WINDOW *win, int y, int x, char ch) {
    #if __linux__
    mvwaddch(win, y, x, ch);
    #elif _WIN32
    WINDOW * tmp = win;
    while(tmp != NULL) {
        y += tmp->yo;
        x += tmp->xo;
        tmp = tmp->precedent;
    }
    gotoxy(x,y);
    putch(ch);
    #endif
}

void wborder_perso(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d) {
    #if __linux__
    wborder(win, gauche, droit, haut, bas, haut_g, haut_d, bas_g, bas_d);
    #elif _WIN32
    if(win == NULL) return;
    // Bar haut
    char bar_haut[255] = {'\0'};
    for (int i = 0; i < win->width+1; i++) {
        if (i == 0) strcat(bar_haut, &haut_g);
        else if (i == (win->width)) strcat(bar_haut, &haut_d);
        else strcat(bar_haut, &haut);
    }
    mvwaddstr_perso(win, 0, 0, bar_haut);
    // Cotes
    for (int j = 1; j < win->height-1; j++) {
        mvwaddch_perso(win, j, 0, gauche);
        mvwaddch_perso(win, j, win->width, droit);
    }
    // Bar bas
    char bar_bas[255] = {'0'};
    for (int i = 0; i < win->width+1; i++) {
        if (i == 0) strcat(bar_bas, &bas_g);
        else if (i == (win->width)) strcat(bar_bas, &bas_d);
        else strcat(bar_bas, &bas);
    }
    mvwaddstr_perso(win, win->height-1, 0, bar_bas);
    #endif
}

void wrefresh_perso(WINDOW *win){
    #if __linux__
    wrefresh(win);
    #endif
};