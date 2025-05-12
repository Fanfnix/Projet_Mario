#ifndef AFFICHAGE
#define AFFICHAGE

#define TX 3
#define TY 2

void afficherChunk(WIN * fenetre, struct Chunk * troncon, int decal);

void afficherMap(WIN * fenetre, struct Map * niv, int decal);
void afficherMap_simp(WIN * fenetre, struct Map * niv);
void afficherTmp(WIN * tmp, int X, int Y, int dMax, int * table, int seed);

#endif