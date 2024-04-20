//#define XPAINT
//#define XPPM
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/all.h"
#include <string.h>
#include <wchar.h>

int main() {
    srand(time(NULL));
    x_open(1000, 600, "zz_figura_draw");
    x_color_set(x_color_make(0, 0, 0, 150));
    x_clear();
    x_color_load('g');

    x_fill_circle(200, 200, 300);
    x_color_set(WHITE);
    x_fill_arc(200, 200, 150, 50, 190, 100);

    x_pen_set_thick(30);
    x_pen_set_pos(150, 100);
    x_pen_set_angle(-20);
    for(int i = 0; i < 5; i++){
        x_pen_walk(500);
        x_color_set(x_color_make(rand() % 256, rand() % 256, rand() % 256, 255));
        x_pen_rotate(-144);
    }
    x_save();
    x_close();
}

