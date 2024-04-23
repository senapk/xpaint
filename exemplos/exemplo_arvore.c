#define XPAINT
#include "xpaint.h"

void fractal(float x, float y, float ang, float lado){
    float delta = 35 + xrand(-2, 2); /* angulo de rotacao */
    float dec = 0.72 + xrand(-20, 20)/100.0;
    if(lado < 10)
        return;
    
    float fx = x + lado * xcos(ang);
    float fy = y - lado * xsin(ang);
    line(x, y, fx, fy); /* desenha a linha */
    
    fractal(fx, fy, ang - delta, lado * dec);
    fractal(fx, fy, ang        , lado * dec);
    fractal(fx, fy, ang + delta, lado * dec);
}

int main(){
    open(800, 500, "figura_arvore");
    stroke(WHITE);
    fractal(400, 450, 90, 100);
    save();
    close();
    return 0;
}

