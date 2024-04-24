#include "../src/all.h"

#include "stdio.h"
int main(){
    open(400, 400, "zz_draw");
    
    stroke("white");
    fill("yellow");
    background("black");
    push();
    rotate(15);
    scale(1.5);
    
    strokeWeight(3);
    arc(250, 200, 200, 20, 30, 290);
    rect(200, 150, 100, 100);
    circle(250, 200, 100);
    pop();
    

    save();
    close();
    return 0;
}