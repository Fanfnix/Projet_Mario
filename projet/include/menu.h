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

WIN * creerFenetre(WINDOW * fenetre, int width, int height);

WIN * creerWindowLogo();
WIN * creerWindowMenu();
WIN * creerWindowChoix();
WIN * creerWindowControle();
WIN * creerWindowEloise();

void affichageRetromario(WIN * win);
void affichageControle(WIN * controle);
void affichageDessinmenu(WIN * eloise);

void affichageGenerale(WIN * logo, WIN * controle, WIN * eloise);

void affichageMenuPrincipal(WIN * menu, int choix);
void actionMenuPrincipal(WIN* menu, int* id, Mix_Chunk* selectSE, Mix_Chunk* confirmeSE);

// HI-SCORE
struct Score * recupScore(char * str);
struct Score ** recupHiscores();

void ecritureHiscores(struct Score ** liste_score);
void trierHiscores(struct Score ** liste_score);

void affichageHiscores(WIN * win, struct Score ** liste_score, int choisi);
void actionHiscores(WIN* win, struct Score** liste_score, int* id, Mix_Chunk* selectSE, Mix_Chunk* degatSE);
void supprHiscores(struct Score ** liste_score, int id);
void libererHiscores(struct Score ** liste_score);

// SAUVEGARDES
Save * recupSave(char * str);
Save ** recupCheckpoint();
void ecritureSauvegarde(struct Save ** liste_sauvegarde);
void affichageSauvegarde(WIN * win, Save ** liste_sauvegarde, int choisi);
void actionSauvegarde(WIN* win, Save** liste_sauvegarde, int* id, Mix_Chunk* selectSE, Mix_Chunk* degatSE);
void supprSauvegarde(Save ** liste_sauvegarde, int id);
void libererSauvegarde(Save ** liste_sauvegarde);

void nettoyerMenu(WIN * logo, WIN * menu, WIN * choix, WIN * controle, WIN * eloise);

void supprWin(WIN * fenetre);

#endif