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

#define WIDTH_CHOIX 40

#define WIDTH_ELOISE 120
#define HEIGHT_ELOISE 30

struct Score {
    int id;
    char pseudo[50];
    int score;
};

WINDOW * creerWindowLogo();
WINDOW * creerWindowMenu();
WINDOW * creerWindowChoix();
WINDOW * creerWindowControle();
WINDOW * creerWindowEloise();

void affichageRetromario(WINDOW * win);
void affichageControle(WINDOW * controle);

void affichageMenuPrincipal(WINDOW * menu, int choix);
void actionMenuPrincipal(WINDOW * menu, int * id);

struct Score ** recupHiscores();
struct Score ** recupHiscores();
void affichageHiscores(WINDOW * win, struct Score ** liste_score);
void libererHiscores(struct Score ** liste_score);

#endif