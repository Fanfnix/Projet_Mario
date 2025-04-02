#ifndef WIN
#define WIN

typedef struct  WINDOW
{
    int xo;
    int yo;
    int height;
    int width;
    struct WINDOW *precedent;    
}WINDOW;

newwin(int height, int width, int yo, int xo);
delwin(WINDOW *win, int height, int width, int yo, int xo);
wborder(WINDOW *win, char gauche, char droit, char haut, char bas, char haut_g, char haut_d, char bas_g, char bas_d);
wrefresh(WINDOW *win);
mvwaddstr(WINDOW *win, int y, int x, int str);
mvwaddch(WINDOW *win, int y, int x, int ch);


#endif