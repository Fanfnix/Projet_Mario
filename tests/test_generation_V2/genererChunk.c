#include "header.h"

void genererChunk(struct Map* niv, int id_chunk, int* table, int* seed) {
    int ymax;
    int x_mystery, y_mystery, genere_mystery = 0;
    // Plateforme >>>
    int plateforme = table[0] % 3;
    int startx_plateforme, starty_plateforme, finishy_plateforme, len_plateforme, mod;
    if (plateforme) {
        startx_plateforme = abs(table[0]) % (DISTANCE - 3);
        starty_plateforme = 0;
        finishy_plateforme = 0;
        mod = DISTANCE - startx_plateforme - 3;
        if (mod <= 0) mod = 1;
        len_plateforme = 3 + abs(table[startx_plateforme]) % mod;
    }
    // <<< Plateforme
    // Terrain >>>
    for (int x = id_chunk*DISTANCE; x < DISTANCE*(id_chunk+1); x++) {
        ymax = perlin(x, table, seed);
        if (x % DISTANCE == 0) {
            for (int y = niv->height-ymax; y < niv->height; y++) niv->carte[y][x] = 2;
        } else {
            for (int y = niv->height-ymax; y < niv->height; y++) niv->carte[y][x] = 1;
        }
        // <<< Terrain
        // Plateforme >>>
        if (plateforme) {
            if (x % DISTANCE == startx_plateforme) starty_plateforme = niv->height-ymax;
            if (x % DISTANCE == startx_plateforme+len_plateforme) finishy_plateforme = niv->height-ymax;
        }
        // <<< Plateforme
    }
    // Plateforme >>>
    if (plateforme) {
        if (starty_plateforme > finishy_plateforme) {
            finishy_plateforme -= H_PLATEFORME;
            starty_plateforme = finishy_plateforme;
        } else {
            starty_plateforme -= H_PLATEFORME;
        }
        if (starty_plateforme < 0) starty_plateforme = 0;
        for (int x = id_chunk*DISTANCE+startx_plateforme; x < id_chunk*DISTANCE+startx_plateforme+len_plateforme; x++) niv->carte[starty_plateforme][x] = 1;
            for (int i = startx_plateforme; i < startx_plateforme+len_plateforme; i++) {
            if (!genere_mystery && table[i] % 5 == 1) {
                x_mystery = id_chunk * DISTANCE + i;
                y_mystery = starty_plateforme;
                genere_mystery = 1;
            }
        }
        if (genere_mystery) niv->carte[y_mystery][x_mystery] = 3;
    }
    // <<< Plateforme
}