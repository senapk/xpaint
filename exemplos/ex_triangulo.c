#define XPAINT
#include "xpaint.h"

void fractal(float x, float y, float lado, float ang){
    if(lado < 5)
        return;
    int i;
    for(i = 0; i < 3; i++){
        fractal(x, y, lado / 2, ang);
        
        float x0 = x, y0 = y; /* salva x e y */
        x += lado * xcos(ang); /* translada x e y */
        y -= lado * xsin(ang);
        line(x0, y0, x, y); /* desenha a linha */
        
        ang -= 120;
    }
}
int main(){
    create(800, 700, "figura_triangulo");
    stroke("white");
    textSize(30);
    text(140, 0, "Exemplo do fractal de Sierpinski");
    fractal(50, 650, 700, 60);
    save();
    destroy();
    return 0;
}

