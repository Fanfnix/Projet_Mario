#include "../include/menu.h"


void affichageRetromario(WINDOW * logo) {
    char chemin[] = "../../design/retromario/retromario1.txt";
    FILE * file = fopen(chemin, "r");
    if (file != NULL) {
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
        wrefresh(logo);
        fclose(file);
    }
    if (errno == 0) printf("ERRNO VIDE\n");
    printf("%d\n", errno);
}

void affichageControle(WINDOW * controle) {
    wborder(controle, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddstr(controle, 2, 3, "> SAUTER : Z");
    mvwaddstr(controle, 4, 3, "> GAUCHE : Q");
    mvwaddstr(controle, 6, 3, "> DROITE : D");
    mvwaddstr(controle, 8, 3, "> PAUSE :  P");

    wrefresh(controle);
}

void affichageMenu(WINDOW * menu, int choix) {
    char elem1[255], elem2[255], elem3[255];
    int p1, p2, p3;

    switch (choix) {
        case 0:
            snprintf(elem1, 255, "> %s <", ELEM1);
            strcpy(elem2, ELEM2);
            strcpy(elem3, ELEM3);
            p1 = 4;
            p2 = 0;
            p3 = 0;
            break;
        case 1:
            snprintf(elem2, 255, "> %s <", ELEM2);
            strcpy(elem1, ELEM1);
            strcpy(elem3, ELEM3);
            p1 = 0;
            p2 = 4;
            p3 = 0;
            break;
        case 2:
            snprintf(elem3, 255, "> %s <", ELEM3);
            strcpy(elem2, ELEM2);
            strcpy(elem1, ELEM1);
            p1 = 0;
            p2 = 0;
            p3 = 4;
            break;
    }
    wclear(menu);
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwaddstr(menu, 5, 1+(WIDTH_MENU - (strlen(ELEM1) + p1)) / 2, elem1);
    mvwaddstr(menu, 10, 1+(WIDTH_MENU - (strlen(ELEM2) + p2)) / 2, elem2);
    mvwaddstr(menu, 15, 1+(WIDTH_MENU - (strlen(ELEM3) + p3)) / 2, elem3);
    wrefresh(menu);
}

void actionMenu(WINDOW * menu) {
    int ch = 0;
    int pressed;
    affichageMenu(menu, ch);
    while ((pressed = wgetch(menu)) != 'k') {
        if (pressed == 'z') {
            ch = abs((3 + ch - 1) % 3);
            affichageMenu(menu, ch);
        }
        if (pressed == 's') {
            ch = (ch + 1) % 3;
            affichageMenu(menu, ch);
        }
        if (pressed == 10) {
            if (ch == 2) {
                break;
            }
        }
    }
}