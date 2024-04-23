#define XPAINT
#include "xpaint.h"

int main() {
    open(600, 600, "figura_cores");
    textSize(40);

    stroke(BLACK);
    __fill_rect(20, 60, 560, 410);
    stroke(WHITE);
    __fill_rect(190, 70, 200, 340);

    int x = 300;
    stroke(RED);    text(60, 70, "    Red");
    stroke(GREEN);  text(x, 70,  "Green");
    stroke(BLUE);   text(60, 140,"   Blue");
    stroke(YELLOW); text(x, 140, "Yellow");
    stroke(CYAN);   text(60, 210,"   Cyan");
    stroke(MAGENTA);text(x, 210, "Maguenta");
    stroke(VIOLET); text(60, 280," Violet");
    stroke(ORANGE); text(x, 280, "Orange");
    stroke(BLACK);  text(x - 100, 350, "Black");
    stroke(WHITE);  text(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        textSize(40);
        int i;
        for(i = 0; i < 10; i++){
            stroke(getPalette(i));
            x = text(x, 500, "%c", colors[i]);
        }
    }

    textSize(20);
    stroke(WHITE);
    text(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    text(40, 480, "Na paleta, cada letra corresponde a uma cor.");

    save();

    close();
    return 0;
}


