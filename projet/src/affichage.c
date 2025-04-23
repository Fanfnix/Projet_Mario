#include "../include/header.h"

void afficherMap_simp(WIN * fenetre, struct Map* niv, int height_carte, int width_carte) {
    char ch;
    for (int y = 0; y < height_carte; y++) {
        for (int x = 0; x < width_carte; x++) {
            switch (niv->carte[y][x]) {
                case 0: ch = ' '; break;
                case 1: ch = '#'; break;
                case 2: ch = 'O'; break;
                case 3: ch = '&'; break;
                case 4: ch = '$'; break;
                case 5: ch = 'H'; break;
                default: ch = '?'; break;
            }
            mvwaddch(fenetre->fenetre, y + 1, x + 1, ch);
        }
    }
    wrefresh(fenetre->fenetre);
}


void affichageTuyau(WIN * win, int Y, int X) {
    char chemin[255] = "../design/tuyau/tuyau1.txt";
    FILE * file = fopen(chemin, "r");
    for (int j = 0; j < 4; j++) {
        char tmp[255];
        fgets(tmp, 10, file);
        for (int k = 0; k < strlen(tmp); k++) {
            if (tmp[k] == '0') {
                tmp[k] = ' ';
            }
        }
        mvwaddstr(win->fenetre, Y+j, X, tmp);
    }
    fclose(file);
}


void afficherMap(WIN * fenetre, struct Map * niv, int height_carte, int width_carte) {
    for (int y = 0; y < height_carte; y++) {
        for (int i = 0; i < 2; i++) {
            for (int x = 0; x < width_carte; x++) {
                switch (niv->carte[y][x]) {
                    case 0: mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "   "); break;
                    case 1: case 2: mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "###"); break;
                    case 3: if (!i) mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "==="); else mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "=?="); break;
                    case 4: if (!i) mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "($)"); else mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "   "); break;
                    case 5: if (i) affichageTuyau(fenetre, TY*(y-1)+1, TX*x+1); break;
                    case 6: break;
                    default: mvwaddstr(fenetre->fenetre, TY*y+i+1, TX*x+1, "???"); break;
                }
            }
        }
    }
}


void afficherTmp(WIN * tmp, int X, int Y, int dMax, int* table, int seed) {
    wborder(tmp->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    char elem[255] = "";
    int x = X - dMax;
    
    snprintf(elem, 255, "X = %d", X);
    mvwaddstr(tmp->fenetre, 1, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "dMax = %d", dMax);
    mvwaddstr(tmp->fenetre, 2, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "x = %d", x);
    mvwaddstr(tmp->fenetre, 3, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "Y = %d", Y);
    mvwaddstr(tmp->fenetre, 4, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "SEED = %d", seed);
    mvwaddstr(tmp->fenetre, 1, 50, elem);
    strcpy(elem, "");
	
    wrefresh(tmp->fenetre);
}