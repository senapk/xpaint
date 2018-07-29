#include <stdio.h>

#include "libs/ximage.h"
#include "libs/xdraw.h"

int main(){
    x_open(1000, 600);
    x_clear(BLACK);

    //cada exemplo vai ser apresentado num espaço de 200x200 pixels
    xs_font_size(35);
    xs_color(GREEN);
    x_write(30, 30, "Exemplo das funcoes de desenho de formas geometricas");

    xs_color(WHITE);
    xs_font_size(20);
    int x = 10;
    int y = 100;
    x_write(x, y, "xd_line");
    xd_line(x + 30, y + 30, x + 180, y + 180);

    x += 200;
    x_write(x, y, "xd_thick_line");
    xd_thick_line(x + 30, y + 30, x + 180, y + 180, 3);

    x += 200;
    x_write(x, y, "xd_circle");
    xd_circle(x + 100, y + 100, 80);

    x += 200;
    x_write(x, y, "xd_elipse");
    xd_ellipse(x + 20, y + 50, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "xd_bezier");
    xd_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

    x = 10;
    y += 250;
    x_write(x, y, "xd_filled_arc");
    xd_filled_arc(x + 100, y + 100, 80, 30, 30, 290);

    x += 200;
    x_write(x, y, "xd_filled_triangle");
    xd_filled_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "xd_filled_circle");
    xd_filled_circle(x + 100, y + 100, 80);

    x += 200;
    x_write(x, y, "xd_filled_elipse");
    xd_filled_ellipse(x + 20, y + 50, x + 180, y + 180);  

    x += 200;
    x_write(x, y, "xd_filled_rect");
    xd_filled_rect(x + 30, y + 50, x + 180, y + 180);  

    x_save("exemplo_edraw");
    x_close();
}