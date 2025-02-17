#include "fct.h"


/* UTILITAIRES */

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

/* MAP : Génération aléatoire */

// Pour les iterations de la seed
int f(int x) {
    return (16807 * x) % 2147483646;
}

void iterationSeed(int * seed) {
    *seed = f(*seed);
}

// Pour le lissage et l'interpolaion de la fonction de lissage
float lissage(float x) {
    return 3 * pow(x, 2) - 2 * pow(x, 3);
}

float interpolate(int y_prec, int y_suiv, int x) {
    return (y_suiv - y_prec) * lissage((float)(x % DISTANCE) / DISTANCE) + y_prec;
}

// Pour la table de valeur aléatoire : création et itération
int * creerTableSeed(int * seed) {
    int * table = malloc(DISTANCE*sizeof(int));
    return table;
}

int * iterationTable(int * seed, int * table) {
    for (int i = 0; i < DISTANCE; i++) {
        table[i] = *seed;
        iterationSeed(seed);
    }
    return table;
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
        int y_prec = (abs(table[0] / 100000000) % VARIANCE) + Y_MIN;
        return y_prec;
    }
    else {
        int y_prec = (abs(table[0] / 100000000) % VARIANCE) + Y_MIN;
        int y_suiv = (abs(f(table[DISTANCE-1]) / 100000000) % VARIANCE) + Y_MIN;

        int y = convInt(interpolate(y_prec, y_suiv, x));

        return y;
    }
}


/* MAP : Création, affichage */

// Creer la Map
struct Map * creerMap(int height, int width) {
    struct Map * niv = malloc(sizeof(struct Map));
    if (!niv) {return NULL;}
    niv->height = height;
    niv->width = width;
    
    niv->carte = malloc(height * sizeof(char *));
    if (!niv->carte) {
        free(niv);
        return NULL;
    }
    
    for (int y = 0; y < height; y++) {
        niv->carte[y] = malloc(width * sizeof(char));
        if (!niv->carte[y]) {
            for (int j = 0; j < y; j++) free(niv->carte[j]);
            free(niv->carte);
            free(niv);
            return NULL;
        }
        memset(niv->carte[y], '0', width);
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

// Affichage Map
void afficherMap(WINDOW * fenetre, struct Map * niv) {
    char ch[TX+1];
    for (int y = 0; y < niv->height; y++) {
        for (int i = 0; i < 2; i++) {
            for (int x = 0; x < niv->width; x++) {
                switch (niv->carte[y][x]) {
                    case '0': strcpy(ch, "   "); break;
                    case '#': strcpy(ch, "###"); break;
                    case 'O': strcpy(ch, "OOO"); break;
                    default: strcpy(ch, "???"); break;
                }
                mvwaddstr(fenetre, TY*y+i+1, TX*x+1, ch);
            }
        }
    }
}

void afficherMap_simp(WINDOW * fenetre, struct Map * niv) {
    for (int y = 0; y < niv->height; y++) {
        for (int x = 0; x < niv->width; x++) {
            if (niv->carte[y][x] == '0') {
                mvwaddch(fenetre, y + 1, x + 1, ' ');
            } else {
                mvwaddch(fenetre, y + 1, x + 1, niv->carte[y][x]);
            }
        }
    }
}

// Génére un tronçon de la map
int iterationMap(struct Map * niv, int X, int dMax, int * table, int * seed, int version) {
    int y, x;
    switch (version) {
        case 1: y = perlin(X, table, seed); break;
        case 0: y = 5; break;
    }

    if (y < 0 || y >= niv->height) {
        printf("ERR M1 : Y = %d\n", y);
    }
    else {
        x = X - dMax;
        for (int i = niv->height - 1; i >= 0; i--) {
            if (i >= niv->height - y) {
                if (X % DISTANCE == 0) {
                    niv->carte[i][x] = 'O';
                } else {
                    niv->carte[i][x] = '#';
                }
            } else {
                niv->carte[i][x] = '0';
            }
        }
    }
    return y;
}

int avancerMap(struct Map * niv, int X, int dMax, int * table, int * seed, int version) {
    int Y;
    for (int y = 0; y < niv->height; y++) {
        for (int x = 1; x < niv->width; x++) {
            niv->carte[y][x-1] = niv->carte[y][x];
        }
    }
    Y = iterationMap(niv, X, dMax, table, seed, version);
    return Y;
}

void afficherTmp(WINDOW * tmp, int X, int Y, int dMax, int * table, int seed) {
    wborder(tmp, '|', '|', '-', '-', '+', '+', '+', '+');
    char elem1[255], elem2[255], elem3[255], elem4[255];
    int x = X - dMax;
    
    snprintf(elem1, 255, "X = %d", X);
    snprintf(elem2, 255, "dMax = %d", dMax);
    snprintf(elem3, 255, "x = %d", x);
    snprintf(elem4, 255, "Y = %d", Y);
    
    mvwaddstr(tmp, 1, 1, elem1);
    mvwaddstr(tmp, 2, 1, elem4);
    mvwaddstr(tmp, 3, 1, elem2);
    mvwaddstr(tmp, 4, 1, elem3);
	
    wrefresh(tmp);
}

void affichageElem(WINDOW * win, struct Elem truc, int dMax) {
    char chemin[255];

    snprintf(chemin, 255, "../../design/%s/%s%d.txt", truc.nom, truc.nom, truc.nb_frame);

    FILE * file = fopen(chemin, "r");

    for (int j = 0; j < truc.height * TY; j++) {
        char tmp[255];
        fgets(tmp, truc.width*TX+1, file);

        for (int k = 0; k < strlen(tmp); k++) {
            if (tmp[k] == '0') {
                tmp[k] = ' ';
            }
        }
        int x = 1 + (truc.x - dMax) * TX;
        int y = 1 + (truc.y - truc.height) * TY + j;
        mvwaddstr(win, y, x, tmp);
    }
    wrefresh(win);
    fclose(file);
}