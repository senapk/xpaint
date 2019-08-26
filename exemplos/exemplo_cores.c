#define XPAINT_FULL
#include "../xpaint.h"

int main() {
    x_open(600, 600, "figura_cores");
    x_set_font_size(70);

    x_set_color(X_COLOR_BLACK);
    x_fill_rect(20, 60, 560, 410);
    x_set_color(X_COLOR_WHITE);
    x_fill_rect(190, 70, 200, 340);

    int x = 300;
    x_set_color(X_COLOR_RED);    x_write(20, 70, "    RED");
    x_set_color(X_COLOR_GREEN);  x_write(x, 70,  "GREEN");
    x_set_color(X_COLOR_BLUE);   x_write(20, 140,"   BLUE");
    x_set_color(X_COLOR_YELLOW); x_write(x, 140, "YELLOW");
    x_set_color(X_COLOR_CYAN);   x_write(20, 210,"   CYAN");
    x_set_color(X_COLOR_MAGENTA);x_write(x, 210, "MAGUENTA");
    x_set_color(X_COLOR_VIOLET); x_write(20, 280," VIOLET");
    x_set_color(X_COLOR_ORANGE); x_write(x, 280, "ORANGE");
    x_set_color(X_COLOR_BLACK);  x_write(x - 100, 350, "BLACK");
    x_set_color(X_COLOR_WHITE);  x_write(x - 100, 410, "WHITE");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        x_set_font_size(100);
        int i;
        for(i = 0; i < 10; i++){
            x_set_color(x_get_palette(colors[i]));
            x = x_write(x, 500, "%c", colors[i]);
        }
    }

    x_set_font_size(25);
    x_set_color(X_COLOR_WHITE);
    x_write(40, 20, "cores.png : Cores do copiadas do solarized.");
    x_write(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    x_save();

    x_close();
    return 0;
}


