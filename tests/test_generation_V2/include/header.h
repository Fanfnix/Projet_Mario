#ifndef TEST
#define TEST

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#if __linux__
#include <ncurses.h>

#elif _WIN32


typedef struct WINDOW {
    int xo;
    int yo;
    int height;
    int width;
    struct WINDOW *precedent;
} WINDOW;

#endif

WINDOW *newwin_perso(int height, int width, int yo, int xo);
WINDOW *derwin_perso(WINDOW *win, int height, int width, int yo, int xo);
void mvwaddstr_perso(WINDOW *win, int y, int x, char str[]);
void mvwaddch_perso(WINDOW *win, int y, int x, char ch);
void wborder_perso(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d);
void wrefresh_perso(WINDOW *win);

/* MAP : Création, affichage */
#define TX 3
#define TY 2

struct Map {
    int height, width;
    int** carte;
};

struct Elem {
    char nom[20];
    int nb_frames;
    int height, width;
    int x, y;
};

struct Map* creerMap(int L, int l);
void libMemMap(struct Map* niv);

void afficherMap(WINDOW * fenetre, struct Map * niv, int height_carte, int width_carte);
void afficherMap_simp(WINDOW* fenetre, struct Map* niv, int height_carte, int width_carte);
void afficherTmp(WINDOW* tmp, int X, int Y, int dMax, int* table, int seed);

// int avancerMap(struct Map* niv, int X, int dMax, int* table, int* seed, int version);

void genererChunk(struct Map* niv, int id_chunk, int* table, int* seed);

/* MAP : Génération aléatoire */
#define DISTANCE 8  // Longueur de chaque pente
#define VARIANCE 5  // Variation dans les hauteurs générées
#define Y_MIN 1  // Hauteur minimale

#define H_PLATEFORME 4

int * creerTableSeed();
int * iterationTable(int* seed, int* table);
int rand_nb(int seed);
int perlin(int x, int* table, int* seed);

#endif