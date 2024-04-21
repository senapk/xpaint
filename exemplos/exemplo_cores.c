#define XPAINT
#include "xpaint.h"

int main() {
    open(600, 600, "figura_cores");
    set_font_size(40);

    stroke(BLACK);
    fill_rect(20, 60, 560, 410);
    stroke(WHITE);
    fill_rect(190, 70, 200, 340);

    int x = 300;
    stroke(RED);    write(60, 70, "    Red");
    stroke(GREEN);  write(x, 70,  "Green");
    stroke(BLUE);   write(60, 140,"   Blue");
    stroke(YELLOW); write(x, 140, "Yellow");
    stroke(CYAN);   write(60, 210,"   Cyan");
    stroke(MAGENTA);write(x, 210, "Maguenta");
    stroke(VIOLET); write(60, 280," Violet");
    stroke(ORANGE); write(x, 280, "Orange");
    stroke(BLACK);  write(x - 100, 350, "Black");
    stroke(WHITE);  write(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        set_font_size(40);
        int i;
        for(i = 0; i < 10; i++){
            stroke(get_palette(i));
            x = write(x, 500, "%c", colors[i]);
        }
    }

    set_font_size(20);
    stroke(WHITE);
    write(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    write(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    save();

    close();
    return 0;
}


