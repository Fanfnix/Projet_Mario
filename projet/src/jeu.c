#include "../include/header.h"

void avancerMapChunk(struct Map * niv, int nb_chunk){

    if (niv == NULL) return;
    
    libMemChunk(niv->carte [0]);
    for (int i = 0; i < niv->nb_chunks; i++){
        niv->carte [i]= niv->carte [i+1];
        niv->carte [i+1] = NULL;
    }
    struct Chunk * newChunk = genererChunk(struct Map * niv, int id_chunk, int * table, int * seed);
    ajouterChunk(struct Map * niv, struct Chunk * newChunk);
}
