#include "../include/header.h"

void genererChunk(struct Map* niv, int id_chunk, int* table, int* seed) {
    // Variables >>>
    int ymax;
    int startx_plateforme, starty_plateforme = 0, finishy_plateforme = 0, len_plateforme, mod;
    int x_mystery, y_mystery, genere_mystery = 0;
    int startx_piece, x_piece = 0, y_piece = 0, nb_piece, compteur_piece = 0;
    // <<< Variables
    // Aléatoire >>>
    int plateforme = table[0] % 3 == 1;
    int piece = table[0] % 2;
    // <<< Aléatoire
    // Plateforme >>>
    if (plateforme) {
        startx_plateforme = abs(table[0]) % (DISTANCE - 3);
        mod = DISTANCE - startx_plateforme - 3;
        if (mod <= 0) mod = 1;
        len_plateforme = 3 + abs(table[startx_plateforme]) % mod;
    }
    // <<< Plateforme
    // Piece >>>
    int genere_piece_on_plateforme = table[startx_plateforme] % 2;
    if (piece) {
        startx_piece = abs(table[1]) % (DISTANCE - 3);
        mod = DISTANCE - x_piece - 3;
        if (mod <= 0) mod = 1;
        nb_piece = 3 + abs(table[x_piece]) % mod;
    }
    // <<< Piece
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
            if (x % DISTANCE == startx_plateforme) starty_plateforme = niv->height - ymax;
            if (x % DISTANCE == startx_plateforme+len_plateforme) finishy_plateforme = niv->height - ymax;
        }
        // <<< Plateforme
        // Piece >>>
        if (piece && x%DISTANCE >= startx_piece && compteur_piece < nb_piece) {
            x_piece = x;
            y_piece = niv->height - ymax - 1;
            if (niv->carte[y_piece][x_piece] == 0) niv->carte[y_piece][x_piece] = 4;
            compteur_piece++;
        }
        // <<< Piece
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
            // Mystery >>>
            if (!genere_mystery && table[i] % 5 == 1) {
                x_mystery = id_chunk * DISTANCE + i;
                y_mystery = starty_plateforme;
                niv->carte[y_mystery][x_mystery] = 3;
                genere_mystery = 1;
            }
            // <<< Mystery
            // Piece >>>
            if (genere_piece_on_plateforme) {
                x_piece = id_chunk * DISTANCE + i;
                y_piece = starty_plateforme - 1;
                niv->carte[y_piece][x_piece] = 4;
            }
            // <<< Piece
        }
    }
    // <<< Plateforme
}