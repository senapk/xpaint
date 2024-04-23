//#define XPAINT
//#define XPPM
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/all.h"
#include <string.h>
#include <wchar.h>

int main() {
    srand(time(NULL));
    open(1000, 600, "zz_figura_draw");
    stroke(color(0, 0, 0, 150));
    background(BLACK);
    stroke_char('g');

    __fill_circle(200, 200, 300);
    stroke(WHITE);
    arc(200, 200, 150, 50, 190, 100);

    penSetThick(30);
    penSetPos(150, 100);
    penSetAngle(-20);
    for(int i = 0; i < 5; i++){
        penWalk(500);
        stroke(color(rand() % 256, rand() % 256, rand() % 256, 255));
        penRotate(-144);
    }
    save();
    close();
}

