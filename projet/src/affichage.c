#include "../include/header.h"

void afficherMap_simp(WIN * fenetre, struct Map * niv) {
    char ch;
    for (int i = 0; i < niv->nb_chunks; i++) {
        for (int y = 0; y < niv->height; y++) {
            for (int x = 0; x < DISTANCE; x++) {
                switch (niv->carte[i]->area[y][x]) {
                    case 0: ch = ' '; break;
                    case 1: ch = '#'; break;
                    case 2: ch = 'O'; break;
                    case 3: ch = '&'; break;
                    case 4: ch = '$'; break;
                    case 5: ch = 'H'; break;
                    default: ch = '?'; break;
                }
                mvwaddch(fenetre->fenetre, y + 1, i*DISTANCE + x + 1, ch);
            }
        }
    }
    wrefresh(fenetre->fenetre);
}


int convX(int x) {
    return TX * x + 1;
}

int convY(int y) {
    return TY * y + 1;
}


void affichageTuyau(WIN * win, int y, int x) {
    char chemin[255] = "../design/tuyau/tuyau1.txt";
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 3; j >= 0; j--) {
        fgets(tmp, 10, file);
        if ((win->width-1-convX(x)) < strlen(tmp)) tmp[(win->width-1-convX(x))] = '\0';
        for (int k = 0; k < strlen(tmp); k++) {
            if (tmp[k] == '0') {
                tmp[k] = ' ';
            }
        }
        mvwaddstr(win->fenetre, convY(y)+1-j, convX(x), tmp);
    }
    fclose(file);
}


void affichageGoomba(WIN * win, struct Goomba * machin) {
    if (machin == NULL) return;
    char chemin[255] = "../design/goomba/goomba1.txt";
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 1; j >= 0; j--) {
        fgets(tmp, 4, file);
        for (int k = 0; k < strlen(tmp); k++) {
            if (tmp[k] == '0') {
                tmp[k] = ' ';
            }
        }
        mvwaddstr(win->fenetre, convY(machin->Y)+1-j, convX(machin->X), tmp);
    }
    fclose(file);
}


void afficherMap(WIN * fenetre, struct Map * niv) {
    if (niv == NULL || fenetre == NULL) return;
    char txt[255];
    for (int i = 0; i < niv->nb_chunks; i++) {
        int anti_depassement = ((fenetre->width-2)/TX < (i+1)*DISTANCE) ? ((i+1)*DISTANCE - (fenetre->width-2)/TX) : 0;
        for (int y = 0; y < niv->height; y++) {
            for (int x = 0; x < DISTANCE - anti_depassement; x++) {
                switch (niv->carte[i]->area[y][x]) {
                    case 0:
                        mvwaddstr(fenetre->fenetre, convY(y), convX(x+i*DISTANCE), "   ");
                        mvwaddstr(fenetre->fenetre, convY(y)+1, convX(x+i*DISTANCE), "   ");
                        break;
                    case 1: case 2:
                        mvwaddstr(fenetre->fenetre, convY(y), convX(x+i*DISTANCE), "###");
                        mvwaddstr(fenetre->fenetre, convY(y)+1, convX(x+i*DISTANCE), "###");
                        break;
                    case 3:
                        mvwaddstr(fenetre->fenetre, convY(y), convX(x+i*DISTANCE), "===");
                        mvwaddstr(fenetre->fenetre, convY(y)+1, convX(x+i*DISTANCE), "=?=");
                        break;
                    case 4:
                        mvwaddstr(fenetre->fenetre, convY(y), convX(x+i*DISTANCE), "($)");
                        mvwaddstr(fenetre->fenetre, convY(y)+1, convX(x+i*DISTANCE), "   ");
                        break;
                    case 5:
                        affichageTuyau(fenetre, y, x+i*DISTANCE);
                        break;
                    case 6:
                        break;
                    default:
                        mvwaddstr(fenetre->fenetre, convY(y), convX(x+i*DISTANCE), "???");
                        mvwaddstr(fenetre->fenetre, convY(y)+1, convX(x+i*DISTANCE), "???");
                        break;
                }
            }
        }
    }
    
    char tmp[512];
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (niv->liste_goomba[i] != NULL) {
            if (convX(niv->liste_goomba[i]->X) < fenetre->width-3-1) {
                affichageGoomba(fenetre, niv->liste_goomba[i]);
            }
            snprintf(tmp, 511, "ID: %d, X: %d, Y: %d, x: %.2f, y: %.2f, S: %.2f, DIFF: %d", niv->liste_goomba[i]->id, niv->liste_goomba[i]->X, niv->liste_goomba[i]->Y, niv->liste_goomba[i]->x, niv->liste_goomba[i]->y, niv->liste_goomba[i]->speed, fenetre->width-3-1 - convX(niv->liste_goomba[i]->X));
            mvwaddstr(fenetre->fenetre, i+2, 1, tmp);
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