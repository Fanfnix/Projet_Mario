#ifndef TEST
#define TEST

#include <ncurses.h>

/* MAP : Création, affichage */
#define TX 3
#define TY 2

struct Map {
    int L;
    int l;
    char ** carte;
};

struct Map * creerMap(int L, int l);
void libMemMap(struct Map * niv);
void afficherMap(WINDOW * fenetre, struct Map * niv);
void iterationMap(struct Map * niv, int x, int * table, int * seed, int version);
// void avancerMap(struct Map * niv, int * table, int * seed, int version);


/* MAP : Génération aléatoire */
#define DISTANCE 12  // Longueur de chaque pente
#define VARIANCE 6  // Variation dans les hauteurs générées
#define Y_MIN 2  // Hauteur minimale

int * creerTableSeed(int * seed);
int * iterationTable(int * seed, int * table);
int rand_nb(int seed);
int perlin(int x, int * table, int * seed);

#endif