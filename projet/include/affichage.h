#ifndef AFFICHAGE
#define AFFICHAGE

#define TX 3
#define TY 2

void afficherMap(WIN * fenetre, struct Map * niv);
void afficherMap_simp(WIN * fenetre, struct Map * niv);
void afficherTmp(WIN * tmp, int X, int Y, int dMax, int * table, int seed);

#endif