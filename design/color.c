#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void changeConsoleColor(int textColor) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
#else
    printf("\033[%dm", 30 + textColor);
#endif
}

int main() {
    int textColor;
    
    printf("Entrez un code couleur de texte (0-7) : ");
    scanf("%d", &textColor);
    
    if (textColor < 0 || textColor > 7) {
        printf("Codes couleur invalides ! Utilisation des couleurs par défaut.\n");
    } else {
        changeConsoleColor(textColor);
        printf("Couleurs changees !\n");
    }
    
    printf("Appuyez sur une touche pour quitter...\n");
    getchar();
    getchar();
#ifdef _WIN32
    system("pause");
#else
    printf("\033[0m"); // Réinitialiser les couleurs
#endif
    return 0;
}

