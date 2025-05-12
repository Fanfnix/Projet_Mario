#ifndef JEU
#define JEU


typedef struct  Mario {
    int id;
    int X, Y;
    float x, y;
    float speed;
    int vies;
} Mario;

void lancerPartie();

struct Mario * creerMario(float speed, int vies);
void initMario(Mario * perso, struct Map * niv, WIN * fenetre);
void avancerMapChunk(struct Map * niv, int * table, int * seed);
void affichageMario(WIN * win, Mario * perso);

#endif