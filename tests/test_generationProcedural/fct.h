#ifndef TEST
#define TEST


// MAP : Création, affichage //
struct Map {
    int L;
    int l;
    char ** carte;
};

struct Map * creerMap(int L, int l);
void libMemMap(struct Map * niv);
void afficherMap(struct Map * niv);
void iterationMap(struct Map * niv, int x, int * table, int * seed, int version);


// MAP : Génération aléatoire //
#define DISTANCE 20
#define VARIANCE 6
#define Y_MIN 2

int * creerTableSeed(int * seed);
int * iterationTable(int * seed, int * table);
int rand_nb(int seed);
int perlin(int x, int * table, int * seed);

#endif