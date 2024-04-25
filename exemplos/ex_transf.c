#define XPAINT
#include "xpaint.h"
#include <stdlib.h>

int main() {
    open(400, 400, "figura_transf");
    srand(1);//lock random seed
    for (int i = 0; i < 100; i++) {
        push();
            translate(i * 10, i * 10);
            rotate(i * 10);
            scale(1 + 0.1 * i);
            fill("%d, %d, %d", xrand(255), xrand(255), xrand(255));
            square(-20, -20, 40);
        pop();
    }
    save();
    close();
}