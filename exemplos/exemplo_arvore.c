#define XPAINT
#include "xpaint.h"

void fractal(float x, float y, float ang, float lado){
    float delta = 35 + math_rand(-2, 2); /* angulo de rotacao */
    float dec = 0.72 + math_rand(-20, 20)/100.0;
    if(lado < 10)
        return;
    
    float fx = x + lado * math_cos(ang);
    float fy = y - lado * math_sin(ang);
    draw_line(x, y, fx, fy); /* desenha a linha */
    
    fractal(fx, fy, ang - delta, lado * dec);
    fractal(fx, fy, ang        , lado * dec);
    fractal(fx, fy, ang + delta, lado * dec);
}

int main(){
    open(800, 500, "figura_arvore");
    fractal(400, 450, 90, 100);
    save();
    close();
    return 0;
}

