#define XPAINT
#include "xpaint.h"

int main() {
    open(600, 600, "figura_cores");
    x_set_font_size(40);

    stroke(BLACK);
    x_fill_rect(20, 60, 560, 410);
    stroke(WHITE);
    x_fill_rect(190, 70, 200, 340);

    int x = 300;
    stroke(RED);    x_write(60, 70, "    Red");
    stroke(GREEN);  x_write(x, 70,  "Green");
    stroke(BLUE);   x_write(60, 140,"   Blue");
    stroke(YELLOW); x_write(x, 140, "Yellow");
    stroke(CYAN);   x_write(60, 210,"   Cyan");
    stroke(MAGENTA);x_write(x, 210, "Maguenta");
    stroke(VIOLET); x_write(60, 280," Violet");
    stroke(ORANGE); x_write(x, 280, "Orange");
    stroke(BLACK);  x_write(x - 100, 350, "Black");
    stroke(WHITE);  x_write(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        x_set_font_size(40);
        int i;
        for(i = 0; i < 10; i++){
            stroke(x_get_palette(i));
            x = x_write(x, 500, "%c", colors[i]);
        }
    }

    x_set_font_size(20);
    stroke(WHITE);
    x_write(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    x_write(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    save();

    close();
    return 0;
}


