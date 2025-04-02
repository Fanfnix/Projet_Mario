#include "../include/windows.h"


WINDOW *newwin(int height, int width, int yo, int xo){

};

WINDOW *derwin(WINDOW *win, int height, int width, int yo, int xo){

};

void mvwaddstr(WINDOW *win, int y, int x, char str[]){

};

void mvwaddch(WINDOW *win, int y, int x, char ch){

};

void wborder(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d){

};

void wrefresh(WINDOW *win){

};

