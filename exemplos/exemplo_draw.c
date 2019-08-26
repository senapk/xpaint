#define XPAINT_FULL
#include "../xpaint.h"

void x_set_pcolor(char c){
    x_set_color(x_get_palette(c));
}

int main(){
    x_open(1000, 600, "figura_draw");
    x_set_pcolor('k');
    x_clear();

    /* cada exemplo vai ser apresentado num espaço de 200x200 pixels */
    x_set_font_size(35);
    x_set_pcolor('g');
    x_write(30, 30, "Exemplo das funcoes de desenho de formas geometricas");

    x_set_pcolor('w');
    x_set_font_size(20);
    int x = 10;
    int y = 100;
    x_write(x, y, "x_draw_line");
    x_draw_line(x + 30, y + 30, x + 180, y + 180);

    x += 200;
    x_write(x, y, "x_fill_line");
    x_fill_line(x + 30, y + 30, x + 180, y + 180, 3);

    x += 200;
    x_write(x, y, "x_draw_circle");
    x_draw_circle(x + 100, y + 100, 80);

    x += 200;
    x_write(x, y, "x_draw_ellipse");
    x_draw_ellipse(x + 20, y + 50, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "x_draw_bezier");
    x_draw_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

    x = 10;
    y += 250;
    x_write(x, y, "x_fill_arc");
    x_fill_arc(x + 100, y + 100, 80, 30, 30, 290);

    x += 200;
    x_write(x, y, "x_fill_triangle");
    x_fill_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "x_fill_circle");
    x_fill_circle(x + 100, y + 100, 80);

    x += 200;
    x_write(x, y, "x_fill_ellipse");
    x_fill_ellipse(x + 20, y + 50, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "x_fill_rect");
    x_fill_rect(x + 30, y + 50, 120, 100);  

    x_save();
    x_close();
    return 0;
}