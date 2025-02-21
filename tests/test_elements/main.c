#include "header.h"

int main() {

    srand(time(NULL));

    int size = 64;
    struct Element ** tabElem = creerTabElem(size);
    (tabElem == NULL) ? printf("ERR : tabElem est NULL\n") : printf("SUCCESS : tabElem créé\n");

    while (1) {
        (!ajouterElem(tabElem, size, randomElem())) ? printf("ERR : ajout a échoué\n") : printf("SUCCESS : ajout a réussi\n");
        sleep(1);
        system("clear");
        affichageTabElem(tabElem, size);

        supprElem(tabElem, 10);
    }

    libTabElem(tabElem, size);

    return 0;
}