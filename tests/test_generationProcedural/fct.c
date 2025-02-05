#include "fct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>


int convInt(float y) {
    float tmp = y * 100;
    int res = (int)tmp;
    if (y > res / 100 + 0.5) {
        res = res / 100 + 1;
    } else {
        res =  res / 100;
    }
    return res;
}

// MAP : Génération aléatoire //

int f(int x) {
    return (16807 * x) % 2147483646;
}

void iterationSeed(int * seed) {
    *seed = f(*seed);
}

float lissage(float x) {
    return 3 * pow(x, 2) - 2 * pow(x, 3);
}

float interpolate(int y_prec, int y_suiv, int x) {
    return (y_suiv - y_prec) * lissage((float)(x % DISTANCE) / DISTANCE) + y_prec;
}

int * creerTableSeed(int * seed) {
    int * table = malloc(DISTANCE*sizeof(int));
    return table;
}

int * iterationTable(int * seed, int * table) {
    for (int i = 0; i < DISTANCE; i++) {
        table[i] = *seed;
        iterationSeed(seed);
    }
    return table;
}

int perlin(int x, int * table, int * seed) {
    if (x % DISTANCE == 0) {
        table = iterationTable(seed, table);
        int y_prec = (abs(table[0] / 100000000) % VARIANCE) + Y_MIN;
        // printf("X = %d | Y_PREC : %d\n", x, y_prec);
        return y_prec;
    }
    else {
        int y_prec = (abs(table[0] / 100000000) % VARIANCE) + Y_MIN;
        int y_suiv = (abs(f(table[DISTANCE-1]) / 100000000) % VARIANCE) + Y_MIN;

        int y = convInt(interpolate(y_prec, y_suiv, x));

        // printf("X = %d | Y_PREC : %d | Y_SUIV : %d\n", x, y_prec, y_suiv);
        return y;
    }
}


// MAP : Création, affichage //

struct Map * creerMap(int L, int l) {
    struct Map *niv = malloc(sizeof(struct Map));
    if (!niv) {return NULL;}
    niv->L = L;
    niv->l = l;
    
    niv->carte = malloc(L * sizeof(char *));
    if (!niv->carte) {
        free(niv);
        return NULL;
    }
    
    for (int y = 0; y < L; y++) {
        niv->carte[y] = malloc(l * sizeof(char));
        if (!niv->carte[y]) {
            for (int j = 0; j < y; j++) free(niv->carte[j]);
            free(niv->carte);
            free(niv);
            return NULL;
        }
        memset(niv->carte[y], '0', l);
    }
    return niv;
}

void libMemMap(struct Map *niv) {
    if (!niv) return;
    for (int y = 0; y < niv->L; y++) {
        free(niv->carte[y]);
    }
    free(niv->carte);
    free(niv);
}

void afficherMap(struct Map *niv) {
    for (int y = 0; y < niv->L; y++) {
        for (int x = 0; x < niv->l; x++) {
            char ch = (niv->carte[y][x] == '0') ? ' ' : niv->carte[y][x];
            printw("%c", ch);
        }
    }
}

void iterationMap(struct Map * niv, int x, int * table, int * seed, int version) {
    int y;
    switch (version) {
        case 1: y = perlin(x, table, seed); break;
        case 0: y = 5; break;
    }

    if (y < 0 || y >= niv->L) {
        printf("ERR M1 : Y = %d\n", y);
    }
    else {
        for (int i = niv->L - 1; i >= niv->L - y; i--) {
            if (x % DISTANCE == 0) {
                niv->carte[i][x] = 'O';
            } else {
                niv->carte[i][x] = '#';
            }
        }
    }
}
    