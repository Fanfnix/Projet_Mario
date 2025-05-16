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
    while (tmp_chunk->suivant != NULL) tmp_chunk = tmp_chunk->suivant;

    struct Chunk * newChunk = genererChunk(niv, tmp_chunk->id+1, table, seed);
    if (newChunk == NULL) {
        endwin();
        printf("ERR [avancerMapChunk] : newChunk == NULL\n");
        return;
    }

    if (newChunk != NULL) tmp_chunk->suivant = newChunk;

    return;
}


struct Mario * creerMario(int vies, float speed, float vertical_speed) {
    struct Mario * perso = malloc(sizeof(struct Mario));
    if (perso == NULL) return NULL;
    perso->id = 0;
    perso->speed = speed;
    perso->vertical_speed = vertical_speed;
    perso->vies= 3;
    return perso;
}

void initMario(Mario * perso, struct Map * niv, WIN * fenetre){
    if (perso == NULL || niv == NULL || fenetre == NULL) return;
    perso->x = 1.0f;
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
            perso->y = j-1;
            break;
        }
    }
}


void actionGoombas(struct Map * niv) {
    if (niv == NULL) return;
    if (niv->liste_goomba == NULL) return;
    struct Goomba * machin;
    int bloc;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        machin = niv->liste_goomba[i];
        if (machin != NULL) {
            float new_pos_x = machin->x + machin->speed * SPEED_GOOMBA;
            int id_chunk = new_pos_x / DISTANCE;
            int pos_in_chunk = convInt(new_pos_x) % DISTANCE;
            struct Chunk * tmp_chunk = niv->p_chunk;

            while (tmp_chunk->suivant != NULL) {
                if (tmp_chunk->id == id_chunk) break;
                tmp_chunk = tmp_chunk->suivant;
            }
            if (tmp_chunk->id == id_chunk) {
                if (convInt(machin->x) <= niv->p_chunk->id * DISTANCE) {
                    supprimerGoomba(niv->liste_goomba, machin->id);
                    continue;
                }
                if (verifSol(niv, machin->x, machin->y) == 0) machin->y += 1.0f;
                bloc = tmp_chunk->area[convInt(machin->y)][pos_in_chunk];
                if (bloc == 1 || bloc == 2 || bloc == 3 || bloc == 5 || bloc == 6) {
                    machin->speed = (machin->speed < 0) ? 1.0f : -1.0f;
                    new_pos_x = machin->x + machin->speed * SPEED_GOOMBA;
                }
                machin->x = new_pos_x;
            }
        }
    }
}

void actionMario(Mario * perso, struct Map * niv){
    if (perso == NULL || niv == NULL) return;
    if (perso->y <= 2) {
        perso->y = 2.0f;
        perso->vertical_speed = 0.0f;
    }
    if (verifSol(niv, perso->x, perso->y) == 1) {
        perso->vertical_speed = 0.0f;
        perso->y = convInt(perso->y);
    }
    perso->vertical_speed += GRAVITE;
    perso->y += perso->vertical_speed;
}


void libMario(Mario * perso) {
    free(perso);
    perso == NULL;
}

void checkpoint(Mario * perso, struct Save * checkpoint){
    if(perso == NULL || checkpoint == NULL) return ;

    checkpoint->posx = perso->x;
    checkpoint->posy = perso->y;
    // checkpoint->score = score;
    checkpoint->vies = perso->vies;
     
}