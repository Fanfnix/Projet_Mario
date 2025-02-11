#include "fct.h"

// void affichageRetromario(WINDOW * win, int width, int height) {
//     char chemin[] = "retromario/retromario1.txt";
//     FILE * retromario = fopen(chemin, "r");

//     clear();

//     for (int y = 0; y < height; y++) {
//         char tmp[width+1];
//         fgets(tmp, width+1, retromario);

//         for (int x = 0; x < strlen(tmp); x++) {
//             if (tmp[x] == '0') {
//                 tmp[x] = ' ';
//             }
//         }
//         mvwaddstr(win, y+1, 1, tmp);
//     }
//     fclose(retromario);
// }

void affichageRetromario(WINDOW * win) {
    char chemin[] = "../../design/retromario/retromario1.txt";
    FILE * file = fopen(chemin, "r");

    for (int y = 0; y < HEIGHT_LOGO; y++) {
        char tmp[WIDTH_LOGO+1];
        fgets(tmp, WIDTH_LOGO+1, file);
        for (int i = 0; i < strlen(tmp); i++) {
            if (tmp[i] == '0') {
                tmp[i] = ' ';
            }
        }
        mvwaddstr(win, y+1, 1, tmp);
    }
    wrefresh(win);
    fclose(file);
}