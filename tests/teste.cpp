#include <iostream>
#include "base.h"
#include "color.h"
#include "draw.h"
#include "modules.h"


int main() {
    srand(time(NULL));
    open(1000, 600, "figura_draw");
    stroke(color(0, 0, 0, 150));
    background();
    stroke_char('g');

    __fill_circle(200, 200, 300);
    stroke(WHITE);
    arc(200, 200, 150, 50, 190, 100);

    pen_set_thick(30);
    pen_set_pos(150, 100);
    pen_set_angle(-20);
    for(int i = 0; i < 5; i++){
        pen_walk(500);
        stroke(color(rand() % 256, rand() % 256, rand() % 256, 255));
        pen_rotate(-144);
    }
    save();
    close();
}
