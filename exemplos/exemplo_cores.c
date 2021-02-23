#define XPAINT
#include "../xpaint.h"

int main() {
    x_open(600, 600, "figura_cores");
    x_set_viewer("eog");
    x_set_font_size(40);

    x_set_color(BLACK);
    x_fill_rect(20, 60, 560, 410);
    x_set_color(WHITE);
    x_fill_rect(190, 70, 200, 340);

    int x = 300;
    x_set_color(RED);    x_write(60, 70, "    Red");
    x_set_color(GREEN);  x_write(x, 70,  "Green");
    x_set_color(BLUE);   x_write(60, 140,"   Blue");
    x_set_color(YELLOW); x_write(x, 140, "Yellow");
    x_set_color(CYAN);   x_write(60, 210,"   Cyan");
    x_set_color(MAGENTA);x_write(x, 210, "Maguenta");
    x_set_color(VIOLET); x_write(60, 280," Violet");
    x_set_color(ORANGE); x_write(x, 280, "Orange");
    x_set_color(BLACK);  x_write(x - 100, 350, "Black");
    x_set_color(WHITE);  x_write(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        x_set_font_size(40);
        int i;
        for(i = 0; i < 10; i++){
            x_set_pcolor(colors[i]);
            x = x_write(x, 500, "%c", colors[i]);
        }
    }

    x_set_font_size(20);
    x_set_color(WHITE);
    x_write(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    x_write(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    x_save();

    x_close();
    return 0;
}


