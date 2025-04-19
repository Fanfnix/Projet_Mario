#include "../include/header.h"


/* === UTILITAIRES === */

int convInt(float y) {
    /* #######################################################
        convInt(float y)

    PARAMETRE :
        float y : valeur a convertir en int

    RETOUR :
        int : valeur converti en entier

    DESCRIPTION :
        Renvoie la valeur entière arrondie
    
    EXEMPLE :
        convInt(8.7483)
        >>> 9
    ####################################################### */
    float tmp = y * 100;
    int res = (int)tmp;
    if (y > res / 100 + 0.5) {
        res = res / 100 + 1;
    } else {
        res =  res / 100;
    }
    return res;
}


/* === GENERATION === */

/* Gestion seed */

// Pour les iterations de la seed
int f(int x) {
    return (int)((x * x) / 100);
}


void iterationSeed(int* seed) {
    *seed = f(*seed);
}

/* Table aléatoire */

// Pour la table de valeur aléatoire : création et itération
int * creerTableSeed() {
    int * table = malloc(DISTANCE*sizeof(int));
    return table;
}


int * iterationTable(int* seed, int* table) {
    for (int i = 0; i < DISTANCE; i++) {
        table[i] = *seed;
        iterationSeed(seed);
    }
    return table;
}

/* Perlin */

// Pour le lissage et l'interpolaion de la fonction de lissage
float lissage(float x) {
    return 3 * pow(x, 2) - 2 * pow(x, 3);
}


float interpolate(int y_prec, int y_suiv, int x) {
    return (y_suiv - y_prec) * lissage((float)(x % DISTANCE) / DISTANCE) + y_prec;
}


// Génére le relief
int perlin(int x, int* table, int* seed) {
    /* #######################################################
        perlin(int x, int * table, int * seed)

    PARAMETRE :
        int x : valeur x où la valeur de hauteur doit être généré
        int * table : pointeur vers la table de valeur aléatoire
        int * seed : pointeur vers la seed

    RETOUR :
        int : valeur de la hauteur généré

    DESCRIPTION :
        Génére une valeur de hauteur avec la méthode du bruit
        de perlin. La valeur généré sera comprise entre la
        valeur minimale (Y_MIN) et la la valeur minimale plus
        la variance (Y_MIN + VARIANCE).
    
    EXEMPLE :
        convInt(0, table, seed)
        >>> 4
    ####################################################### */
    if (x % DISTANCE == 0) {
        table = iterationTable(seed, table);
        int y_prec = (abs(table[0]) % VARIANCE) + Y_MIN;
        return y_prec;
    }
    else {
        int y_prec = (abs(table[0]) % VARIANCE) + Y_MIN;
        int y_suiv = (abs(f(table[DISTANCE-1])) % VARIANCE) + Y_MIN;

        int y = convInt(interpolate(y_prec, y_suiv, x));

        return y;
    }
}


/* === MAP === */

// Creer la Map
struct Map * creerMap(int height, int width) {
    struct Map * niv = malloc(sizeof(struct Map));
    if (!niv) {return NULL;}
    width = (width / DISTANCE + 2) * DISTANCE;
    niv->height = height;
    niv->width = width;
    
    niv->carte = malloc(niv->height * sizeof(int *));
    if (!niv->carte) {
        free(niv);
        return NULL;
    }
    
    for (int y = 0; y < niv->height; y++) {
        niv->carte[y] = malloc(niv->width * sizeof(int));
        if (!niv->carte[y]) {
            for (int j = 0; j < y; j++) free(niv->carte[j]);
            free(niv->carte);
            free(niv);
            return NULL;
        }
        for (int x = 0; x < niv->width; x++) niv->carte[y][x] = 0;
    }
    return niv;
}


// Libère la Map
void libMemMap(struct Map* niv) {
    if (!niv) return;
    for (int y = 0; y < niv->height; y++) {
        free(niv->carte[y]);
    }
    free(niv->carte);
    free(niv);
}