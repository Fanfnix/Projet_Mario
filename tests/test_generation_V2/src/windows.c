#include "../include/header.h"
#if _WIN32

WINDOW *newwin(int height, int width, int yo, int xo) {
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
}

WINDOW *derwin(WINDOW *win, int height, int width, int yo, int xo) {
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
}

void mvwaddstr(WINDOW *win, int y, int x, char str[]) {
    WINDOW * tmp = win;
    while(tmp != NULL) {
        y += tmp->yo;
        x += tmp->xo;
        tmp = tmp->precedent;
        gotoxy(x,y);
        for(int i = 0; i < strlen(str); i++) putch(str[i]);
    }
}

void mvwaddch(WINDOW *win, int y, int x, char ch){
    WINDOW * tmp = win;
    while(tmp != NULL) {
        y += tmp->yo;
        x += tmp->xo;
        tmp = tmp->precedent;
        gotoxy(x,y);
        putch(ch);
    }
}

void wborder(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d){

};

void wrefresh(WINDOW *win){

};

#endif