#include "../include/menu.h"


WINDOW * creerWindowLogo() {
    int height_fenetre_logo, width_fenetre_logo, startx_fenetre_logo, starty_fenetre_logo;
    height_fenetre_logo = HEIGHT_LOGO + 2;
    width_fenetre_logo = WIDTH_LOGO + 2;
    startx_fenetre_logo = (COLS - width_fenetre_logo) / 2;
    starty_fenetre_logo = 1;
    WINDOW *logo = newwin(height_fenetre_logo, width_fenetre_logo, starty_fenetre_logo, startx_fenetre_logo);
    return logo;
}


WINDOW * creerWindowControle() {
    int height_fenetre_controle, width_fenetre_controle, startx_fenetre_controle, starty_fenetre_controle;
    height_fenetre_controle = HEIGHT_CONTROLE + 2;
    width_fenetre_controle = WIDTH_CONTROLE + 2;
    startx_fenetre_controle = COLS - width_fenetre_controle - 2;
    starty_fenetre_controle = (LINES - height_fenetre_controle) / 2;
    WINDOW *controle = newwin(height_fenetre_controle, width_fenetre_controle, starty_fenetre_controle, startx_fenetre_controle);
    return controle;
}


WINDOW * creerWindowMenu() {
    int height_fenetre_menu, width_fenetre_menu, startx_fenetre_menu, starty_fenetre_menu;
    height_fenetre_menu = LINES - 2;
    width_fenetre_menu = WIDTH_MENU + 2;
    startx_fenetre_menu = 2;
    starty_fenetre_menu = 1;
    WINDOW *menu = newwin(height_fenetre_menu, width_fenetre_menu, starty_fenetre_menu, startx_fenetre_menu);
    return menu;
}


WINDOW * creerWindowChoix() {
    int height_fenetre_choix, width_fenetre_choix, startx_fenetre_choix, starty_fenetre_choix;
    height_fenetre_choix = LINES - 2;
    width_fenetre_choix = COLS - WIDTH_MENU - 7;
    startx_fenetre_choix = WIDTH_MENU + 6;
    starty_fenetre_choix = 1;
    WINDOW *choix = newwin(height_fenetre_choix, width_fenetre_choix, starty_fenetre_choix, startx_fenetre_choix);
    return choix;
}


WINDOW * creerWindowEloise() {
    int height_fenetre_eloise, width_fenetre_eloise, startx_fenetre_eloise, starty_fenetre_eloise;
    height_fenetre_eloise = HEIGHT_ELOISE;
    width_fenetre_eloise = WIDTH_ELOISE;
    startx_fenetre_eloise = (COLS - width_fenetre_eloise) / 2;
    starty_fenetre_eloise = (LINES - height_fenetre_eloise) / 2;
    WINDOW *eloise = newwin(height_fenetre_eloise, width_fenetre_eloise, starty_fenetre_eloise, startx_fenetre_eloise);
    return eloise;
}


void affichageEloise(WINDOW * eloise) {
    wborder(eloise, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(eloise);
}


void affichageRetromario(WINDOW * logo) {
    char chemin[] = "../design/retromario/retromario1.txt";  // Le chemin est à calculer depuis l'éxécutable.
    FILE * file = fopen(chemin, "r");
    if (file != NULL) {
        wattron(logo, A_BOLD);
        for (int y = 0; y < HEIGHT_LOGO; y++) {
            char tmp[WIDTH_LOGO+1];
            fgets(tmp, WIDTH_LOGO+1, file);
            for (int i = 0; i < strlen(tmp); i++) {
                if (tmp[i] == '0') {
                    tmp[i] = ' ';
                }
            }
            mvwaddstr(logo, y+1, 1, tmp);
        }
        wattroff(logo, A_BOLD);
        wrefresh(logo);
        fclose(file);
    }
}

void affichageControle(WINDOW * controle) {
    wborder(controle, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle, 2, 3, "> SAUTER / ^ : Z");
    mvwaddstr(controle, 4, 3, "> GAUCHE / v : Q");
    mvwaddstr(controle, 6, 3, "> DROITE : D");
    mvwaddstr(controle, 8, 3, "> PAUSE :  P");

    wrefresh(controle);
}

void affichageGenerale(WINDOW * logo, WINDOW * controle, WINDOW * eloise) {
    affichageRetromario(logo);
    affichageControle(controle);
    affichageEloise(eloise);
}

void affichageMenuPrincipal(WINDOW * menu, int choix) {
    wclear(menu);
    const int taille_menu = 4;
    char liste_menu[4][100] = {"LANCER UNE PARTIE", "HI-SCORES", "SAUVEGARDES", "QUITTER"};

    wclear(menu);
    wattron(menu, A_BOLD);
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    wattroff(menu, A_BOLD);
    char affiche[255];
    for (int i = 0; i < taille_menu; i++) {
        if (i == choix) {
            sprintf(affiche, "> %s <", liste_menu[i]);
            wattron(menu, A_BOLD);
        } else sprintf(affiche, "  %s  ", liste_menu[i]);
        mvwaddstr(menu, 4*(i+1), (WIDTH_MENU-(strlen(liste_menu[i])+4)+1)/2, affiche);
        if (i == choix) wattroff(menu, A_BOLD);
    }
    wrefresh(menu);
}

void actionMenuPrincipal(WINDOW * menu, int * id) {
    char pressed;
    affichageMenuPrincipal(menu, *id);
    while ((pressed = wgetch(menu)) != '\n') {
        if (pressed == 'z') (*id)--;
        else if (pressed == 's') (*id)++;
        if (*id < 0) *id = 3;
        if (*id > 3) *id = 0;
        affichageMenuPrincipal(menu, *id);
    }
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
    struct_score->id = atoi(elem[0]);
    strncpy(struct_score->pseudo, elem[1], sizeof(struct_score->pseudo) - 1);
    struct_score->pseudo[sizeof(struct_score->pseudo) - 1] = '\0';
    struct_score->score = atoi(elem[2]);

    return struct_score;
}


struct Score ** recupHiscores() {
    struct Score ** liste_score = malloc(10 * sizeof(struct Score*));
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
    fclose(file);
    return liste_score;
}


void affichageHiscores(WINDOW * win, struct Score ** liste_score, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win);
    wattron(win, A_BOLD);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win, 1, (COLS - WIDTH_MENU - 37) / 2, " _____ _____ _____ _____ _____ _____ ");
    mvwaddstr(win, 2, (COLS - WIDTH_MENU - 37) / 2, "|   __|     |     | __  |   __|   __|");
    mvwaddstr(win, 3, (COLS - WIDTH_MENU - 37) / 2, "|__   |   --|  |  |    -|   __|__   |");
    mvwaddstr(win, 4, (COLS - WIDTH_MENU - 37) / 2, "|_____|_____|_____|__|__|_____|_____|");
    wattroff(win, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) sprintf(text, "  >>> %d. %s - %d", i+1, liste_score[i]->pseudo, liste_score[i]->score);
        else sprintf(text, "  >>> null");
        WINDOW * score = derwin(win, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
        if (i == choisi) wattron(score, A_BOLD);
        mvwaddstr(score, 2, 2, text);
        if (i == choisi) wattroff(score, A_BOLD);
    }
    mvwaddstr(win, 50, 2, " 'x' to delete a score");
    wrefresh(win);
}


void actionHiscores(WINDOW * win, struct Score ** liste_score, int * id) {
    char pressed;
    affichageHiscores(win, liste_score, *id);
    while ((pressed = wgetch(win)) != 'k') {
        if (pressed == 'z') (*id)--;
        else if (pressed == 's') (*id)++;
        else if (pressed == 'x') supprHiscores(liste_score, *id);  // Supprimer le score
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageHiscores(win, liste_score, *id);
    }
    wclear(win);
    wrefresh(win);
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

Save * recupSave(char * str){

    Save * liste_sauvegarde = malloc(sizeof(Save));
    if (liste_sauvegarde == NULL) return NULL;
    char * elem[8]= {NULL};
    elem[0] = strtok(str, ", \n");
    for (int i = 1; i < 8; i++)
    {
        elem[i] = strtok(NULL, ", \n");
    }
    liste_sauvegarde->id = atoi(elem[0]);
    liste_sauvegarde->seed = atoi(elem[1]);
    liste_sauvegarde->distance = atoi(elem[2]);
    liste_sauvegarde->posx = atoi(elem[3]);
    liste_sauvegarde->posy = atoi(elem[4]);
    liste_sauvegarde->kills = atoi(elem[5]);
    liste_sauvegarde->piece = atoi(elem[6]);
    liste_sauvegarde->vies = atoi(elem[7]);

    return liste_sauvegarde;
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
    fclose(file);
    return liste_sauvegarde;
}

void affichageSauvegarde(WINDOW * win, Save ** liste_sauvegarde, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win);
    wattron(win, A_BOLD);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win, 1, (COLS - WIDTH_MENU - 68) / 2, " _____ _____ _____ _____ _____ _____ _____ _____ ____  _____ _____ ");
    mvwaddstr(win, 2, (COLS - WIDTH_MENU - 68) / 2, "|   __|  _  |  |  |  |  |   __|   __|  _  | __  |    \\|   __|   __|");
    mvwaddstr(win, 3, (COLS - WIDTH_MENU - 68) / 2, "|__   |     |  |  |  |  |   __|  |  |     |    -|  |  |   __|__   |");
    mvwaddstr(win, 4, (COLS - WIDTH_MENU - 68) / 2, "|_____|__|__|_____|\\___/|_____|_____|__|__|__|__|____/|_____|_____|");
    wattroff(win, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_sauvegarde[i] != NULL) {
            WINDOW * save = derwin(win, 5, (COLS - WIDTH_MENU - 7), 5+2*i, 0);
            sprintf(text, "  >>> %d. Seed :%d - Distance :%d - Pose en x/y : %d / %d - kills : %d - Pieces : %d - Vies : %d",liste_sauvegarde[i]->id, liste_sauvegarde[i]->seed, liste_sauvegarde[i]->distance,liste_sauvegarde[i]->posx,liste_sauvegarde[i]->posy,liste_sauvegarde[i]->kills,liste_sauvegarde[i]->piece,liste_sauvegarde[i]->vies);
            if (i == choisi) wattron(save, A_BOLD);
            mvwaddstr(save, 2, 2, text);
            if (i == choisi) wattroff(save, A_BOLD);
        } else break;
    }
    mvwaddstr(win, 50, 2, " 'x' to delete a save");
    wrefresh(win);
}

void actionSauvegarde(WINDOW * win,  Save ** liste_sauvegarde, int * id) {
    char pressed;
    affichageSauvegarde(win, liste_sauvegarde, *id);
    while ((pressed = wgetch(win)) != 'k') {
        if (pressed == 'z') (*id)--;
        else if (pressed == 's') (*id)++;
        else if (pressed == 'x') supprSauvegarde(liste_sauvegarde, *id);  // Supprimer la sauvegarde
        if (*id < 0) *id = 9;
        if (*id > 9) *id = 0;
        affichageSauvegarde(win, liste_sauvegarde, *id);
    }
    wclear(win);
    wrefresh(win);
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