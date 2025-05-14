#include "../include/header.h"


void avancerMapChunk(struct Map * niv, int * table, int * seed){
    if (niv == NULL) {
        endwin();
        printf("ERR [avancerMapChunk] : niv == NULL\n");
        return;
    }

    if (niv->p_chunk == NULL) {
        endwin();
        printf("ERR [avancerMapChunk] : niv->p_chunk == NULL\n");
        return;
    }

    struct Chunk * a_suppr = niv->p_chunk;
    niv->p_chunk = niv->p_chunk->suivant;
    libMemChunk(a_suppr);

    struct Chunk * tmp_chunk = niv->p_chunk;
    tmp_chunk->id--;
    while (tmp_chunk->suivant != NULL) {
        tmp_chunk = tmp_chunk->suivant;
        tmp_chunk->id--;
    }

    struct Chunk * newChunk = genererChunk(niv, tmp_chunk->id+1, table, seed);
    if (newChunk == NULL) {
        endwin();
        printf("ERR [avancerMapChunk] : newChunk == NULL\n");
        return;
    }

    if (newChunk != NULL) tmp_chunk->suivant = newChunk;

    return;
}

int avancerMap(struct Map * niv, int * table, int * seed, int decal) {
    decal = (decal + 1) % DISTANCE;
    if (decal == 0) avancerMapChunk(niv, table, seed);
    if (niv->liste_goomba == NULL) return decal;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (niv->liste_goomba[i] != NULL) {
            niv->liste_goomba[i]->x--;
        }
    }
    return decal;
}


struct Mario * creerMario(float speed, int vies) {
    struct Mario * perso = malloc(sizeof(struct Mario));
    if (perso == NULL) return NULL;
    perso->id = 0;
    perso->speed = speed;
    perso->vies= 3;
    return perso;
}

void initMario(Mario * perso, struct Map * niv, WIN * fenetre){
    if (perso == NULL || niv == NULL || fenetre == NULL) return;
    perso->x = 5;
    int id_chunk = perso->x / DISTANCE;
    struct Chunk * tmp_chunk = niv->p_chunk;
    for (int i = 0; i < id_chunk; i++)
    {
        tmp_chunk = tmp_chunk->suivant;
    }
    for (int j = 0; j < tmp_chunk->height; j++)
    {
        if (tmp_chunk->area[j][convInt(perso->x)] == 1 || tmp_chunk->area[j][convInt(perso->x)] == 2)
        {
            perso->x = tmp_chunk->height + j;
            break;
        }     
    }
}


void actionGoombas(struct Map * niv) {
    if (niv == NULL) return;
    if (niv->liste_goomba == NULL) return;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (niv->liste_goomba[i] != NULL) {
            int new_pos_x = niv->liste_goomba[i]->x + niv->liste_goomba[i]->speed * SPEED_GOOMBA;
            int id_chunk = new_pos_x / DISTANCE;
            struct Chunk * tmp_chunk = niv->p_chunk;
            for (int j = 0; j < id_chunk; j++) tmp_chunk = tmp_chunk->suivant;
            // int bloc = tmp_chunk->area[convInt(niv->liste_goomba[i]->y)][convInt(new_pos_x) % DISTANCE];
            // if (bloc == 1 || bloc == 2 || bloc == 3 || bloc == 5 || bloc == 6 || new_pos_x == -1) {
            //     niv->liste_goomba[i]->speed = (niv->liste_goomba[i]->speed < 0) ? 1.0f : -1.0f;
            //     new_pos_x = niv->liste_goomba[i]->x + niv->liste_goomba[i]->speed * SPEED_GOOMBA;
            // }
            niv->liste_goomba[i]->x = new_pos_x;
        }
    }
}