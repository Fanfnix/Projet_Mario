#ifndef TEST
#define TEST

#if __linux__
#include <ncurses.h>
#elif _WIN32
#include <conio.h>
#endif

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

#if __linux__
void afficherMap(WINDOW * fenetre, struct Map * niv, int height_carte, int width_carte);
void afficherMap_simp(WINDOW* fenetre, struct Map* niv, int height_carte, int width_carte);
void afficherTmp(WINDOW* tmp, int X, int Y, int dMax, int* table, int seed);
#elif _WIN32
void afficherMap_W(struct Map * niv, int height_carte, int width_carte);
void afficherMap_simp_W(struct Map* niv, int height_carte, int width_carte);
void afficherTmp_W(int X, int Y, int dMax, int* table, int seed);
#endif

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