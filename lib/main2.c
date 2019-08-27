#include "base.h"
#include "draw.h"
#include <stdio.h>
#include "text.h"
#include "modules.h"

int main(){

    x_open(800, 800, "img");
    x_set_viewer("eog");
    x_set_color(X_COLOR_BLACK);
    x_clear();
    x_set_color(x_make_color(0, 0, 255, 150));
    x_fill_rect(50, 50, 400, 300);
    x_set_color(x_make_color(0, 255, 0, 150));
    x_fill_rect(250, 250, 400, 300);
    x_set_color(x_make_color(255, 0, 0, 150));
    //x_fill_ellipse(300, 300, 200, 400);
    x_fill_ellipse(50, 70, 350, 500);


    x_set_color(x_make_color(255, 0, 0, 150));
    x_pen_set_pos(100, 350);
    x_pen_set_thick(50);
    x_pen_set_angle(-45);
    x_pen_walk(400);
    x_pen_rotate(90);
    x_pen_walk(400);
    x_pen_rotate(90);
    x_pen_walk(400);
    x_pen_rotate(90);
    x_pen_walk(400);
    x_pen_rotate(90);

    x_set_font_size(50);
    x_set_color(x_make_color(200, 200, 0, 255));
    __x_make_layer();
    x_write(100, 100, "Hoje vamos a uma festa e vai ser demais");
    x_save();
    x_close();
}
