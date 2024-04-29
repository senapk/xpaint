#define XPAINT
#include "xpaint.h"

int main() {
    open(100, 100, "figura_cores");
    stroke("white");
    fill("red");
    ellipse(50, 50, 31, 41);

    save();
    close();
    return 0;
}


