#define XPAINT
#include "xpaint.h"

int main() {
    create(600, 600, "figura_cores");
    textSize(50);
    noStroke();
    background("0");
    fill("black");
    rect(20, 60, 560, 410);
    fill("white");
    ellipse(270, 240, 200, 380);

    int x = 300;
    stroke("red")    ; text(60, 70, "    Red");
    stroke("green")  ; text(x, 70,  "Green");
    stroke("blue")   ; text(60, 140,"   Blue");
    stroke("yellow") ; text(x, 140, "Yellow");
    stroke("cyan")   ; text(60, 210,"   Cyan");
    stroke("magenta"); text(x, 210, "Maguenta");
    stroke("violet") ; text(60, 280," Violet");
    stroke("orange") ; text(x, 280, "Orange");
    stroke("black")  ; text(x - 100, 330, "Black");
    stroke("white")  ; text(x - 100, 410, "White");
    {
        char * colors = "rgbymcwkvo";
        x = 50;
        textSize(70);
        int i;
        for(i = 0; i < 10; i++){
            stroke("%c", colors[i]);
            x = text(x, 500, "%c", colors[i]);
        }
    }

    textSize(20);
    stroke("white");
    text(40, 20, "cores.png: Cores do copiadas do {solarized}.");
    text(40, 480, "Na paleta, cada letra corresponde a uma cor.");
    save();

    destroy();
    return 0;
}


