#include "../include/header.h"


WIN * creerFenetre(WINDOW * fenetre, int width, int height) {
    WIN * win = malloc(sizeof(WIN));
    if (win == NULL || fenetre == NULL) return NULL;
    win->fenetre = fenetre;
    win->width = width;
    win->height = height;
    return win;
}


WIN * creerWindowLogo() {
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;
    WINDOW * logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    WIN * fenetre = creerFenetre(logo, width_fenetre_logo, height_fenetre_logo);
    return fenetre;
}


WIN * creerWindowControle() {
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;
    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = COLS - width_fenetre_controle - 2;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;
    WINDOW * controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    WIN * fenetre = creerFenetre(controle, width_fenetre_controle, height_fenetre_controle);
    return fenetre;
}


WIN * creerWindowMenu() {
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    height_fenetre_menu = LINES - 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = 2;
    starty_fenetre_menu = 1;
    WINDOW * menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);
    keypad(menu, true);
    WIN * fenetre = creerFenetre(menu, width_fenetre_menu, height_fenetre_menu);
    return fenetre;
}


WIN * creerWindowChoix() {
    int height_fenetre_choix, width_fenetre_choix, startx_fenetre_choix, starty_fenetre_choix;
    height_fenetre_choix = LINES - 2;
    width_fenetre_choix = COLS - WIDTH_MENU - 7;
    startx_fenetre_choix = WIDTH_MENU + 6;
    starty_fenetre_choix = 1;
    WINDOW * choix = newwin(height_fenetre_choix, width_fenetre_choix, starty_fenetre_choix, startx_fenetre_choix);
    keypad(choix, true);
    WIN * fenetre = creerFenetre(choix, width_fenetre_choix, height_fenetre_choix);
    return fenetre;
}


WIN * creerWindowEloise() {
    int height_fenetre_eloise, width_fenetre_eloise, startx_fenetre_eloise, starty_fenetre_eloise;
    height_fenetre_eloise = HEIGHT_ELOISE;
    width_fenetre_eloise = WIDTH_ELOISE;
    startx_fenetre_eloise = (COLS - width_fenetre_eloise) / 2;
    starty_fenetre_eloise = (LINES - height_fenetre_eloise) / 2;
    WINDOW * eloise = newwin(height_fenetre_eloise, width_fenetre_eloise, starty_fenetre_eloise, startx_fenetre_eloise);
    WIN * fenetre = creerFenetre(eloise, width_fenetre_eloise, height_fenetre_eloise);
    return fenetre;
}

WIN * creerWindowAscii() {
    int height_fenetre_ascii, width_fenetre_ascii, startx_fenetre_ascii, starty_fenetre_ascii;
    height_fenetre_ascii = HEIGHT_ASCII + 2;
    width_fenetre_ascii = WIDTH_ASCII + 2;
    startx_fenetre_ascii = 50;
    starty_fenetre_ascii = 6;
    WINDOW * ascii = newwin(height_fenetre_ascii, width_fenetre_ascii, starty_fenetre_ascii, startx_fenetre_ascii);
    WIN * fenetre = creerFenetre(ascii, width_fenetre_ascii, height_fenetre_ascii);
    return fenetre;
}

WIN * creerWindowBlocpiece() {
    int height_fenetre_blocpiece, width_fenetre_blocpiece, startx_fenetre_blocpiece, starty_fenetre_blocpiece;
    height_fenetre_blocpiece = HEIGHT_BLOCPIECE + 2;
    width_fenetre_blocpiece = WIDTH_BLOCPIECE + 2;
    startx_fenetre_blocpiece = 190;
    starty_fenetre_blocpiece = 7;
    WINDOW * blocpiece = newwin(height_fenetre_blocpiece, width_fenetre_blocpiece, starty_fenetre_blocpiece, startx_fenetre_blocpiece);
    WIN * fenetre = creerFenetre(blocpiece, width_fenetre_blocpiece, height_fenetre_blocpiece);
    return fenetre;
}

void affichageDessinmenu(WIN * eloise){
    char chemin[] = "../design/dessinmenu/dessinmenu1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_ELOISE; y++){
            char tmp[WIDTH_ELOISE+1];
            fgets(tmp, WIDTH_ELOISE+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(eloise->fenetre, y+1, 1, tmp);
        }
        wrefresh(eloise->fenetre);
        fclose(file);
    }
}

void affichageAscii(WIN * ascii){
    char chemin[] = "../design/ascii/ascii1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_ASCII; y++){
            char tmp[WIDTH_ASCII+1];
            fgets(tmp, WIDTH_ASCII+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(ascii->fenetre, y+1, 1, tmp);
        }
        wrefresh(ascii->fenetre);
        fclose(file);
    }
}

void affichageBlocpiece(WIN * blocpiece){
    char chemin[] = "../design/blocpiece/blocpiece1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL){
        for (int y = 0; y < HEIGHT_BLOCPIECE; y++){
            char tmp[WIDTH_BLOCPIECE+1];
            fgets(tmp, WIDTH_BLOCPIECE+1, file);
            for (int i = 0; i < strlen(tmp); i++){
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(blocpiece->fenetre, y+1, 1, tmp);
        }
        wrefresh(blocpiece->fenetre);
        fclose(file);
    }
}

void affichageRetromario(WIN * logo) {
    char chemin[] = "../design/retromario/retromario1.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file != NULL) {
        wattron(logo->fenetre, A_BOLD);
        for (int y = 0; y < HEIGHT_LOGO; y++) {
            char tmp[WIDTH_LOGO+1];
            fgets(tmp, WIDTH_LOGO+1, file);
            for (int i = 0; i < strlen(tmp); i++) {
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(logo->fenetre, y+1, 1, tmp);
        }
        wattroff(logo->fenetre, A_BOLD);
        wrefresh(logo->fenetre);
        fclose(file);
    }
}

void affichageControle(WIN * controle) {
    wborder(controle->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle->fenetre, 2, 3, "> SAUTER / ^ : Z");
    mvwaddstr(controle->fenetre, 4, 3, "> GAUCHE / v : Q");
    mvwaddstr(controle->fenetre, 6, 3, "> DROITE : D");
    mvwaddstr(controle->fenetre, 8, 3, "> PAUSE :  P");

    wrefresh(controle->fenetre);
}

void affichageGenerale(WIN * logo, WIN * controle, WIN * eloise) {
    affichageRetromario(logo);
    affichageControle(controle);
    affichageDessinmenu(eloise);

}

void affichageMenuPrincipal(WIN * menu, int choix) {
    wclear(menu->fenetre);
    const int taille_menu = 4;
    char liste_menu[4][100] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu->fenetre);
    wattron(menu->fenetre, A_BOLD);
    wborder(menu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(menu->fenetre, A_BOLD);
    char affiche[255];
    for (int i = 0; i < taille_menu; i++) {
        if (i == choix) {
            sprintf(affiche, "> %s <", liste_menu[i]);
            wattron(menu->fenetre, A_BOLD);
        } else sprintf(affiche, "  %s  ", liste_menu[i]);
        mvwaddstr(menu->fenetre, 4*(i+1), (WIDTH_MENU-(strlen(liste_menu[i])+4)+1)/2, affiche);
        if (i == choix) wattroff(menu->fenetre, A_BOLD);
    }
    wrefresh(menu->fenetre);
}

void actionMenuPrincipal(WIN * menu, int * id, Mix_Chunk* selectSE, Mix_Chunk* confirmeSE) {
    int pressed;
    affichageMenuPrincipal(menu, *id);
    while ((pressed = wgetch(menu->fenetre)) != 10) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        if (*id < 0) *id = 3;
        if (*id > 3) *id = 0;
        affichageMenuPrincipal(menu, *id);
    }
    Mix_PlayChannel(-1, confirmeSE, 0);
}

// HI-SCORE

struct Score * recupScore(char * str) {
    struct Score * struct_score = malloc(sizeof(struct Score));
    if (struct_score == NULL) return NULL;

    char * elem[3] = {NULL};
    elem[0] = strtok(str, ", \n");
    for (int i = 1; i < 3; i++) {
        elem[i] = strtok(NULL, ", \n");
    }
    if (!elem[0] || !elem[1] || !elem[2]) {
        free(struct_score);
        return NULL;
    }
    struct_score->id = atoi(elem[0]);
    strncpy(struct_score->pseudo, elem[1], sizeof(struct_score->pseudo) - 1);
    struct_score->pseudo[sizeof(struct_score->pseudo) - 1] = '\0';
    struct_score->score = atoi(elem[2]);

    return struct_score;
}


struct Score ** recupHiscores() {
    struct Score ** liste_score = malloc(10 * sizeof(struct Score*));
    if (liste_score == NULL) return NULL;
    for (int i = 0; i < 10; i++) liste_score[i] = NULL;

    char chemin[] = "data/hi_scores.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file == NULL) {
        free(liste_score);
        return NULL;
    }
    char line[50];
    for (int i = 0; i < 10; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        liste_score[i] = recupScore(line);
    }
    if (fclose(file) == EOF)
    {
        return NULL;
    }
    return liste_score;
}

void ecritureHiscores(struct Score ** liste_score) {
    if (liste_score == NULL) return;
    char chemin[] = "data/hi_scores.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "w");
    if (file == NULL) return;
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) {
            fprintf(file, "%d,%s,%d\n", liste_score[i]->id, liste_score[i]->pseudo, liste_score[i]->score);
        }
    }
    if (fclose(file) == EOF) return;
}

void trierHiscores(struct Score ** liste_score) {
    if (liste_score == NULL) return;
    for (int i = 0; i < 10-1 ; i++) {
        for (int j = 0; j < 10-i-2; j++) {
            if (liste_score[j] == NULL || liste_score[j+1] == NULL) continue;
            if (liste_score[j]->score < liste_score[j+1]->score){
                struct Score * tmp = liste_score[j];
                liste_score[j] = liste_score[j+1];
                liste_score[j+1] = tmp;
            }
        }
    }
}

void affichageHiscores(WIN * win,WIN * ascii, WIN * blocpiece, struct Score ** liste_score, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win->fenetre);
    wattron(win->fenetre, A_BOLD);
    wborder(win->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win->fenetre, 1, (COLS - WIDTH_MENU - 37) / 2, " _____ _____ _____ _____ _____ _____ ");
    mvwaddstr(win->fenetre, 2, (COLS - WIDTH_MENU - 37) / 2, "|   __|     |     | __  |   __|   __|");
    mvwaddstr(win->fenetre, 3, (COLS - WIDTH_MENU - 37) / 2, "|__   |   --|  |  |    -|   __|__   |");
    mvwaddstr(win->fenetre, 4, (COLS - WIDTH_MENU - 37) / 2, "|_____|_____|_____|__|__|_____|_____|");
    wattroff(win->fenetre, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) sprintf(text, "  >>> %d. %s - %d", i+1, liste_score[i]->pseudo, liste_score[i]->score);
        else sprintf(text, "  >>> null");
        WINDOW * score = derwin(win->fenetre, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
        if (i == choisi) wattron(score, A_BOLD);
        mvwaddstr(score, 2, (COLS - WIDTH_MENU - strlen(text))/2, text);
        if (i == choisi) wattroff(score, A_BOLD);
    }
    mvwaddstr(win->fenetre, 50, 2, " [DEL] to delete a score");
    wrefresh(win->fenetre);
    affichageAscii(ascii);
    affichageBlocpiece(blocpiece);

}

void actionHiscores(WIN * win,WIN *ascii,WIN * blocpiece, struct Score ** liste_score, int * id, Mix_Chunk* selectSE, Mix_Chunk* degatSE) {
    int pressed;
    affichageHiscores(win, ascii, blocpiece, liste_score, *id);
    while ((pressed = wgetch(win->fenetre)) != 27) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == 8 || pressed == 263) {
            supprHiscores(liste_score, *id);
            Mix_PlayChannel(-1, degatSE, 0);
        }  // Supprimer le score
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageHiscores(win, ascii, blocpiece, liste_score, *id);
    }
    wclear(win->fenetre);
    wrefresh(win->fenetre);
}

void supprHiscores(struct Score ** liste_score, int id){
    if (liste_score == NULL)
    {
        printf("Pas de score a supprimer");
        return;
    }
    
    free(liste_score[id]);
    liste_score[id]= NULL;
    for (int i = id + 1; i < 10; i++)
    {
        liste_score[i-1]= liste_score[i];
        if (liste_score[i-1] == NULL) break;
        liste_score[i-1]->id--;
    } 
}

void libererHiscores(struct Score ** liste_score) {
    if (liste_score == NULL) return;
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) {
            free(liste_score[i]);
            liste_score[i] = NULL;
        }
    }
    free(liste_score);
    liste_score = NULL;
}

//SAUVEGARDES

Save * recupSave(char * str) {
    if (str == NULL) return NULL;
    Save * sauvegarde = malloc(sizeof(Save));
    if (sauvegarde == NULL) return NULL;
    char * elem[8]= {NULL};
    elem[0] = strtok(str, ", \n");
    for (int i = 1; i < 7; i++)
    {
        elem[i] = strtok(NULL, ", \n");
    }
    sauvegarde->id = atoi(elem[0]);
    sauvegarde->seed = atoi(elem[1]);
    sauvegarde->distance = atoi(elem[2]);
    sauvegarde->score = atoi(elem[3]);
    sauvegarde->posx = (float)atoi(elem[4]);
    sauvegarde->posy = (float)atoi(elem[5]);
    sauvegarde->vies = atoi(elem[6]);

    return sauvegarde;
}

Save ** recupCheckpoint() {
    Save ** liste_sauvegarde = malloc(10 * sizeof(struct Save*));
    for (int i = 0; i < 10; i++) liste_sauvegarde[i] = NULL;

    char chemin[] = "data/sauvegardes.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file == NULL) {
        free(liste_sauvegarde);
        return NULL;
    }
    char line[50];
    for (int i = 0; i < 10; i++) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        liste_sauvegarde[i] = recupSave(line);
    }
    if (fclose(file) == EOF)
    {
        return NULL;
    }
    return liste_sauvegarde;
}

void ecritureSauvegarde(struct Save ** liste_sauvegarde) {
    if (liste_sauvegarde == NULL) return;
    char chemin[] = "data/sauvegardes.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "w");
    if (file == NULL) return;
    for (int i = 0; i < 10; i++) {
        if (liste_sauvegarde[i] != NULL) {
            fprintf(file, "%d,%d,%d,%d,%f,%f,%d\n", liste_sauvegarde[i]->id, liste_sauvegarde[i]->seed, liste_sauvegarde[i]->distance, liste_sauvegarde[i]->score, liste_sauvegarde[i]->posx, liste_sauvegarde[i]->posy, liste_sauvegarde[i]->vies);
        }
    }
    if (fclose(file) == EOF) return;
}

void affichageSauvegarde(WIN * win, Save ** liste_sauvegarde, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win->fenetre);
    wattron(win->fenetre, A_BOLD);
    wborder(win->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win->fenetre, 1, (COLS - WIDTH_MENU - 68) / 2, " _____ _____ _____ _____ _____ _____ _____ _____ ____  _____ _____ ");
    mvwaddstr(win->fenetre, 2, (COLS - WIDTH_MENU - 68) / 2, "|   __|  _  |  |  |  |  |   __|   __|  _  | __  |    \\|   __|   __|");
    mvwaddstr(win->fenetre, 3, (COLS - WIDTH_MENU - 68) / 2, "|__   |     |  |  |  |  |   __|  |  |     |    -|  |  |   __|__   |");
    mvwaddstr(win->fenetre, 4, (COLS - WIDTH_MENU - 68) / 2, "|_____|__|__|_____|\\___/|_____|_____|__|__|__|__|____/|_____|_____|");
    wattroff(win->fenetre, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_sauvegarde[i] != NULL) {
            WINDOW * save = derwin(win->fenetre, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
            sprintf(text, "  >>> %d. Seed :%d - Pose en x/y : %.0f / %.0f - score : %d - Vies : %d",liste_sauvegarde[i]->id, liste_sauvegarde[i]->seed, liste_sauvegarde[i]->posx, liste_sauvegarde[i]->posy, liste_sauvegarde[i]->score, liste_sauvegarde[i]->vies);
        }
        else sprintf(text, "  >>> null");
        WINDOW * save = derwin(win->fenetre, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
        if (i == choisi) wattron(save, A_BOLD);
        mvwaddstr(save, 2, (COLS - WIDTH_MENU - strlen(text))/2, text);
        if (i == choisi) wattroff(save, A_BOLD);
    }
    mvwaddstr(win->fenetre, 50, 2, " [DEL] to delete a save");
    wrefresh(win->fenetre);
}

void actionSauvegarde(WIN * win,  Save ** liste_sauvegarde, int * id, Mix_Chunk* selectSE, Mix_Chunk* degatSE) {
    int pressed;
    affichageSauvegarde(win, liste_sauvegarde, *id);
    while ((pressed = wgetch(win->fenetre)) != 27) {
        if (pressed == KEY_UP) {
            (*id)--;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == KEY_DOWN) {
            (*id)++;
            Mix_PlayChannel(-1, selectSE, 0);
        }
        else if (pressed == 8 || pressed == 263) {
            supprSauvegarde(liste_sauvegarde, *id);
            Mix_PlayChannel(-1, degatSE, 0);
        }  // Supprimer la sauvegarde
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageSauvegarde(win, liste_sauvegarde, *id);
    }
    wclear(win->fenetre);
    wrefresh(win->fenetre);
}

void supprSauvegarde(Save **liste_sauvegarde, int id){
    
    if (liste_sauvegarde == NULL)
    {
        printf("Pas de sauvegarde a supprimer");
        return;
    }
    
    free(liste_sauvegarde[id]);
    liste_sauvegarde[id]= NULL;
    for (int i = id + 1; i < 10; i++)
    {
        liste_sauvegarde[i-1]= liste_sauvegarde[i];
        if (liste_sauvegarde[i-1] == NULL) break;
        liste_sauvegarde[i-1]->id--;
    }   
}

void libererSauvegarde(Save ** liste_sauvegarde) {
    if (liste_sauvegarde == NULL) return;
    for (int i = 0; i < 10; i++) {
        if (liste_sauvegarde[i] != NULL) {
            free(liste_sauvegarde[i]);
            liste_sauvegarde[i] = NULL;
        }
    }
    free(liste_sauvegarde);
    liste_sauvegarde = NULL;
}

void nettoyerMenu(WIN * logo, WIN * menu, WIN * choix, WIN * controle, WIN * eloise, WIN * ascii, WIN * blocpiece) {
    wclear(logo->fenetre);
    wrefresh(logo->fenetre);

    wclear(menu->fenetre);
    wrefresh(menu->fenetre);

    wclear(choix->fenetre);
    wrefresh(choix->fenetre);

    wclear(controle->fenetre);
    wrefresh(controle->fenetre);

    wclear(eloise->fenetre);
    wrefresh(eloise->fenetre);

    wclear(ascii->fenetre);
    wrefresh(ascii->fenetre);

    wclear(blocpiece->fenetre);
    wrefresh(blocpiece->fenetre);
}


void supprWin(WIN * fenetre) {
    if (fenetre == NULL) return;
    if (fenetre->fenetre != NULL) {
        wclear(fenetre->fenetre);
        wrefresh(fenetre->fenetre);
        delwin(fenetre->fenetre);
    }
    free(fenetre);
    fenetre = NULL;
}