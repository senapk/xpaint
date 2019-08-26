#include "color.h"
#include "xmath.h"
#include "base.h"
#include <stdio.h>
#include <math.h>
#include "text.h"

int main(){
    X_Color c = x_get_palette('k');
    printf("%d %d %d\n", c.r, c.g, c.b);
    printf("%f\n", xm_cos(45));
    x_open(800, 600, "img");
    x_set_viewer("eog");
    x_set_color(X_COLOR_ORANGE);
    x_set_font_size(80);
    x_write(50, 50, "ola pessoal\nvamos juntos à praia hoje comigo todos voces");
    x_save();
    x_close();
}
