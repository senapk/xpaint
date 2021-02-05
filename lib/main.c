#define XPAINT_FULL
#include <stdio.h>
#include "base.h"
#include "draw.h"
#include "text.h"
#include "modules.h"

int main(){
    srand(time(NULL));
    x_open(1000, 600, "figura_draw");
    x_set_viewer("eog");

    x_set_color(X_COLOR_GREEN);

    x_fill_circle(200, 200, 300);
    x_set_color(X_COLOR_WHITE);
    x_fill_arc(200, 200, 150, 50, 190, 100);

    x_pen_set_thick(30);
    x_pen_set_pos(150, 100);
    x_pen_set_angle(-20);
    for(int i = 0; i < 5; i++){
        x_pen_walk(500);
        x_set_color(x_make_color(rand() % 256, rand() % 256, rand() % 256, 255));
        x_pen_rotate(-144);
    }

    x_save();
    x_close();
    return 0;
}

ler capacidade
total = 0
while total < 2 * capacidade
    ler valor
    total += valor
    if total == 0
        vazio
    else if total < capacidade
        ainda cabe
    else if total < 2 * capacidade
        lotado
    else
        hora de partir