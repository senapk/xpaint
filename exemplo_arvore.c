#include "xpaint.h"
#include <stdlib.h>

void fractal(float x, float y, float ang, float lado){
    float delta = 35 + xm_rand(-2, 2); /* angulo de rotacao */
    float dec = 0.72 + xm_rand(-20, 20)/100.0;
    if(lado < 10)
        return;
    
    float fx = x + lado * xm_cos(ang);
    float fy = y - lado * xm_sin(ang);
    xd_line(x, y, fx, fy); /* desenha a linha */
    
    fractal(fx, fy, ang - delta, lado * dec);
    fractal(fx, fy, ang        , lado * dec);
    fractal(fx, fy, ang + delta, lado * dec);
}

int main(){
    x_open(800, 500);
    srand(0); /* comente para ter sempre uma arvore diferente */
    fractal(400, 450, 90, 100);
    x_save("figura_arvore");
    x_close();
    return 0;
}

