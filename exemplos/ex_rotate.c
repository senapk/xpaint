#define XPAINT
#include "xpaint.h"

void center_rect(int x, int y, int width, int height){
    int x0 = x - width / 2;
    int y0 = y - height / 2;
    rect(x0, y0, width, height);
}

int main(){
    create(400, 400, "figura_rotate");
    background("black");    
    stroke("white");
    fill("yellow");

    push();
        translate(200, 200);
        rotate(15);
        scale(1.5);
        strokeWeight(3);
        int x = 0;
        int y = 0;
        arc(x, y, 200, 180, 45, 270);
        center_rect(x, y, 100, 100);
        circle(x, y, 100);
    pop();

    save();
    destroy();
    return 0;
}