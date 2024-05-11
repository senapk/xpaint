#define XPAINT
#include "xpaint.h"

int main() {
    create(300, 300, "figura_cores");
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
    noFill();
    triangle(270, 30, 50, 180, 150, 190);
    pop();
    save();
    destroy();
    return 0;
}


