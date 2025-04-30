#include "../include/header.h"

void genererChunk(struct Map * niv, int id_chunk, int * table, int * seed) {
    int CHO = id_chunk * DISTANCE;
    if (table == NULL && seed == NULL) {
        for (int x = CHO; x < CHO + DISTANCE; x++) {
            for (int y = niv->height-Y_MIN; y < niv->height; y++) niv->carte[y][x] = 1;
        }
        return;
    }
    // Variables >>>
    int ymax;
    int ydeb = 0, yfin = 0;
    int startx_plateforme, starty_plateforme = 0, finishy_plateforme = 0, len_plateforme, mod;
    int x_mystery, y_mystery, genere_mystery = 0;
    int startx_piece, x_piece = 0, y_piece = 0, nb_piece, compteur_piece = 0;
    int x_tuyaux, y_tuyaux;
    float x_goomba, y_goomba, speed_goomba;
    // <<< Variables
    // Aléatoire >>>
    int plateforme = (table[0] % 3) == 1;
    int piece = (table[0] % 2) == 1;
    int tuyau = ((table[0] / 10) % 3) == 0 || ((table[0] / 10) % 3) == 1;
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
    // Goomba >>>
    struct Goomba * goomba;
    if (!tuyau) {
        x_goomba = abs(table[2]) % DISTANCE;
        speed_goomba = (table[(int)x_goomba] % 2) ? -1 : 1;
    }
    // >>> Goomba
    // Terrain >>>
    for (int x = CHO; x < CHO + DISTANCE; x++) {
        ymax = perlin(x, table, seed);
        if (x == CHO) ydeb = ymax;
        if (x == CHO + DISTANCE - 1) yfin = ymax;
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
        if (piece && x % DISTANCE >= startx_piece && compteur_piece < nb_piece) {
            x_piece = x;
            y_piece = niv->height - ymax - 1;
            if (niv->carte[y_piece][x_piece] == 0) niv->carte[y_piece][x_piece] = 4;
            compteur_piece++;
        }
        // <<< Piece
        // Goomba >>>
        if (!tuyau && x % DISTANCE == x_goomba) {
            goomba = creerGoomba(id_chunk, (float)(CHO + x_goomba), (float)(niv->height - ymax), speed_goomba);
            ajouterGoomba(niv->liste_goomba, goomba);
        }
        // >>> Goomba
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
        for (int x = CHO + startx_plateforme; x < CHO + startx_plateforme + len_plateforme; x++) niv->carte[starty_plateforme][x] = 1;
        for (int i = startx_plateforme; i < startx_plateforme+len_plateforme; i++) {
            // Mystery >>>
            if (!genere_mystery && table[i] % 5 == 1) {
                x_mystery = CHO + i;
                y_mystery = starty_plateforme;
                niv->carte[y_mystery][x_mystery] = 3;
                genere_mystery = 1;
            }
            // <<< Mystery
            // Piece >>>
            if (genere_piece_on_plateforme) {
                x_piece = CHO + i;
                y_piece = starty_plateforme - 1;
                niv->carte[y_piece][x_piece] = 4;
            }
            // <<< Piece
        }
    // <<< Plateforme
    } else {
        // Tuyau >>>
        if (ydeb == yfin && tuyau) {
            x_tuyaux = CHO + abs(table[0] % (DISTANCE - 3));
            y_tuyaux = niv->height - ydeb - 1;
            niv->carte[y_tuyaux][x_tuyaux] = 5;
            niv->carte[y_tuyaux][x_tuyaux+1] = 6;
            niv->carte[y_tuyaux][x_tuyaux+2] = 6;
            niv->carte[y_tuyaux-1][x_tuyaux] = 6;
            niv->carte[y_tuyaux-1][x_tuyaux+1] = 6;
            niv->carte[y_tuyaux-1][x_tuyaux+2] = 6;
        }
        // <<< Tuyau
    }
}