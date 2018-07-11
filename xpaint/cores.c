#include <stdio.h>

#if 1
#include "ximage.h"
#include "xdraw.h"
#include "xvet.h"
#include "stdlib.h"
#else
#define   X_FULL
#include "xdraw.h"
#endif


#define SWAP(x, y) do {x = x ^ y; y = y ^ x; x = x ^ y;} while(0)
int main() {

//pegar monokai bright and dark colors e usar como RGB rgb
//COLOR_BBLUE, COLOR_DBLUE

#if 1
    //teste de cores
    x_init(600, 600);
    xs_font_size(70);

    xs_color(BLACK);
    xd_filled_square(20, 60, 580, 470);
    //xd_filled_triangle(20, 60, 280, 460, 280, 60);
    xs_color(WHITE);
    xd_filled_square(190, 70, 390, 410);

    int x = 300;
    xs_color(RED);    x_write(20, 70, "    RED");
    xs_color(GREEN);  x_write(x, 70,  "GREEN");
    xs_color(BLUE);   x_write(20, 140,"   BLUE");
    xs_color(YELLOW); x_write(x, 140, "YELLOW");
    xs_color(CYAN);   x_write(20, 210,"   CYAN");
    xs_color(MAGENTA);x_write(x, 210, "MAGUENTA");
    xs_color(VIOLET); x_write(20, 280," VIOLET");
    xs_color(ORANGE); x_write(x, 280, "ORANGE");
    xs_color(BLACK);  x_write(x - 100, 350, "BLACK");
    xs_color(WHITE);  x_write(x - 100, 410, "WHITE");
    char * colors = "rgbymcwkvo";
    x = 50;
    xs_font_size(100);
    for(int i = 0; i < 10; i++){
        xs_color(xg_pallete(colors[i]));
        x = x_write(x, 500, "%c", colors[i]);
    }

    xs_font("font_alex.ttf");
    xs_font_size(50);
    xs_color(YELLOW);
    x_write(30, 0, "cores.png : Cores do copiadas do solarized.");
    x_write(15, 470, "Na paleta, cada letra corresponde a uma cor.");
    // e seus respectivos caracteres na paleta de cores

    x_save("cores.png");

    x_close();
    return 0;
#endif

#if 0
    x_init(600, 600);
    int vet[34];
    int size = sizeof(vet)/sizeof(int);
    int i, j;

    for(i = 0; i < size; i++)
        vet[i] = rand() % 500;
    {
        int indices[] = {0, 2, 4, size - 1};
        xc_vet_show(vet, size, indices, "rgbv");
    }

    //selection sort
    for(i = 1; i < size; i++){
        for(j = i; j > 0; j--){
            if(vet[j] < vet[j - 1])
                SWAP(vet[j], vet[j - 1]);
            else
                break;
        }
    }
    {
        x_clear(BLACK);
        xc_vet_show(vet, size, NULL, "");
        x_save("vet.png");
        getchar();
        //printf("%d, ", cont++);
    }
    x_close();


#endif

    return 0;
}


