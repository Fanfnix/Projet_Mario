#ifndef AFFICHAGE
#define AFFICHAGE

#define TX 3
#define TY 2

void afficherChunk(WIN* fenetre, struct Chunk* troncon, int dmax, int pos_plantes);

void afficherMap(WIN* fenetre, struct Map* niv, int dmax, int pos_plantes);
void afficherTmp(WIN * tmp, int X, int Y, int dMax, int * table, int seed);

#endif