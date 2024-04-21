#define XPAINT
#include "xpaint.h"


int main(){
    open(1000, 600, "figura_draw");
    stroke_char('k');
    background();

    /* cada exemplo vai ser apresentado num espaço de 200x200 pixels */
    set_font_size(30);
    stroke(YELLOW);
    write(90, 30, "Exemplo das funções de desenho de\n         formas geométricas");

    stroke(WHITE);
    set_font_size(20);
    int x = 10;
    int y = 100;
    write(x, y, "draw_line");
    draw_line(x + 30, y + 30, x + 180, y + 180);

    x += 200;
    write(x, y, "fill_line");
    fill_line(x + 30, y + 30, x + 180, y + 180, 30);

    x += 200;
    write(x, y, "draw_circle");
    draw_circle(x + 100, y + 100, 80);

    x += 200;
    write(x, y, "draw_ellipse");
    draw_ellipse(x + 20, y + 50, 180, 100);  

    x += 200;
    write(x, y, "draw_bezier");
    draw_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

    x = 10;
    y += 250;
    write(x, y, "fill_arc");
    fill_arc(x + 100, y + 100, 80, 30, 30, 290);

    x += 200;
    write(x, y, "raw_fill_triangle");
    raw_fill_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

    x += 200;
    write(x, y, "fill_circle");
    fill_circle(x + 100, y + 100, 80);

    x += 200;
    write(x, y, "fill_ellipse");
    fill_ellipse(x + 20, y + 50, 180, 100);  

    x += 200;
    write(x, y, "fill_rect");
    fill_rect(x + 30, y + 50, 120, 100);  

    save();
    close();
    return 0;
}