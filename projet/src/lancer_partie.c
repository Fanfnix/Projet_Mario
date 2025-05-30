#include "../include/header.h"

Save * lancerPartie(Mix_Music* menuzik, Save * partie, struct Score ** liste_score) {

    int max_fps = 60;
    
    // Initialisation aléatoire
    srand(time(NULL));
    int min_seed = 16807;
    int max_seed = 2147483646;
    int seed;
    if (partie == NULL) {
        seed = ((rand() % (max_seed - min_seed + 1)) + min_seed) / VARIANCE * VARIANCE;  // Le "/ VARIANCE * VARIANCE" est pour s'assurer que la premiere generation sera à Y_MIN pour le raccordement
    } else {
        seed = partie->seed;
    }
    int * table = creerTableSeed();

    // Creation des fenetre
    WIN * tmp;
    WIN * jeu;
    // WIN * mini_jeu;
    WIN * pause;
    WIN * pseudo;

    // Setup dimension fenêtre tmp
    int height_fenetre_tmp = 6;
    int width_fenetre_tmp = COLS;  // COLS renvoie la largeur de la console en mode "ncurses"
    int startx_fenetre_tmp = 0;
    int starty_fenetre_tmp = 0;

    // Setup dimension fenêtre de jeu
    int height_fenetre_jeu = 30;
    int width_fenetre_jeu = COLS;
    int startx_fenetre_jeu = 0;
    int starty_fenetre_jeu = starty_fenetre_tmp + height_fenetre_tmp;

    // Setup dimension fenêtre de pause
    int height_fenetre_pause = 12;
    int width_fenetre_pause = 36;
    int startx_fenetre_pause = (COLS / 2) - 18;
    int starty_fenetre_pause = 10;

    // Setup dimension fenêtre pseudo
    int height_fenetre_pseudo = 12;
    int width_fenetre_pseudo = 36;
    int startx_fenetre_pseudo = (COLS / 2) - 18;
    int starty_fenetre_pseudo = 10;
    // Initialisation du pseudo
    char nom_joueur[10] = "\0";

    // Creer fenetre de jeu
    WINDOW * jeu_fenetre = newwin(height_fenetre_jeu + 2, width_fenetre_jeu, starty_fenetre_jeu, startx_fenetre_jeu);
    jeu = creerFenetre(jeu_fenetre, width_fenetre_jeu, height_fenetre_jeu);
    if (!jeu) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }
	wborder(jeu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(jeu->fenetre);

    // Creer fenetre de pause
    WINDOW* pause_fenetre = newwin(height_fenetre_pause + 2, width_fenetre_pause, starty_fenetre_pause, startx_fenetre_pause);
    pause = creerFenetre(pause_fenetre, width_fenetre_pause, height_fenetre_pause);
    if (!pause) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Creer fenetre demande pseudo
    WINDOW* pseudo_fenetre = newwin(height_fenetre_pseudo + 2, width_fenetre_pseudo, starty_fenetre_pseudo, startx_fenetre_pseudo);
    pseudo = creerFenetre(pseudo_fenetre, width_fenetre_pseudo, height_fenetre_pseudo);
    if (!pseudo) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Creer fenetre tmp
    WINDOW * tmp_fenetre = newwin(height_fenetre_tmp, width_fenetre_tmp, starty_fenetre_tmp, startx_fenetre_tmp);
    tmp = creerFenetre(tmp_fenetre, width_fenetre_tmp, height_fenetre_tmp);
    if (!tmp) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Setup dimension carte
    int height_carte = height_fenetre_jeu / TY;
    int width_carte = (width_fenetre_jeu - 2) / TX;

    // Setup création
    int nb_chunks = width_carte / DISTANCE + 2;

    // Setup dimension fenêtre mini_jeu
    // int height_fenetre_mini_jeu = height_carte;
    // int width_fenetre_mini_jeu = COLS;
    // int startx_fenetre_mini_jeu = 0;
    // int starty_fenetre_mini_jeu = starty_fenetre_jeu + height_fenetre_jeu + 2;

    // WINDOW * mini_jeu_fenetre = newwin(height_fenetre_mini_jeu + 2, width_fenetre_mini_jeu, starty_fenetre_mini_jeu, startx_fenetre_mini_jeu);
    // mini_jeu = creerFenetre(mini_jeu_fenetre, width_fenetre_mini_jeu, height_fenetre_mini_jeu);
    // if (!mini_jeu) {
    //     endwin();  // Sort la console du mode "ncurses"
    //     fprintf(stderr, "Erreur d'allocation mémoire\n");
    //     return NULL;
    // }
	// wborder(mini_jeu->fenetre, '|', '|', '-', '-', '+', '+', '+', '+');
	// wrefresh(mini_jeu->fenetre);

    // Création d'un niveau vide avec mario
    struct Map * niv = creerMap(height_carte, nb_chunks);
    Mario * perso = creerMario();

    // Vérification de la création du niveau
    if (!niv) {
        endwin();  // Sort la console du mode "ncurses"
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Ajout de la génération de base
    struct Chunk * newChunk;
    for (int i = 0; i < nb_chunks; i++) {
        if (partie == NULL) {
            if (i < 3) newChunk = genererChunk(niv, i, NULL, NULL);
            else newChunk = genererChunk(niv, i, table, &seed);
        } else {
            newChunk = genererChunk(niv, i + partie->distance / DISTANCE, table, &seed);
        }

        if (newChunk == NULL) {
            endwin();
            printf("ERR [main] : newChunk == NULL\n");
            return NULL;
        }

        struct Chunk * tmp_first = niv->p_chunk;
        if (niv->p_chunk == NULL) {
            niv->p_chunk = newChunk;
        }
        else {
            while (tmp_first->suivant != NULL) tmp_first = tmp_first->suivant;
            if (newChunk != NULL) tmp_first->suivant = newChunk;
        }
    }

    if (partie == NULL) {
        initMario(perso, niv);
    } else {
        perso->x = partie->posx;
        perso->y = partie->posy;
        perso->vertical_speed = 0.0f;
    }

    nodelay(jeu->fenetre, true);
    keypad(jeu->fenetre, true);

    clock_t begin, end;
    float fps, timediff, supp;
    int nb_frames = 0;
    int tot_sec = 0;
    char txt_fps[255] = "\0";

    int dmax = 0;

    int pressed;

    int quit = 0;

    int cycle_plantes = 0;
    int pos_plantes = 2;

    int anima_drapeau = 0;
    int cycle_drapeau = 0;

    int freeze_frames = 0;

    int goomba_tuee = (partie != NULL) ? partie->goomba_tuee : 0;
    int coin = (partie != NULL) ? partie->coin : 0;
    int lifes = (partie != NULL) ? partie->vies : 3;

    int score = calculScore(perso->x, coin, goomba_tuee);

    Mix_Chunk* coinSE = Mix_LoadWAV("./musique/coin.wav");
    if (!coinSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* jumpSE = Mix_LoadWAV("./musique/jump.wav");
    if (!jumpSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* powerupSE = Mix_LoadWAV("./musique/powerup.wav");
    if (!powerupSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* degatSE = Mix_LoadWAV("./musique/degat.wav");
    if (!degatSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* selectSE = Mix_LoadWAV("./musique/select.wav");
    if (!selectSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* confirmeSE = Mix_LoadWAV("./musique/confirme.wav");
    if (!confirmeSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    Mix_Chunk* mortgoombaSE = Mix_LoadWAV("./musique/mortgoomba.wav");
    if (!mortgoombaSE) {
        printf("Erreur chargement: %s\n", Mix_GetError());
        return NULL;
    }

    FILE * f = popen("echo $XDG_SESSION_TYPE", "r");
    char xorg[512] = {0};
    fgets(xorg, 512, f);
    pclose(f);
    
    system("xset r rate 100 25");

    while (quit == 0 && lifes > 0) {
        pressed = wgetch(jeu->fenetre);
        begin = clock();
        // CODE >>>

        actionGoombas(niv);
        actionMario(perso, niv);

        afficherTmp(tmp, dmax, lifes, score);

        int test_d;

        switch (pressed) {
            case KEY_RIGHT:
                if (!verifDroite(niv, perso->x, perso->y)) perso->x++;
                if (convInt(perso->x) - dmax >= (jeu->width / 3 / TX)) dmax++;
                if ((convInt(perso->x) % DISTANCE) == 0 && (convInt(perso->x) - dmax + 1) == (jeu->width / 3 / TX)) {
                    struct Chunk* tmp_chunk = niv->p_chunk;
                    while (tmp_chunk->suivant != NULL) tmp_chunk = tmp_chunk->suivant;
                    if ((tmp_chunk->id + 1) == dmax / DISTANCE + niv->nb_chunks) {
                        avancerMapChunk(niv, table, &seed);
                    }
                }
                break;
            case KEY_LEFT:
                if (convInt(perso->x) - dmax > 0 && !verifGauche(niv, perso->x, perso->y)) perso->x--;
                break;
            case 32:
                if (verifSol(niv, perso->x, perso->y) == 1) {
                    perso->y--;
                    perso->vertical_speed -= 0.9f;
                    Mix_PlayChannel(-1, jumpSE, 0);
                }
                break;
            case 27:
                system("xset r rate 500 33");
                quit = actions_menu(pause, selectSE,confirmeSE);
                system("xset r rate 100 25");
        }

        if (!verifHaut(niv, perso->x, perso->y, perso->vertical_speed)) perso->vertical_speed = 0.0f;

        if (surGoomba(niv, perso->x, perso->y, &goomba_tuee) == 0) {
            perso->y--;
            perso->vertical_speed -= 0.9f;
            Mix_PlayChannel(-1, mortgoombaSE, 0);
        }


        getCoin(niv, perso->x, perso->y, &coin, coinSE);
        getLife(niv, perso->x, perso->y, &lifes, powerupSE);

        touchePlante(niv, perso->x, perso->y, &lifes, degatSE, pos_plantes, &freeze_frames);
        dansGoomba(niv, perso->x, perso->y, &lifes, degatSE, &freeze_frames);

        score = calculScore(dmax + (perso->x - dmax), coin, goomba_tuee);

        int dmax_affichage = (partie != NULL) ? partie->distance : 0;

        // afficherMap_simp(mini_jeu, niv, perso, dmax + dmax_affichage);
        afficherMap(jeu, niv, dmax + dmax_affichage, pos_plantes);
        affichageMario(jeu, perso, dmax + dmax_affichage);

        if (freeze_frames != 0) freeze_frames--;

        cycle_plantes++;
        if (cycle_plantes == 10) pos_plantes = 3;
        if (cycle_plantes == 110) pos_plantes = 2;
        if (cycle_plantes == 120 || cycle_plantes == 230) pos_plantes = 1;
        if (cycle_plantes == 130) pos_plantes = 0;
        if (cycle_plantes == 240) {
            cycle_plantes = 0;
            pos_plantes = 2;
        }

        if (niv->flag != NULL) if (perso->x == convInt(niv->flag->x)) {
            if (niv->partie == NULL) niv->partie = malloc(sizeof(Save));
            if (niv->partie != NULL) {
                if (niv->partie->posx != perso->x) {
                    niv->partie->seed = seed;
                    niv->partie->distance = dmax + (perso->x - dmax);
                    niv->partie->coin = coin;
                    niv->partie->goomba_tuee = goomba_tuee;
                    niv->partie->posx = perso->x;
                    niv->partie->posy = perso->y;
                    niv->partie->vies = lifes;
                }
            }
            anima_drapeau = 1;
        }
        if (anima_drapeau == 1) {
            cycle_drapeau++;
            if (cycle_drapeau % 10 == 0 && cycle_drapeau <= 60) niv->flag->frame++;
            if (cycle_drapeau == 70) {
                cycle_drapeau = 0;
                anima_drapeau = 0;
            }
        }

        // <<< CODE
        end = clock();
        timediff = (float)(end - begin) / CLOCKS_PER_SEC;
        supp = (1.0f / max_fps) - timediff;
        if (supp > 0.0f) usleep(1000000 * supp);
        fps = 1.0f / (timediff + supp);
        nb_frames++;
        if (nb_frames >= max_fps+1) {
            nb_frames = 0;
            tot_sec++;
        }
        txt_fps[0] = '\0';
        snprintf(txt_fps, 254, "FPS : %.1lf | NB_FRAMES : %d | TOT_SEC : %d", fps, nb_frames, tot_sec);
        mvwaddstr(jeu->fenetre, 1, 1, txt_fps);
        wrefresh(jeu->fenetre);

    }

    system("xset r rate 500 33");
    if (lifes > 0) {
        for(int i = 0; i < 10; i++) {
            if (liste_score[i] != NULL) liste_score[i]->id = i;
            else {
                char * nom_tmp = choix_pseudo(pseudo, nom_joueur);
                if (nom_tmp == NULL) break;
                liste_score[i] = malloc(sizeof(struct Score));
                if (liste_score[i] != NULL) {
                    strcpy(liste_score[i]->pseudo, nom_tmp);
                    liste_score[i]->score = score;
                    if (i > 0)
                        if (liste_score[i-1] != NULL)
                            liste_score[i]->id = liste_score[i-1]->id + 1;
                        else
                            liste_score[i]->id = i;
                }
                break;
            }
        }
    }
    
    Mix_HaltMusic();
    Mix_PlayMusic(menuzik, -1);

    // Libération de la mémoire : niveau et table aléatoire
    Mix_FreeChunk(coinSE);
    Mix_FreeChunk(jumpSE);
    Mix_FreeChunk(powerupSE);
    Mix_FreeChunk(degatSE);
    Mix_FreeChunk(selectSE);
    Mix_FreeChunk(confirmeSE);
    Mix_FreeChunk(mortgoombaSE);

    Save * save = niv->partie;

    libMemMap(niv);
    free(table);
    table = NULL;

    supprWin(jeu);
    supprWin(tmp);
    // supprWin(mini_jeu);
    supprWin(pause);

    libMario(perso);

    return save;
}