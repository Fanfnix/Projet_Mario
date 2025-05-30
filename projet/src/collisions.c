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
        if (tmp_chunk->area[y_int + 1][pos_in_chunk] == 0 || tmp_chunk->area[y_int + 1][pos_in_chunk] == 4 || tmp_chunk->area[y_int + 1][pos_in_chunk] >= 7) return 0;
    }
    return 1;
}

int verifHaut(struct Map* niv, float x, float y, float vertical_speed) {
    if (niv == NULL) return -1;
    if (y <= 2) return 1;
    if (vertical_speed >= 0) return 1;

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
        if (tmp_chunk->area[y_int - 2][pos_in_chunk] == 3) {
            tmp_chunk->area[y_int - 2][pos_in_chunk] = 1;
            int proba = rand() % 5;
            if (proba == 0) tmp_chunk->area[y_int - 3][pos_in_chunk] = 7;
            else tmp_chunk->area[y_int - 3][pos_in_chunk] = 4   ;
            return 0;
        }
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
        if (tmp_chunk->area[y_int][pos_in_chunk] == 0 || tmp_chunk->area[y_int][pos_in_chunk] == 4 || tmp_chunk->area[y_int][pos_in_chunk] >= 7) return 0;
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
        if (tmp_chunk->area[y_int][pos_in_chunk] == 0 || tmp_chunk->area[y_int][pos_in_chunk] == 4 || tmp_chunk->area[y_int][pos_in_chunk] >= 7) return 0;
    }
    return 1;
}

void getCoin(struct Map* niv, float x, float y, int * coin, Mix_Chunk* coinSE) {
    if (niv == NULL) return;
    if (y <= 1) return;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return;
    if (tmp_chunk->id == id_chunk) {
        if (tmp_chunk->area[y_int][pos_in_chunk] == 4) {
            (*coin)++;
            tmp_chunk->area[y_int][pos_in_chunk] = 0;
            Mix_PlayChannel(-1, coinSE, 0);
        }
        else if (tmp_chunk->area[y_int - 1][pos_in_chunk] == 4) {
            (*coin)++;
            tmp_chunk->area[y_int-1][pos_in_chunk] = 0;
            Mix_PlayChannel(-1, coinSE, 0);
        }
    }
    return ;
}

void getLife(struct Map* niv, float x, float y, int* lifes, Mix_Chunk* powerupSE) {
    if (niv == NULL) return;
    if (y <= 1) return;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return;
    if (tmp_chunk->id == id_chunk) {
        if (tmp_chunk->area[y_int][pos_in_chunk] == 7) {
            (*lifes)++;
            tmp_chunk->area[y_int][pos_in_chunk] = 0;
            Mix_PlayChannel(-1, powerupSE, 0);
        }
        if (tmp_chunk->area[y_int-1][pos_in_chunk] == 7) {
            (*lifes)++;
            tmp_chunk->area[y_int-1][pos_in_chunk] = 0;
            Mix_PlayChannel(-1, powerupSE, 0);
        }
    }
    return;
}

void touchePlante(struct Map* niv, float x, float y, int* lifes, Mix_Chunk* degatSE, int pos_plantes, int* freeze_frames) {
    if (niv == NULL) return;
    if ((*freeze_frames) != 0) return;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int pos_in_chunk = x_int % DISTANCE;

    if (pos_in_chunk < 0 || pos_in_chunk > DISTANCE) return;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        if (tmp_chunk->id == id_chunk) break;
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return;
    if (tmp_chunk->id == id_chunk) {
        if ((tmp_chunk->area[y_int][pos_in_chunk] == 8 && pos_plantes >= 1) || (tmp_chunk->area[y_int][pos_in_chunk] == 9 && pos_plantes >= 2) || (tmp_chunk->area[y_int][pos_in_chunk] == 10 && pos_plantes >= 3)) {
            (*lifes)--;
            (*freeze_frames) = 60;
            Mix_PlayChannel(-1, degatSE, 0);
        }
    }
    return;
}

int surGoomba(struct Map* niv, float x, float y, int * goomba_tuee) {
    if (niv == NULL) return -1;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int mario_in_chunk = x_int % DISTANCE;

    if (mario_in_chunk < 0 || mario_in_chunk >= DISTANCE) return -1;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL && tmp_chunk->id != id_chunk) {
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return -1;

    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        struct Goomba* goomba = niv->liste_goomba[i];
        if (goomba == NULL) return 1;

        int x_goomba = convInt(goomba->x);
        int y_goomba = convInt(goomba->y);
        int id_chunk_goomba = x_goomba / DISTANCE;
        int goomba_in_chunk = x_goomba % DISTANCE;

        if (goomba_in_chunk < 0 || goomba_in_chunk >= DISTANCE) return -1;

        if (id_chunk_goomba == id_chunk && goomba_in_chunk == mario_in_chunk && y_goomba == y_int + 1) {
            (*goomba_tuee)++;
            supprimerGoomba(niv->liste_goomba, goomba->id);
            return 0;
        }
    }

    return 1;
}

void dansGoomba(struct Map* niv, float x, float y, int * lifes, Mix_Chunk* degatSE, int* freeze_frames) {
    if (niv == NULL) return;

    int x_int = convInt(x);
    int y_int = convInt(y);

    int id_chunk = x_int / DISTANCE;
    int mario_in_chunk = x_int % DISTANCE;

    if (mario_in_chunk < 0 || mario_in_chunk >= DISTANCE) return;

    struct Chunk* tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL && tmp_chunk->id != id_chunk) {
        tmp_chunk = tmp_chunk->suivant;
    }
    if (tmp_chunk == NULL) return;

    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        struct Goomba* goomba = niv->liste_goomba[i];
        if (goomba == NULL) return;

        int x_goomba = convInt(goomba->x);
        int y_goomba = convInt(goomba->y);
        int id_chunk_goomba = x_goomba / DISTANCE;
        int goomba_in_chunk = x_goomba % DISTANCE;

        if (goomba_in_chunk < 0 || goomba_in_chunk >= DISTANCE) return;

        if (id_chunk_goomba == id_chunk && goomba_in_chunk == mario_in_chunk && y_goomba == y_int && *freeze_frames == 0) {
            (*lifes)--;
            (*freeze_frames) = 60;
            Mix_PlayChannel(-1, degatSE, 0);
            return;
        }
    }
    return;
}