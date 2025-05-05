#ifndef HEADER
#define HEADER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL_mixer.h>

#include <ncurses.h>

typedef struct WIN {
    int width, height;
    WINDOW * fenetre;
} WIN;

#include "generation.h"
#include "affichage.h"
#include "menu.h"
#include "jeu.h"

#endif