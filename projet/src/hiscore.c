#include "../include/header.h"

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

void affichageHiscores(WIN * win, WIN * ascii, WIN * blocpiece, struct Score ** liste_score, int choisi) {
    if (choisi >= 10) {
        endwin();
        printf("CHOIX = %d | SIZE = 10\n", choisi);
        return;
    }
    wclear(win->fenetre);
    wattron(win->fenetre, A_BOLD);
    wborder(win->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(win->fenetre, 1, (win ->width - 37) / 2, " _____ _____ _____ _____ _____ _____ ");
    mvwaddstr(win->fenetre, 2, (win ->width - 37) / 2, "|   __|     |     | __  |   __|   __|");
    mvwaddstr(win->fenetre, 3, (win ->width - 37) / 2, "|__   |   --|  |  |    -|   __|__   |");
    mvwaddstr(win->fenetre, 4, (win ->width - 37) / 2, "|_____|_____|_____|__|__|_____|_____|");
    wattroff(win->fenetre, A_BOLD);
    char text[255];
    for (int i = 0; i < 10; i++) {
        if (liste_score[i] != NULL) sprintf(text, "  %d. %s - %d", i+1, liste_score[i]->pseudo, liste_score[i]->score);
        else sprintf(text, "  null");
        WINDOW * score = derwin(win->fenetre, 7, (win ->width - 7), 5+2*i, 0);
        mvwaddstr(score, 3, (win ->width - 37)/2, "-------------------------------------");
        mvwaddstr(score, 4, (win->width + 36)/2, "|");
        mvwaddstr(score, 4, (win ->width - 37)/2, "|");
        mvwaddstr(score, 5, (win ->width - 37)/2, "-------------------------------------");
        if (i == choisi) wattron(score, A_BOLD);
        mvwaddstr(score, 4, (win ->width - strlen(text))/2, text);
        if (i == choisi) wattroff(score, A_BOLD);
    }
    mvwaddstr(win->fenetre, 50, 2, " [DEL] to delete a score");
    wrefresh(win->fenetre);
    affichageAscii(ascii);
    affichageBlocpiece(blocpiece);

}
void supprHiscores(struct Score ** liste_score, int id) {
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