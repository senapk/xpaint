#define XPAINT_FULL
#include <stdio.h>
#include "base.h"
#include "draw.h"
#include "text.h"
#include "modules.h"

int main(){
    x_open(1000, 600, "figura_draw");
    x_set_viewer("eog");
    x_set_color(X_COLOR_BLACK);
    x_clear();

    x_set_color(X_COLOR_GREEN);
/*     x_pen_set_pos(300, 400);
    x_pen_set_angle(90);
    x_pen_walk(50); */
    x_pen_set_thick(10);
    x_pen_walk(200);
    x_pen_rotate(30);
    x_pen_walk(100);
    //x_fill_line(50, 50, 70, 70, 3);

    x_save();
    x_close();
    return 0;
}