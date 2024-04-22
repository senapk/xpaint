#include "../src/all.h"


void draw_square(int x, int y, int size){
    line(x, y, x + size, y);
    line(x + size, y, x + size, y + size);
    line(x + size, y + size, x, y + size);
    line(x, y + size, x, y);
}

int main(){
    open(1200, 1200, "zz_roda");
    stroke_char('w');
    fill_char('w');
    background(BLACK);

    for (int i = 0; i < 5; i++) {
        push();
        translate(i * 200, i * 200);
        stroke_char('w');
        fill_char('w');
        rotate(9 * i);
        scale(1 + 0.5 * i);
        __fill_rect(-50, -50, 100, 100);
        stroke_char('g');
        fill_char('r');
        no_fill();
        circle(0, 0, 70);
        // fill_char('g');
        ellipse(0, 0, 100, 50);
        pop();
    }
    save();
    close();
    return 0;
}