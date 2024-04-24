#include "../src/all.h"

#include "stdio.h"
int main(){
    open(1000, 600, "zz_draw");
    stroke("white");
    background("black");

    // push();

    textSize(30);
    stroke("yellow");
    text(90, 30, "Exemplo das funções de desenho de\n         formas geométricas");

    strokeWeight(3);
    stroke("white");
    fill("yellow");
    textSize(20);
    int x = 10;
    int y = 100;
    text(x, y, "line");
    line(x + 30, y + 30, x + 180, y + 180);

    x += 200;
    text(x, y, "circle");
    circle(x + 100, y + 100, 80);

    x += 200;
    text(x, y, "bezier");
    bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200, x + 180, y + 180);  

    x += 200;
    text(x, y, "rect");
    rect(x + 30, y + 30, 150, 100);

    x = 10;
    y += 250;
    text(x, y, "arc");
    arc(x + 100, y + 100, 80, 30, 30, 290);

    x += 200;
    text(x, y, "triangle");
    triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

    x += 200;
    text(x, y, "ellipse");
    ellipse(x + 80, y + 100, 180, 100);  

    x += 200;
    text(x, y, "square");
    square(x + 30, y + 30, 150);

    // pop();


    save();
    close();
    return 0;
}