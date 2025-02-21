#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// DRAPEAU : drapeau, 7, 3, 10
// GOOMBA : goomba, 2, 3, 2
// MARIO : mario, 3, 3, 8
// PLANTE : plante, 4, 3, 6
// TUYAU : tuyau, 1, 9, 4

struct Element {
    char nom[20];
    int largeur, hauteur;
    int x, y;
    int nb_frames;
};

struct Element * creerElem(char * nom, int largeur, int longueur, int x, int y, int nb_frames);
struct Element * randomElem();
char * affichageElem(char * txt, struct Element * elem);

struct Element ** creerTabElem(int size);
void libTabElem(struct Element ** tabElem, int size);
int ajouterElem(struct Element ** tabElem, int size, struct Element * elem);
void supprElem(struct Element ** tabElem, int X);

void affichageTabElem(struct Element ** tabElem, int size);

#endif