#include "../include/header.h"

int verifSol(struct Map* niv, float x, float y) {
    if (niv == NULL) return -1;

    if (y <= 2) y = 2;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return -1;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return -1;
    if (tmp_chunk->id == id_chunk) {
        if ((y_int + 1) >= niv->height) y = (float)(niv->height - 1);
        if (tmp_chunk->area[y_int + 1][pos_in_chunk] == 0 || tmp_chunk->area[y_int + 1][pos_in_chunk] == 4) return 0;
    }
    return 1;
}

int verifDroite(struct Map* niv, float x, float y) {
    if (niv == NULL) return -1;

    int x_int = convInt(x) + 1;
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return -1;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return -1;
    if (tmp_chunk->id == id_chunk) {
        if (tmp_chunk->area[y_int][pos_in_chunk] == 0 || tmp_chunk->area[y_int][pos_in_chunk] == 4) return 0;
    }
    return 1;
}

int verifGauche(struct Map* niv, float x, float y) {
    if (niv == NULL) return -1;

    int x_int = convInt(x) - 1;
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return -1;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return -1;
    if (tmp_chunk->id == id_chunk) {
        if (tmp_chunk->area[y_int][pos_in_chunk] == 0 || tmp_chunk->area[y_int][pos_in_chunk] == 4) return 0;
    }
    return 1;
}