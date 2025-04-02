#ifndef GENERATION
#define GENERATION

#define DISTANCE 8  // Longueur de chaque pente
#define VARIANCE 5  // Variation dans les hauteurs générées
#define Y_MIN 1  // Hauteur minimale

#define H_PLATEFORME 4  // Hauteur plateformes

struct Map {
    int height, width;
    int** carte;
};

struct Elem {
    char nom[20];
    int nb_frames;
    int height, width;
    int x, y;
};

int * creerTableSeed();
int * iterationTable(int* seed, int* table);
int rand_nb(int seed);
int perlin(int x, int* table, int* seed);

struct Map* creerMap(int L, int l);
void libMemMap(struct Map* niv);

void genererChunk(struct Map* niv, int id_chunk, int* table, int* seed);

#endif