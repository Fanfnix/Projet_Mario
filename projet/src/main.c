#include "../include/header.h"

int main() {

    WIN * logo;
    WIN * menu;
    WIN * choix;
    WIN * controle;
    WIN * eloise;
    WIN * ascii;
    WIN * blocpiece;

    srand(time(NULL));

    struct Score ** liste_score;
    Save ** liste_sauvegarde;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Echec INIT_AUDIO\n");
        return 0;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Echec Open_Audio\n");
        return 0;
    }

    // Creer musique/sons

    Mix_Music * menuzik = Mix_LoadMUS("../musique/monbeaumenu.mp3");
    if (!menuzik) {
        printf("Echec Mix_LoadMUS\n");
        return 0;
    }

    Mix_Music* jeuzik = Mix_LoadMUS("../musique/allan-venture.mp3");
    if (!jeuzik) {
        printf("Echec Mix_LoadMUS\n");
        return 0;
    }

    Mix_Chunk* selectSE = Mix_LoadWAV("../musique/select.wav");
    if (!selectSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return 0;
    }

    Mix_Chunk* degatSE = Mix_LoadWAV("../musique/degat.wav");
    if (!degatSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return 0;
    }

    Mix_Chunk* confirmeSE = Mix_LoadWAV("../musique/confirme.wav");
    if (!confirmeSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return 0;
    }

    initscr();
    curs_set(0);
    noecho();
    set_escdelay(25);

    logo = creerWindowLogo();
    controle = creerWindowControle();
    eloise = creerWindowEloise();
    menu = creerWindowMenu();
    choix = creerWindowChoix();

    blocpiece = creerWindowBlocpiece(choix);
    ascii = creerWindowAscii(choix);

    affichageGenerale(logo, controle, eloise);

    liste_score = recupHiscores();
    liste_sauvegarde = recupCheckpoint();

    Save * save = NULL;

    int id = 0;
    int id_choix = 0;
    int run = 1;
    Mix_PlayMusic(menuzik, -1);
    do {
        actionMenuPrincipal(menu, &id, selectSE, confirmeSE);
        switch (id) {
            case 0: nettoyerMenu(logo, menu, choix, controle, eloise, ascii, blocpiece);
                Mix_HaltMusic();
                Mix_PlayMusic(jeuzik, -1);
                save = lancerPartie(menuzik, NULL);
                break;
            case 1: actionHiscores(choix, ascii, blocpiece, liste_score, &id_choix, selectSE, degatSE); break;
            case 2: if (actionSauvegarde(choix, ascii, blocpiece, liste_sauvegarde, &id_choix, selectSE, degatSE)) {
                        nettoyerMenu(logo, menu, choix, controle, eloise, ascii, blocpiece);
                        Mix_HaltMusic();
                        Mix_PlayMusic(jeuzik, -1);
                        save = lancerPartie(menuzik, liste_sauvegarde[id_choix]);
                    };
                    break;
            case 3: run = 0; break;
        }
        affichageGenerale(logo, controle, eloise);
    } while (run);

    supprWin(logo);
    supprWin(menu);
    supprWin(choix);
    supprWin(controle);
    supprWin(eloise);
    supprWin(ascii);
    supprWin(blocpiece);

    endwin();

    Mix_FreeMusic(menuzik);
    Mix_FreeMusic(jeuzik);
    Mix_FreeChunk(selectSE);
    Mix_FreeChunk(degatSE);
    Mix_FreeChunk(confirmeSE);
    Mix_CloseAudio();
    SDL_Quit();

    if (save != NULL) {
        for (int i = 0; i < 10; i++) {
            if (liste_sauvegarde[i] == NULL) {
                liste_sauvegarde[i] = save;
                break;
            }
        }
    }

    trierHiscores(liste_score);
    ecritureHiscores(liste_score);
    ecritureSauvegarde(liste_sauvegarde);

    libererHiscores(liste_score);
    libererSauvegarde(liste_sauvegarde);
        
    return 0;
}