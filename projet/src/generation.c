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

// Creer un chunk
struct Chunk * creerChunk(int id, int height) {
    struct Chunk * piece = malloc(sizeof(struct Chunk));
    if (piece == NULL) return NULL;
    piece->id = id;
    piece->height = height;
    piece->area = malloc(height * sizeof(int *));
    piece->suivant = NULL;
    if (piece->area == NULL) {
        free(piece);
        return NULL;
    }
    for (int y = 0; y < height; y++) {
        piece->area[y] = malloc(DISTANCE * sizeof(int));
        if (piece->area[y] != NULL) for (int x = 0; x < DISTANCE; x++) piece->area[y][x] = 0;
    }
    return piece;
}


// Libère un chunk
void libMemChunk(struct Chunk * piece) {
    if (piece == NULL) return;
    for (int y = 0; y < piece->height; y++) {
        free(piece->area[y]);
        piece->area[y] = NULL;
    }
    free(piece->area);
    piece->area = NULL;
    free(piece);
    piece = NULL;
}


// Ajoute le chunk a la carte
void ajouterChunk(struct Map * niv, struct Chunk * piece) {
    if (niv == NULL || piece == NULL) return;
    if (niv->p_chunk == NULL) niv->p_chunk = piece;
    struct Chunk * tmp_first = niv->p_chunk;
    while (tmp_first->suivant != NULL) {
        tmp_first = tmp_first->suivant;
    }
    tmp_first->suivant = piece;
    return;
}


// Creer la Map
struct Map * creerMap(int height, int nb_chunks) {
    struct Map * niv = malloc(sizeof(struct Map));
    if (niv == NULL) return NULL;
    niv->height = height;
    niv->nb_chunks = nb_chunks;
    niv->p_chunk = NULL;
    niv->partie = NULL;
    niv->flag = NULL;
    niv->liste_goomba = malloc(T_LISTE_GOOMBA * sizeof(struct Goomba *));
    if (niv->liste_goomba == NULL) {
        free(niv);
        return NULL;
    }
    for (int i = 0; i < T_LISTE_GOOMBA; i++) niv->liste_goomba[i] = NULL;
    return niv;
}


// Libère la Map
void libMemMap(struct Map * niv) {
    if (niv == NULL) {
        endwin();
        printf("ERR [libMemMap] : niv == NULL\n");
        return;
    }
    if (niv->p_chunk == NULL) {
        endwin();
        printf("ERR [libMemMap] : niv->p_chunk == NULL\n");
        return;
    }
    struct Chunk * tmp_chunk = NULL;
    for (int i = 0; i < T_LISTE_GOOMBA; i++) if (niv->liste_goomba[0] != NULL) supprimerGoomba(niv->liste_goomba, niv->liste_goomba[0]->id);
    while (niv->p_chunk->suivant != NULL) {
        tmp_chunk = niv->p_chunk->suivant;
        libMemChunk(niv->p_chunk);
        niv->p_chunk = tmp_chunk;
    }
    free(niv->flag);
    niv->flag = NULL;
    free(niv);
}


/* === GOOMBA === */

// Creer Goomba
struct Goomba * creerGoomba(int id, float x, float y, float speed) {
    struct Goomba * machin = malloc(sizeof(struct Goomba));
    if (machin == NULL) return NULL;
    machin->id = id;
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


/* === DRAPEAU === */

// Creer Drapeau
struct Drapeau * creerDrapeau(int x, int y) {
    struct Drapeau * flag = malloc(sizeof(struct Drapeau));
    if (flag == NULL) return NULL;
    flag->x = x;
    flag->y = y;
    flag->frame = 1;
}