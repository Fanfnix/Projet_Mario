#ifndef JEU
#define JEU


typedef struct  Mario {
    int id;
    int X, Y;
    float x, y;
    float speed;
    int vies;
} Mario;

struct Mario * creerMario(int id, float x, float y, float speed, int vies);
void initMario(Mario * perso, struct Map *niv, WIN * fenetre);
void avancerMapChunk(struct Map * niv, int * table, int * seed);


#endif