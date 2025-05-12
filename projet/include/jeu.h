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
<<<<<<< HEAD
void affichageMario(WIN * win, Mario * perso);
=======
void affichageMario(WIN * win, Mario * perso);
int avancerMap(struct Map * niv, int * table, int * seed, int decal);
>>>>>>> 178430e (deplacement map)

#endif