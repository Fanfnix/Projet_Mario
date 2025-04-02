#ifndef WIN
#define WIN

typedef struct  
{
    int xo;
    int yo;
    int height;
    int width;
    WINDOW *precedent;    
}WINDOW;

newwin(height, width, yo, xo);
delwin(win, height, width, yo, xo);
wborder(win, "...");
wrefresh();
mvwaddstr(win, y, x, str);
mvwaddch(win, y, x, ch);


#endif