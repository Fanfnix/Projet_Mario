#ifndef AFFICHAGE
#define AFFICHAGE

#define TX 3
#define TY 2

void afficherMap(WINDOW * fenetre, struct Map * niv, int height_carte, int width_carte);
void afficherMap_simp(WINDOW* fenetre, struct Map* niv, int height_carte, int width_carte);
void afficherTmp(WINDOW* tmp, int X, int Y, int dMax, int* table, int seed);

#endif