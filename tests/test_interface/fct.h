#ifndef FCT
#define FCT

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH_LOGO 72
#define HEIGHT_LOGO 6

#define WIDTH_CONTROLE 20
#define HEIGHT_CONTROLE 9

#define WIDTH_MENU 80
#define HEIGHT_MENU 20

#define ELEM1 "LANCER UNE PARTIE"
#define ELEM2 "HI-SCORES"
#define ELEM3 "QUITTER"

#define SZ1 17
#define SZ2 9
#define SZ3 7

void affichageRetromario(WINDOW * win);
void affichageControle(WINDOW * controle);
void actionMenu(WINDOW * menu);

#endif