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
