#ifndef GENERATION
#define GENERATION

#define DISTANCE 8  // Longueur de chaque pente
#define VARIANCE 5  // Variation dans les hauteurs générées
#define Y_MIN 1  // Hauteur minimale

#define H_PLATEFORME 4  // Hauteur plateformes

struct Goomba {
    int id;
    int X, Y;
    float x, y;
    float speed;
};

#define T_LISTE_GOOMBA 50

struct Chunk {
    int id;
    int height;
    int ** area;
};

struct Map {
    int height;
    int nb_chunks;
    struct Chunk ** carte;
    struct Goomba ** liste_goomba;
};

int * creerTableSeed();
int * iterationTable(int * seed, int * table);
int rand_nb(int seed);
int perlin(int x, int * table, int * seed);

struct Chunk * creerChunk(int id, int height);
void libMemChunk(struct Chunk * piece);
void ajouterChunk(struct Map * niv, struct Chunk * piece);

struct Map * creerMap(int height, int nb_chunks);
void libMemMap(struct Map * niv);

struct Goomba * creerGoomba(int id, float x, float y, float speed);
int ajouterGoomba(struct Goomba ** liste_goomba, struct Goomba * machin);
int supprimerGoomba(struct Goomba ** liste_goomba, int id);

struct Chunk * genererChunk(struct Map * niv, int id_chunk, int * table, int * seed);

#endif