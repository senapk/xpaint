#define XPAINT
#include "../xpaint.h"

int main() {
    x_open(600, 600, "figura_cores");
    x_write_set_size(40);

    x_color_set(BLACK);
    x_fill_rect(20, 60, 560, 410);
    x_color_set(WHITE);
    x_fill_rect(190, 70, 200, 340);

    int x = 300;
    x_color_set(RED);    x_write(60, 70, "    Red");
    x_color_set(GREEN);  x_write(x, 70,  "Green");
    x_color_set(BLUE);   x_write(60, 140,"   Blue");
    x_color_set(YELLOW); x_write(x, 140, "Yellow");
    x_color_set(CYAN);   x_write(60, 210,"   Cyan");
    x_color_set(MAGENTA);x_write(x, 210, "Maguenta");
    x_color_set(VIOLET); x_write(60, 280," Violet");
    x_color_set(ORANGE); x_write(x, 280, "Orange");
    x_color_set(BLACK);  x_write(x - 100, 350, "Black");
    x_color_set(WHITE);  x_write(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        x_write_set_size(40);
        int i;
        for(i = 0; i < 10; i++){
            x_color_load(colors[i]);
            x = x_write(x, 500, "%c", colors[i]);
        }
    }

    x_write_set_size(20);
    x_color_set(WHITE);
    x_write(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    x_write(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    x_save();

    x_close();
    return 0;
}


