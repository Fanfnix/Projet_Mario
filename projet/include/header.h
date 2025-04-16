#ifndef HEADER
#define HEADER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <ncurses.h>

WINDOW *newwin_perso(int height, int width, int yo, int xo);
WINDOW *derwin_perso(WINDOW *win, int height, int width, int yo, int xo);
void mvwaddstr_perso(WINDOW *win, int y, int x, char str[]);
void mvwaddch_perso(WINDOW *win, int y, int x, char ch);
void wborder_perso(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d);
void wrefresh_perso(WINDOW *win);

#include "generation.h"
#include "affichage.h"
#include "menu.h"

#endif