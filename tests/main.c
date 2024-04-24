//#define XPAINT
//#define XPPM
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/all.h"
#include <string.h>
#include <wchar.h>

int main() {
    open(1000, 600, "zz_figura_draw");
    background("black");
    stroke("green");
    // circle(200, 200, 300);
    stroke("white");
    arc(200, 200, 150, 50, 190, 100);

    penSetThick(30);
    penSetPos(150, 100);
    penSetAngle(-20);
    for(int i = 0; i < 5; i++){
        penWalk(500);
        stroke(rgba(xrand(0, 256), xrand(0, 256), xrand(0, 256), 100));
        penRotate(-144);
    }
    save();
    close();
}

