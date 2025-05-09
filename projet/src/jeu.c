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

struct Mario * creerMario(int id, float x, float y, float speed, int vies) {
    struct Mario * perso = malloc(sizeof(struct Mario));
    if (perso == NULL) return NULL;
    perso->id = id;
    perso->X = convInt(x);
    perso->Y = convInt(y);
    perso->x = x;
    perso->y = y;
    perso->speed = speed;
    perso->vies=vies;
    return perso;
}

void initMario(Mario * perso, struct Map *niv){
    perso->X = 5;
    
}
niv coord x y jusqua bloc -1 cast int a float

