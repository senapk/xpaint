#include "base.h"
#include "draw.h"
#include <stdio.h>

int main(){
    x_open(800, 600, "img");
    x_set_viewer("eog");
    x_set_color(X_COLOR_BLACK);
    x_clear();
    x_set_color(x_make_color(0, 0, 255));
    x_fill_circle(300, 300, 100);
    x_set_color(x_make_color(0, 255, 0));
    x_fill_circle(300, 200, 100);

    x_save();

    x_close();
}
