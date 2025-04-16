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

#define WIDTH_ELOISE 120
#define HEIGHT_ELOISE 30

struct Score {
    int id;
    char pseudo[50];
    int score;
};

typedef struct Save
{
    int id;
    int seed;
    int posx;
    int posy;
    int distance;
    int kills;
    int piece;
    int vies;

}Save;

WINDOW * creerWindowLogo();
WINDOW * creerWindowMenu();
WINDOW * creerWindowChoix();
WINDOW * creerWindowControle();
WINDOW * creerWindowEloise();

void affichageRetromario(WINDOW * win);
void affichageControle(WINDOW * controle);
void affichageEloise(WINDOW * eloise);

void affichageGenerale(WINDOW * logo, WINDOW * controle, WINDOW * eloise);

void affichageMenuPrincipal(WINDOW * menu, int choix);
void actionMenuPrincipal(WINDOW * menu, int * id);

struct Score ** recupHiscores();
struct Score ** recupHiscores();

void affichageHiscores(WINDOW * win, struct Score ** liste_score, int choisi);
void actionHiscores(WINDOW * win, struct Score ** liste_score, int * id);
void supprHiscores(struct Score ** liste_score, int id);
void libererHiscores(struct Score ** liste_score);

// SAUVEGARDES
Save * recupSave(char * str);
Save ** recupCheckpoint();
void affichageSauvegarde(WINDOW * win, Save ** liste_sauvegarde, int choisi);
void actionSauvegarde(WINDOW * win, Save ** liste_sauvegarde, int * id);
void supprSauvegarde(Save ** liste_sauvegarde, int id);
void libererSauvegarde(Save ** liste_sauvegarde);


#endif