#define XPAINT
#include "base.h"
#include "xmath.h"
#include "color.h"
#include "draw.h"
#include "modules.h"
#include <iostream>

void draw_tree(double size) {
    if (size < 1)
        return;
    int angle = 30;
    double fator = 0.7;
    x_pen_walk(size);
    x_pen_rotate(-angle);
    draw_tree(size * fator);
    x_pen_rotate(2 * angle);
    draw_tree(size * fator);
    x_pen_rotate(-angle);
    x_pen_walk(-size);
}

int main() {
    double fator = 9;
    x_open(500 * fator, 350 * fator, "img_tree");
    x_pen_set_thick(1);
    x_pen_set_angle(90);
    x_pen_set_pos(250 * fator, 350 * fator);
    draw_tree(100 * fator);

    x_color_set(255, 0, 0, 150);
    x_fill_triangle(100, 100, 300, 100, 300, 300);
    x_color_set(0, 255, 0, 180);
    x_fill_triangle(200, 250, 400, 0, 260, 300);
    

    x_save();
    x_close();
}