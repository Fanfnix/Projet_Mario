#include "header.h"

/* ========== Affichage tabElem ========== */

char * affichageElem(char * txt, struct Element * elem) {
    sprintf(txt, "%s | L=%d, H=%d | X=%d, Y=%d | NBF=%d", elem->nom, elem->largeur, elem->hauteur, elem->x, elem->y, elem->nb_frames);
    return txt;
}

void affichageTabElem(struct Element ** tabElem, int size) {
    char txt[100];
    for (int i = 0; i < size; i++) {
        if (tabElem[i] != NULL) printf("%s\n", affichageElem(txt, tabElem[i]));
    }
}

/* ========== Création et manipulation tabElem ========== */

struct Element * creerElem(char * nom, int largeur, int hauteur, int x, int y, int nb_frames) {
    struct Element * elem = malloc(sizeof(struct Element));
    strcpy(elem->nom, nom);
    elem->largeur = largeur;
    elem->hauteur = hauteur;
    elem->x = x;
    elem->y = y;
    elem->nb_frames = nb_frames;
    return elem;
}

struct Element * randomElem() {
    int y = 2 + (rand() % 6);
    int x = rand() % 3;
    switch(rand() % 4) {
        case 0: return creerElem("drapeau", 1, 5, x, y, 7);
        case 1: return creerElem("goomba", 1, 1, x, y, 2);
        case 2: return creerElem("plante", 1, 3, x, y, 4);
        case 3: return creerElem("tuyau", 3, 3, x, y, 1);
        default: return NULL;
    }
}

struct Element ** creerTabElem(int size) {
    struct Element ** tabElem = malloc(size * sizeof(struct Element *));
    for (int i = 0; i < size; i++) {
        tabElem[i] = NULL;
    }
    return tabElem;
}

void libTabElem(struct Element ** tabElem, int size) {
    for (int i = 0; i < size; i++) {
        if (tabElem[i] != NULL) {
            free(tabElem[i]);
            tabElem[i] = NULL;
        }
    }
    free(tabElem);
    tabElem = NULL;
}

int ajouterElem(struct Element ** tabElem, int size, struct Element * elem) {
    if (tabElem == NULL) return 0;
    for (int i = 0; i < size; i++) {
        if (tabElem[i] == NULL) {
            tabElem[i] = elem;
            return (tabElem[i] == NULL) ? 0 : 1;
        }
    }
    return 0;
}

void supprElem(struct Element ** tabElem, int X) {
    for (int i = 0; tabElem[i] != NULL; i++) {
        tabElem[i]->x++;
        if (tabElem[i]->x >= X) {
            free(tabElem[i]);
            tabElem[i] = NULL;
            for (int j = i+1; tabElem[j] != NULL; j++) {
                tabElem[j-1] = tabElem[j];
                tabElem[j] = NULL;
            }
        }
    }
}

/* ====================================================== */