#include "../include/header.h"

void avancerMapChunk(struct Map * niv, int * table, int * seed){

    if (niv == NULL) return;
    
    libMemChunk(niv->carte [0]);
    for (int i = 0; i < niv->nb_chunks; i++){
        niv->carte [i]= niv->carte [i+1];
        niv->carte [i+1] = NULL;
    }
    struct Chunk * newChunk = genererChunk(niv, niv->carte [niv->nb_chunks - 2]->id, table, seed);
    ajouterChunk(niv, newChunk);
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
        if (tmp_chunk->area[j][convint(perso->x)] == 1 || tmp_chunk->area[j][convint(perso->x)] == 2)
        {
            perso->x = tmp_chunk->height - j;
            break;
        }     
    }
}