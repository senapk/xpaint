#include "../src/all.h"


void draw_square(int x, int y, int size){
    draw_line(x, y, x + size, y);
    draw_line(x + size, y, x + size, y + size);
    draw_line(x + size, y + size, x, y + size);
    draw_line(x, y + size, x, y);
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
        fill_rect(-50, -50, 100, 100);
        stroke_char('r');
        fill_char('r');
        fill_ellipse(0, 0, 40, 80);
        pop();
    }
    save();
    close();
    return 0;
}