#ifndef WIN
#define WIN

#include <conio.h>
#include <windows.h>


typedef struct  
{
    int xo;
    int yo;
    int height;
    int width;
    WINDOW *precedent;    
}WINDOW;

#endif