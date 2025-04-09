#ifndef MENU
#define MENU

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#define WIDTH_LOGO 72
#define HEIGHT_LOGO 6

#define WIDTH_CONTROLE 20
#define HEIGHT_CONTROLE 9

#define WIDTH_MENU 30
#define HEIGHT_MENU 53

struct Score {
    int id;
    char pseudo[10];
    int score;
};

void affichageRetromario(WINDOW * win);
void affichageControle(WINDOW * controle);
int actionMenuPrincipal(WINDOW * menu);

struct Score ** recupHiscores();
void affichageHiscores(WINDOW * win, struct Score ** liste_score);

#endif