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
        res = res / 100;
    }
    return res;
}


/* === GENERATION === */

/* Gestion seed */

// Pour les iterations de la seed
int f(int x) {
    return rand_r(&x);
}


int iterationSeed(int * seed) {
    return f(*seed);
}

/* Table aléatoire */

// Pour la table de valeur aléatoire : création et itération
int * creerTableSeed() {
    int * table = malloc(DISTANCE*sizeof(int));
    return table;
}


int * iterationTable(int * seed, int * table) {
    for (int i = 0; i < DISTANCE; i++) {
        table[i] = *seed;
        *seed = iterationSeed(seed);
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
int perlin(int x, int * table, int * seed) {
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
        int copy_suiv = table[DISTANCE-1];
        int y_suiv = (abs(f(copy_suiv)) % VARIANCE) + Y_MIN;

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
    niv->liste_goomba = malloc(T_LISTE_GOOMBA * sizeof(struct Goomba *));
    if (niv->liste_goomba == NULL) {
        for (int y = 0; y < niv->height; y++) free(niv->carte[y]);
        free(niv->carte);
        free(niv);
        return NULL;
    }
    return niv;
}


// Libère la Map
void libMemMap(struct Map * niv) {
    if (!niv) return;
    for (int y = 0; y < niv->height; y++) {
        free(niv->carte[y]);
    }
    free(niv->carte);
    free(niv);
}


/* === GOOMBA === */

// Creer Goomba
struct Goomba * creerGoomba(int id, float x, float y, float speed) {
    struct Goomba * machin = malloc(sizeof(struct Goomba));
    if (machin == NULL) return NULL;
    machin->id = id;
    machin->X = convInt(x);
    machin->Y = convInt(y);
    machin->x = x;
    machin->y = y;
    machin->speed = speed;
    return machin;
}

// Ajouter un goomba à la liste
int ajouterGoomba(struct Goomba ** liste_goomba, struct Goomba * machin) {
    if (liste_goomba == NULL || machin == NULL) return 0;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (liste_goomba[i] == NULL) {
            liste_goomba[i] = machin;
            return 1;
        }
    }
    return 0;
}

// Supprimer un goomba de la liste
int supprimerGoomba(struct Goomba ** liste_goomba, int id) {
    if (liste_goomba == NULL) return 0;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (liste_goomba[i] != NULL) if (liste_goomba[i]->id == id) {
            free(liste_goomba[i]);
            liste_goomba[i] == NULL;
            for (int j = i+1; j < T_LISTE_GOOMBA; j++) {
                liste_goomba[j-1] = liste_goomba[j];
                if (liste_goomba[j-1] == NULL) break;
            }
            return 1;
        }
    }
    return 0;
}