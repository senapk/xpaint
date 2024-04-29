#define XPAINT
#include "xpaint.h"

int main(){
    open(100, 100, "main");
    push();
    scale(10);
    stroke("255");
    rotate(0);
    for (int i = 0; i < 10; i++){
        point(i, i);
    }
    pop();
    save();
    close();
    return 0;
}
