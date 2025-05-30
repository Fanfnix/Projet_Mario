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

#define WIDTH_CONTROLE 22
#define HEIGHT_CONTROLE 9

#define WIDTH_MENU 30

#define WIDTH_ELOISE 120
#define HEIGHT_ELOISE 30

#define WIDTH_ASCII 36
#define HEIGHT_ASCII 36

#define WIDTH_BLOCPIECE 36
#define HEIGHT_BLOCPIECE 36

struct Score {
    int id;
    char pseudo[50];
    int score;
};

typedef struct Save
{
    int id;
    int seed;
    int distance;
    int coin;
    int goomba_tuee;
    float posx;
    float posy;
    int vies;
} Save;

WIN * creerFenetre(WINDOW * fenetre, int width, int height);

WIN * creerWindowLogo();
WIN * creerWindowMenu();
WIN * creerWindowChoix();
WIN * creerWindowControle();
WIN * creerWindowEloise();
WIN * creerWindowAscii(WIN * win);
WIN * creerWindowBlocpiece(WIN * win);

void affichageRetromario(WIN * win);
void affichageControle(WIN * controle);
void affichageDessinmenu(WIN * eloise);
void affichageAscii(WIN * ascii);
void affichageBlocpiece(WIN * blocpiece);

void affichageGenerale(WIN * logo, WIN * controle, WIN * eloise);

void affichageMenuPrincipal(WIN * menu, int choix);
void actionMenuPrincipal(WIN* menu, int* id, Mix_Chunk* selectSE, Mix_Chunk* confirmeSE);

// HI-SCORE
struct Score * recupScore(char * str);
struct Score ** recupHiscores();

void ecritureHiscores(struct Score ** liste_score);
void trierHiscores(struct Score ** liste_score);

void affichageHiscores(WIN * win, WIN * ascii,WIN * blocpiece, struct Score ** liste_score, int choisi);
void actionHiscores(WIN* win, WIN * ascii,WIN * blocpiece, struct Score** liste_score, int* id, Mix_Chunk* selectSE, Mix_Chunk* degatSE);
void supprHiscores(struct Score ** liste_score, int id);
void libererHiscores(struct Score ** liste_score);

// SAUVEGARDES
Save * recupSave(char * str);
Save ** recupCheckpoint();
void ecritureSauvegarde(struct Save ** liste_sauvegarde);
void affichageSauvegarde(WIN * win,WIN * ascii, WIN * blocpiece, Save ** liste_sauvegarde, int choisi);
int actionSauvegarde(WIN* win,WIN * ascii, WIN * blocpiece, Save** liste_sauvegarde, int* id, Mix_Chunk* selectSE, Mix_Chunk* degatSE);
void supprSauvegarde(Save ** liste_sauvegarde, int id);
void libererSauvegarde(Save ** liste_sauvegarde);

void nettoyerMenu(WIN * logo, WIN * menu, WIN * choix, WIN * controle, WIN * eloise, WIN * ascii, WIN * blocpiece);

void supprWin(WIN * fenetre);

#endif