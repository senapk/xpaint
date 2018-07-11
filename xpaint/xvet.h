#ifndef XVET_H
#define XVET_H

#include "ximage.h"
#include "xdraw.h"
#include "string.h"

void __xc_vet_draw_i(int * vet, int i, int thick, int delta, int xbase, int ybase){
    int x = xbase + i * (thick + delta);
    int j;
    for(j = 0; j < thick; j++)
        xd_line(x + j, ybase, x + j, ybase - vet[i]);
}

void xc_vet_show(int * vet, int qtd, int * indices, char * colors){
    x_clear(BLACK);
    int ybase = xg_height() - 10;
    static int xbase = 10;
    static int delta = 2;
    float thick = (xg_width() -10 + delta - qtd * delta) / (float) qtd;

    int i = 0;
    xs_color(WHITE);
    for(i = 0; i < qtd; i++)
        __xc_vet_draw_i(vet, i, thick, delta, xbase, ybase);

    int qtd_indices = strlen(colors);
    int j = 0;
    for(j = 0; j < qtd_indices; j++){
        i = indices[j];
        xs_color(xg_pallete(colors[j]));
        __xc_vet_draw_i(vet, i, thick, delta, xbase, ybase);
    }
}

#endif // XVET_H
