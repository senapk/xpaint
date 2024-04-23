#define XPAINT
#include "xpaint.h"


int main(){
    open(1000, 600, "figura_draw");
    stroke_char('k');
    background();

    /* cada exemplo vai ser apresentado num espaço de 200x200 pixels */
    textSize(30);
    stroke(YELLOW);
    text(90, 30, "Exemplo das funções de desenho de\n         formas geométricas");

    stroke(WHITE);
    textSize(20);
    int x = 10;
    int y = 100;
    text(x, y, "__draw_line");
    __draw_line(x + 30, y + 30, x + 180, y + 180);

    x += 200;
    text(x, y, "__fill_line");
    __fill_line(x + 30, y + 30, x + 180, y + 180, 30);

    x += 200;
    text(x, y, "__draw_circle");
    __draw_circle(x + 100, y + 100, 80);

    x += 200;
    text(x, y, "__draw_ellipse");
    __draw_ellipse(x + 20, y + 50, 180, 100);  

    x += 200;
    text(x, y, "draw_bezier");
    draw_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

    x = 10;
    y += 250;
    text(x, y, "arc");
    arc(x + 100, y + 100, 80, 30, 30, 290);

    x += 200;
    text(x, y, "__fill_raw_triangle");
    __fill_raw_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

    x += 200;
    text(x, y, "__fill_circle");
    __fill_circle(x + 100, y + 100, 80);

    x += 200;
    text(x, y, "__fill_ellipse");
    __fill_ellipse(x + 20, y + 50, 180, 100);  

    x += 200;
    text(x, y, "__fill_rect");
    __fill_rect(x + 30, y + 50, 120, 100);  

    save();
    close();
    return 0;
}