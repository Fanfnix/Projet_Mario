#ifndef WIN
#define WIN

#if _WIN32
#include <conio.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct WINDOW {
    int xo;
    int yo;
    int height;
    int width;
    struct WINDOW *precedent;
} WINDOW;

WINDOW *newwin(int height, int width, int yo, int xo);
WINDOW *derwin(WINDOW *win, int height, int width, int yo, int xo);
void wborder(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d);
void wrefresh(WINDOW *win);
void mvwaddstr(WINDOW *win, int y, int x, char str[]);
void mvwaddch(WINDOW *win, int y, int x, char ch);

#endif