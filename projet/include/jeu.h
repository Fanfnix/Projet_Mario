#ifndef JEU
#define JEU

#define GRAVITE 0.10 

typedef struct  Mario {
    int id;
    int X, Y;
    float x, y;
    float speed;
    float vertical_speed;
    int vies;
} Mario;

void lancerPartie(Mix_Music* menuzik);
void actionGoombas(struct Map * niv);

struct Mario * creerMario(int vies, float speed, float vertical_speed);
void initMario(Mario * perso, struct Map * niv, WIN * fenetre);
void avancerMapChunk(struct Map * niv, int * table, int * seed);
void affichageMario(WIN * win, Mario * perso);
int avancerMap(struct Map * niv, int * table, int * seed, int decal);
void sautMario(Mario * perso, struct Map *niv);
void actionMario(Mario * perso, struct Map * niv);

#endif