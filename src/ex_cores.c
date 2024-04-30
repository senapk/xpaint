#define XPAINT
#include "xpaint.h"

int main() {
    open(100, 100, "figura_cores");
    strokeWeight(1);
    stroke("white");
    fill("red");
    // noStroke();

    push();
    // center(50, 50);
    // rotate(90);
    scale(1);
    ellipse(50, 50, 10, 10);
    circle(50, 70, 10);
    square(5, 5, 30);
    triangle(10, 70, 50, 80, 15, 90);
    pop();
    save();
    close();
    return 0;
}


