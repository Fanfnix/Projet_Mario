#include "../include/header.h"

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

void affichageSauvegarde(WIN * win,WIN * ascii, WIN * blocpiece, struct Save ** liste_sauvegarde, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win->fenetre);
    wattron(win->fenetre, A_BOLD);
    wborder(win->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win->fenetre, 1, (win ->width - 68) / 2, " _____ _____ _____ _____ _____ _____ _____ _____ ____  _____ _____ ");
    mvwaddstr(win->fenetre, 2, (win ->width - 68) / 2, "|   __|  _  |  |  |  |  |   __|   __|  _  | __  |    \\|   __|   __|");
    mvwaddstr(win->fenetre, 3, (win ->width - 68) / 2, "|__   |     |  |  |  |  |   __|  |  |     |    -|  |  |   __|__   |");
    mvwaddstr(win->fenetre, 4, (win ->width - 68) / 2, "|_____|__|__|_____|\\___/|_____|_____|__|__|__|__|____/|_____|_____|");
    wattroff(win->fenetre, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_sauvegarde[i] != NULL) {
            WINDOW * save = derwin(win->fenetre, 5, (win ->width - 7), 5+2*i, 0);
            sprintf(text, "  >>> %d. Seed :%d - Pose en x/y : %.0f / %.0f - score : %d - Vies : %d",liste_sauvegarde[i]->id, liste_sauvegarde[i]->seed, liste_sauvegarde[i]->posx, liste_sauvegarde[i]->posy, liste_sauvegarde[i]->score, liste_sauvegarde[i]->vies);
        }
        else sprintf(text, "  >>> null");
        WINDOW * save = derwin(win->fenetre, 5, (win ->width - 7), 5+2*i, 0);
        if (i == choisi) wattron(save, A_BOLD);
        mvwaddstr(save, 2, (win ->width - strlen(text))/2, text);
        if (i == choisi) wattroff(save, A_BOLD);
    }
    mvwaddstr(win->fenetre, 50, 2, " [DEL] to delete a save");
    wrefresh(win->fenetre);
    affichageAscii(ascii);
    affichageBlocpiece(blocpiece);
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