#include "../include/header.h"

struct Chunk * genererChunk(struct Map * niv, int id_chunk, int * table, int * seed) {
    if (niv == NULL) return NULL;
    struct Chunk * piece = creerChunk(id_chunk, niv->height);
    if (piece == NULL) return NULL;

    // Met un sol dans le cas ou aucune valeur aléatoire lui est donné
    if (table == NULL && seed == NULL) {
        for (int x = 0; x < DISTANCE; x++) for (int y = niv->height-Y_MIN; y < niv->height; y++) piece->area[y][x] = 1;
        return piece;
    }

    // Variables >>>
    int ymax;
    int ydeb = 0, yfin = 0;
    int startx_plateforme, starty_plateforme = 0, finishy_plateforme = 0, len_plateforme, mod;
    int x_mystery, y_mystery, genere_mystery = 0;
    int startx_coin, x_coin = 0, y_coin = 0, nb_coin, compteur_coin = 0;
    int x_tuyaux, y_tuyaux;
    float x_goomba, y_goomba, speed_goomba;
    // <<< Variables

    // Aléatoire >>>
    int plateforme = (table[0] % 3) == 1;
    int coin = (table[0] % 2) == 1;
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
    int genere_coin_on_plateforme;
    if (plateforme) genere_coin_on_plateforme = table[startx_plateforme] % 2;
    if (coin) {
        startx_coin = abs(table[1]) % (DISTANCE - 3);
        mod = DISTANCE - x_coin - 3;
        if (mod <= 0) mod = 1;
        nb_coin = 3 + abs(table[x_coin]) % mod;
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
    for (int x = 0; x < DISTANCE; x++) {
        ymax = perlin(x, table, seed);

        if (x == 0) ydeb = ymax;
        if (x == DISTANCE - 1) yfin = ymax;

        if (x == 0) for (int y = niv->height-ymax; y < niv->height; y++) piece->area[y][x] = 2;
        else for (int y = niv->height-ymax; y < niv->height; y++) piece->area[y][x] = 1;
        // <<< Terrain

        // Plateforme >>>
        if (plateforme) {
            if (x == startx_plateforme) starty_plateforme = niv->height - ymax;
            if (x == startx_plateforme+len_plateforme) finishy_plateforme = niv->height - ymax;
        }
        // <<< Plateforme

        // Piece >>>
        if (coin && x >= startx_coin && compteur_coin < nb_coin) {
            x_coin = x;
            y_coin = niv->height - ymax - 1;
            if (piece->area[y_coin][x_coin] == 0) piece->area[y_coin][x_coin] = 4;
            compteur_coin++;
        }
        // <<< Piece

        // Goomba >>>
        if (!tuyau && x == x_goomba) {
            goomba = creerGoomba(id_chunk, (float)x_goomba, (float)(niv->height - ymax), speed_goomba);
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
        for (int x = startx_plateforme; x < startx_plateforme + len_plateforme; x++) piece->area[starty_plateforme][x] = 1;
        for (int i = startx_plateforme; i < startx_plateforme+len_plateforme; i++) {
            // Mystery >>>
            if (!genere_mystery && table[i] % 5 == 1) {
                x_mystery = i;
                y_mystery = starty_plateforme;
                piece->area[y_mystery][x_mystery] = 3;
                genere_mystery = 1;
            }
            // <<< Mystery
            // Piece >>>
            if (genere_coin_on_plateforme) {
                x_coin = i;
                y_coin = starty_plateforme - 1;
                piece->area[y_coin][x_coin] = 4;
            }
            // <<< Piece
        }
    // <<< Plateforme
    } else {
        // Tuyau >>>
        if (ydeb == yfin && tuyau) {
            x_tuyaux = abs(table[0] % (DISTANCE - 3));
            y_tuyaux = niv->height - ydeb - 1;
            piece->area[y_tuyaux][x_tuyaux] = 5;
            piece->area[y_tuyaux][x_tuyaux+1] = 6;
            piece->area[y_tuyaux][x_tuyaux+2] = 6;
            piece->area[y_tuyaux-1][x_tuyaux] = 6;
            piece->area[y_tuyaux-1][x_tuyaux+1] = 6;
            piece->area[y_tuyaux-1][x_tuyaux+2] = 6;
        }
        // <<< Tuyau
    }
    return piece;
}