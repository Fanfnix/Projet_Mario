#ifndef HEADER
#define HEADER

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#if __linux__
    #include <ncurses.h>

#elif _WIN32
    #include <conio.h>
    typedef struct WINDOW {
        int LINES, COLS;
    } WINDOW;

#endif

// #include "generation.h"
// #include "affichage.h"
#include "menu.h"

#endif