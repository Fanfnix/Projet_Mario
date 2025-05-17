#ifndef JEU
#define JEU

#define GRAVITE 0.075f

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
void affichageMario(WIN * win, Mario * perso, int dmax);
void actionMario(Mario * perso, struct Map * niv);
void libMario(Mario * perso);

void afficherMap_simp(WIN * fenetre, struct Map * niv, Mario * perso, int dmax);

void avancerMapChunk(struct Map * niv, int * table, int * seed);

int verifSol(struct Map * niv, float x, float y);
int verifHaut(struct Map* niv, float x, float y, float vertical_speed);
int verifDroite(struct Map * niv, float x, float y);
int verifGauche(struct Map* niv, float x, float y);
void getCoin(struct Map* niv, float x, float y, int * coin, Mix_Chunk* coinSE);
void getLife(struct Map* niv, float x, float y, int* lifes, Mix_Chunk* powerupSE);
int surGoomba(struct Map* niv, float x, float y);
void checkpoint(Mario * perso, struct Save * checkpoint);

#endif