#include "../include/header.h"

void afficherMap_simp(WIN * fenetre, struct Map * niv, Mario * perso, int dmax) {
    char ch;
    struct Chunk * tmp_chunk = niv->p_chunk;
    while (tmp_chunk != NULL) {
        for (int y = 0; y < niv->height; y++) {
            for (int x = 0; x < DISTANCE; x++) {
                switch (tmp_chunk->area[y][x]) {
                    case 0: ch = ' '; break;
                    case 1: ch = '#'; break;
                    case 2: ch = 'O'; break;
                    case 3: ch = '&'; break;
                    case 4: ch = '$'; break;
                    case 5: ch = 'H'; break;
                    case 7: ch = '8'; break;
                    case 8: ch = '|'; break;
                    case 9: ch = '|'; break;
                    case 10: ch = 'V'; break;
                    default: ch = '?'; break;
                }
                mvwaddch(fenetre->fenetre, y + 1, (tmp_chunk->id - dmax / DISTANCE) * DISTANCE + x + 1, ch);
            }
        }
        tmp_chunk = tmp_chunk->suivant;
        // Afficher Mario
        mvwaddch(fenetre->fenetre, convInt(perso->y), convInt(perso->x) + 1 - (dmax / DISTANCE) * DISTANCE, 'M');
        mvwaddch(fenetre->fenetre, convInt(perso->y) + 1, convInt(perso->x) + 1 - (dmax / DISTANCE) * DISTANCE, 'X');
    }
    wrefresh(fenetre->fenetre);
}


int convX(int x) {
    return TX * x + 1;
}

int convY(int y) {
    return TY * y + 1;
}

void affichageDrapeau(WIN * win, struct Drapeau * flag, int dmax) {
    if(win == NULL) return;
    char chemin[255];
    snprintf(chemin, 255, "../design/drapeau/drapeau%d.txt", flag->frame);
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 10; j >= 0; j--) {
        if (file != NULL) {
            if (fgets(tmp, sizeof(tmp), file) == NULL) break;
            tmp[strcspn(tmp, "\n")] = '\0';
            if ((win->width-1-convX(flag->x)) < strlen(tmp)) tmp[(win->width-1-convX(flag->x))] = '\0';
            for (int k = 0; k < strlen(tmp); k++) {
                if (tmp[k] == '0') tmp[k] = ' ';
            }
            mvwaddstr(win->fenetre, convY(flag->y)+1-j, convX(flag->x - dmax), tmp);
        }
    }
    if (file != NULL) fclose(file);
}


void affichageTuyau(WIN * win, int y, int x) {
     if(win == NULL) return;
    char chemin[255] = "../design/tuyau/tuyau1.txt";
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 3; j >= 0; j--) {
        if (file != NULL) {
            if (fgets(tmp, sizeof(tmp), file) == NULL) break;
            tmp[strcspn(tmp, "\n")] = '\0';
            if ((win->width-1-convX(x)) < strlen(tmp)) tmp[(win->width-1-convX(x))] = '\0';
            for (int k = 0; k < strlen(tmp); k++) {
                if (tmp[k] == '0') tmp[k] = ' ';
            }
            mvwaddnstr(win->fenetre, convY(y)+1-j, convX(x), tmp, 9);
        }
    }
    if (file != NULL) fclose(file);
}


void affichageGoomba(WIN * win, struct Goomba * machin, int dmax) {
    if (machin == NULL) return;
    char chemin[255] = "../design/goomba/goomba1.txt";
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 1; j >= 0; j--) {
        if (file != NULL) {
            if (fgets(tmp, sizeof(tmp), file) == NULL) break;
            tmp[strcspn(tmp, "\n")] = '\0';
            for (int k = 0; k < strlen(tmp); k++) {
                if (tmp[k] == '0') tmp[k] = ' ';
            }
            mvwaddnstr(win->fenetre, convY(convInt(machin->y)) + 1 - j, convX(convInt(machin->x) - dmax), tmp, 3);
        }
    }
    if (file != NULL) fclose(file);
}

void affichageMario(WIN * win, Mario * perso, int dmax) {
    if (perso == NULL) return;
    char chemin[255] = "../design/mario/mario1.txt";
    char tmp[255];
    FILE * file = fopen(chemin, "r");
    for (int j = 3; j >= 0; j--) {
        if (file != NULL) {
            if (fgets(tmp, sizeof(tmp), file) == NULL) break;
            tmp[strcspn(tmp, "\n")] = '\0';
            for (int k = 0; k < strlen(tmp); k++) {
                if (tmp[k] == '0') tmp[k] = ' ';
            }
            mvwaddnstr(win->fenetre, convY(convInt(perso->y))-j+1, convX(convInt(perso->x - dmax)), tmp, 3);
        }
    }
    if (file != NULL) fclose(file);
}


void afficherBloc(WIN * fenetre, int y, int x, int id_bloc, int pos_plantes) {
    if (fenetre == NULL) return;
    int X_affiche = convX(x);
    int Y_affiche = convY(y);
    char haut[TX+1], bas[TX+1];
    switch (id_bloc) {
        case 0: strcpy(haut, "   "); strcpy(bas, "   "); break;
        case 1: case 2: strcpy(haut, "###"); strcpy(bas, "###"); break;
        case 3: strcpy(haut, "==="); strcpy(bas, "=?="); break;
        case 4: strcpy(haut, "($)"); strcpy(bas, "   "); break;
        case 5: strcpy(haut, ""); strcpy(bas, ""); affichageTuyau(fenetre, y, x); break;
        case 6: strcpy(haut, ""); strcpy(bas, ""); break;
        case 7: strcpy(haut, "(O)"); strcpy(bas, " U "); break;
        case 8:
            if (pos_plantes >= 2) {
                strcpy(haut, " | ");
                strcpy(bas, " | ");
            }
            else if (pos_plantes == 1) {
                strcpy(haut, "\\w/");
                strcpy(bas, " V ");
                }
            else {
                strcpy(haut, "   "); strcpy(bas, "   ");
            }
            break;
        case 9:
            if (pos_plantes == 2) {
                strcpy(haut, "\\w/");
                strcpy(bas, " V ");
            }
            else if (pos_plantes == 3) {
                strcpy(haut, " | ");
                strcpy(bas, " | ");
            }
            else {
                strcpy(haut, "   ");
                strcpy(bas, "   ");
            }
            break;
        case 10:
            if (pos_plantes == 3) {
                strcpy(haut, "\\w/");
                strcpy(bas, " v ");
            }
            else {
                strcpy(haut, "   ");
                strcpy(bas, "   ");
            }
            break;
        default: strcpy(haut, "???"); strcpy(bas, "???"); break;
    }
    mvwaddstr(fenetre->fenetre, Y_affiche, X_affiche, haut);
    mvwaddstr(fenetre->fenetre, Y_affiche + 1, X_affiche, bas);
}


void afficherChunk(WIN * fenetre, struct Chunk * troncon, int dmax, int pos_plantes) {
    if (fenetre == NULL || troncon == NULL) return;

    char txt[255];
    int pos_troncon = troncon->id - dmax / DISTANCE;
    int decal = dmax % DISTANCE;

    int anti_depassement;
    if ((fenetre->width-2)/TX < ((pos_troncon+1)*DISTANCE-decal)) {
        anti_depassement = ((pos_troncon+1)*DISTANCE-decal - (fenetre->width-2)/TX);
    } else {
        anti_depassement = 0;
    }

    for (int y = 0; y < troncon->height; y++) {
        int debut = (pos_troncon == 0) ? decal : 0;
        for (int x = debut; x < DISTANCE - anti_depassement; x++) afficherBloc(fenetre, y, x + pos_troncon * DISTANCE - decal, troncon->area[y][x], pos_plantes);
    }
}


void afficherMap(WIN * fenetre, struct Map * niv, int dmax, int pos_plantes) {
    if (niv == NULL || fenetre == NULL) return;
    struct Chunk * tmp_chunk = niv->p_chunk;
    if (tmp_chunk == NULL) {
        endwin();
        printf("ERR [afficherMap] : tmp_chunk = NULL\n");
        return;
    }
    afficherChunk(fenetre, tmp_chunk, dmax, pos_plantes);
    while (tmp_chunk->suivant != NULL) {
        tmp_chunk = tmp_chunk->suivant;
        afficherChunk(fenetre, tmp_chunk, dmax, pos_plantes);
    }
    
    char tmp[512];
    for (int i = 0; i < T_LISTE_GOOMBA; i++) {
        if (niv->liste_goomba[i] != NULL) {
            if (convX(convInt(niv->liste_goomba[i]->x - dmax)) < fenetre->width-3-1) {
                affichageGoomba(fenetre, niv->liste_goomba[i], dmax);
            }
            snprintf(tmp, 511, "ID: %d, X: %d, Y: %d, x: %.2f, y: %.2f, S: %.2f, DIFF: %d", niv->liste_goomba[i]->id, convInt(niv->liste_goomba[i]->x), convInt(niv->liste_goomba[i]->y), niv->liste_goomba[i]->x, niv->liste_goomba[i]->y, niv->liste_goomba[i]->speed, fenetre->width-3-1 - convX(convInt(niv->liste_goomba[i]->x)));
            mvwaddstr(fenetre->fenetre, i+2, 1, tmp);
        }
    }

    if (niv->flag != NULL) {
        affichageDrapeau(fenetre, niv->flag, dmax);
    }
}

void afficherTmp(WIN * tmp, int dmax, int lifes, int score) {
    wclear(tmp->fenetre);
    wborder(tmp->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    char elem[255] = "";
    
    snprintf(elem, 255, "DMAX = %d", dmax);
    mvwaddstr(tmp->fenetre, 2, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "LIVES = %d", lifes);
    mvwaddstr(tmp->fenetre, 3, 1, elem);
    strcpy(elem, "");

    snprintf(elem, 255, "SCORE = %d", score);
    mvwaddstr(tmp->fenetre, 4, 1, elem);
    strcpy(elem, "");
	
    wrefresh(tmp->fenetre);
}

void afficherPause(WIN* pauseF, int id) {
    wclear(pauseF->fenetre);
    wborder(pauseF->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(pauseF->fenetre, 2, 15, "PAUSE");
    if (id == 0) {
        mvwaddstr(pauseF->fenetre, 7, (pauseF->width - 13) / 2, "> continuer <");
        mvwaddstr(pauseF->fenetre, 12, (pauseF->width - 7) / 2, "quitter");
    }
    else if (id == 1) {
        mvwaddstr(pauseF->fenetre, 7, (pauseF->width - 9) / 2, "continuer");
        mvwaddstr(pauseF->fenetre, 12, (pauseF->width - 11) / 2, "> quitter <");
    }
    wrefresh(pauseF->fenetre);
}

void afficherPseudo(WIN* pseudoF) {
    wclear(pseudoF->fenetre);
    wborder(pseudoF->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(pseudoF->fenetre, 2, 15, "ENREGISTRER UN SCORE");
    mvwaddstr(pseudoF->fenetre, 7, (pseudoF->width - 13) / 2, "Choisissez un pseudo :");
    wrefresh(pseudoF->fenetre);
}