#include <string.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// DRAPEAU : drapeau, 6, 5, 11
// GOOMBA : goomba, 2, 3, 2
// MARIO : mario, 3, 2, 4
// PLANTE : plante, 4, 1, 3

struct Elem {
    char * nom;
    int nb_frame;
    int width, height;
};

void affichage(char * elem, int nb_frame, int width, int height) {
    for (int i = 0; i < nb_frame; i++) {
        char chemin[255];

        snprintf(chemin, 255, "%s/%s%d.txt", elem, elem, i + 1);

        FILE * file = fopen(chemin, "r");

        clear();

        for (int j = 0; j < height; j++) {
            char tmp[255];
            fgets(tmp, width+1, file);

            for (int k = 0; k < strlen(tmp); k++) {
                if (tmp[k] == '0') {
                    tmp[k] = ' ';
                }
            }
            printw("#   %s   #\n", tmp);
        }
        refresh();
        usleep(0.5 * 1000000);
        fclose(file);
    }
}


int main() {
    initscr();

    // Modifiiez les valeurs de a_teste pour tester (les valeurs a entrer sont au début du programme)
    struct Elem a_teste = {"drapeau", 6, 5, 11};
    affichage(a_teste.nom, a_teste.nb_frame, a_teste.width, a_teste.height);

    printw("\n>>> Press any to quit :");

    while (1) {
        if (getch() != -1) {
            break;
        }
    }

    endwin();
    return 0;
}