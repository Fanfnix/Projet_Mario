#ifndef TEST
#define TEST

#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* MAP : Création, affichage */
#define TX 3
#define TY 2

struct Map {
    int height, width;
    char ** carte;
};

struct Elem {
    char nom[20];
    int nb_frame;
    int height, width;
    int x, y;
};

struct Map * creerMap(int L, int l);
void libMemMap(struct Map * niv);
void afficherMap(WINDOW * fenetre, struct Map * niv);
int iterationMap(struct Map * niv, int X, int dMax, int * table, int * seed, int version);
int avancerMap(struct Map * niv, int X, int dMax, int * table, int * seed, int version);

void afficherMap_simp(WINDOW * fenetre, struct Map * niv);
void afficherTmp(WINDOW * tmp, int X, int Y, int dMax, int * table, int seed);

void affichageElem(WINDOW * win, struct Elem truc, int dMax);

/* MAP : Génération aléatoire */
#define DISTANCE 12  // Longueur de chaque pente
#define VARIANCE 6  // Variation dans les hauteurs générées
#define Y_MIN 2  // Hauteur minimale

int * creerTableSeed(int * seed);
int * iterationTable(int * seed, int * table);
int rand_nb(int seed);
int perlin(int x, int * table, int * seed);

#endif