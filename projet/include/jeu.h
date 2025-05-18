#ifndef JEU
#define JEU

#define GRAVITE 0.075f

typedef struct  Mario {
    int id;
    float x, y;
    float vertical_speed;
} Mario;

void lancerPartie(Mix_Music* menuzik, Save * partie);

void actionGoombas(struct Map * niv);

struct Mario * creerMario();
void initMario(Mario * perso, struct Map * niv);
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

void touchePlante(struct Map* niv, float x, float y, int* lifes, Mix_Chunk* degatSE, int pos_plantes, int* freeze_frames);

void dansGoomba(struct Map* niv, float x, float y, int * lifes, Mix_Chunk* degatSE, int* freeze_frames);
int surGoomba(struct Map* niv, float x, float y, int * goomba_tuee);

int calculScore(int dmax, int coin, int goomba_tuee);

void checkpoint(Mario * perso, struct Save * checkpoint);

int actions_menu(WIN* pause, WIN* jeu, Mix_Chunk* selectSE);

#endif